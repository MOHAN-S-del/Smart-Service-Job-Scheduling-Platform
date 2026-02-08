/*
 * job_scheduler.cpp
 * Implementation of Greedy Job Scheduling Algorithm
 * Design and Analysis of Algorithms (DAA) Project
 */

#include "job_scheduler.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/*
 * GREEDY JOB SCHEDULING ALGORITHM
 *
 * Strategy:
 * 1. Sort jobs by profit in descending order
 * 2. For each job, schedule it in the latest available slot before its deadline
 * 3. If no slot is available, mark the job as missed
 *
 * Time Complexity: O(n log n + n^2)
 * Space Complexity: O(n)
 */

// Initialize a job
void initJob(Job& job, int id, int deadline, int profit) {
    job.jobId = id;
    job.deadline = deadline;
    job.profit = profit;
    job.status = 0; // Pending
}

// Sort jobs by profit (descending)
static bool compareByProfit(const Job& a, const Job& b) {
    return a.profit > b.profit;
}

// Find maximum deadline
static int findMaxDeadline(const vector<Job>& jobs) {
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }
    return maxDeadline;
}

// Main greedy scheduling algorithm
void scheduleJobs(vector<Job>& jobs) {

    cout << "\n=== GREEDY JOB SCHEDULING ===\n";
    cout << "Sorting jobs by profit (descending order)...\n\n";

    // Step 1: Sort by profit
    sort(jobs.begin(), jobs.end(), compareByProfit);

    // Step 2: Create time slots
    int maxDeadline = findMaxDeadline(jobs);
    vector<int> timeSlots(maxDeadline, -1); // -1 means free slot

    // Step 3: Schedule jobs greedily
    cout << "Scheduling jobs...\n";
    for (int i = 0; i < jobs.size(); i++) {

        // Try latest available slot before deadline
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (timeSlots[j] == -1) {
                timeSlots[j] = i;
                jobs[i].status = 1; // Scheduled

                cout << "Job " << jobs[i].jobId
                     << " scheduled in time slot " << j + 1
                     << " (Profit: " << jobs[i].profit << ")\n";
                break;
            }
        }

        // If still pending, mark as missed
        if (jobs[i].status == 0) {
            jobs[i].status = 2;
            cout << "Job " << jobs[i].jobId
                 << " MISSED (Deadline: " << jobs[i].deadline
                 << ", Profit: " << jobs[i].profit << ")\n";
        }
    }
}

// Display scheduled and missed jobs
void displaySchedule(const vector<Job>& jobs) {

    cout << "\n=== SCHEDULED JOBS ===\n";
    cout << left << setw(10) << "Job ID"
         << setw(12) << "Deadline"
         << setw(10) << "Profit"
         << setw(12) << "Status\n";
    cout << "---------------------------------------------------\n";

    int scheduledCount = 0;
    for (const auto& job : jobs) {
        if (job.status == 1) {
            cout << setw(10) << job.jobId
                 << setw(12) << job.deadline
                 << setw(10) << job.profit
                 << "Scheduled\n";
            scheduledCount++;
        }
    }

    if (scheduledCount == 0) {
        cout << "No jobs scheduled.\n";
    }

    cout << "\n=== MISSED JOBS ===\n";
    cout << left << setw(10) << "Job ID"
         << setw(12) << "Deadline"
         << setw(10) << "Profit"
         << setw(12) << "Status\n";
    cout << "---------------------------------------------------\n";

    int missedCount = 0;
    for (const auto& job : jobs) {
        if (job.status == 2) {
            cout << setw(10) << job.jobId
                 << setw(12) << job.deadline
                 << setw(10) << job.profit
                 << "Missed\n";
            missedCount++;
        }
    }

    if (missedCount == 0) {
        cout << "No jobs missed.\n";
    }
}

// Display individual job
void displayJob(const Job& job) {

    string statusStr;
    if (job.status == 0) statusStr = "Pending";
    else if (job.status == 1) statusStr = "Scheduled";
    else if (job.status == 2) statusStr = "Missed";
    else statusStr = "Unknown";

    cout << "Job ID: " << job.jobId
         << ", Deadline: " << job.deadline
         << ", Profit: " << job.profit
         << ", Status: " << statusStr << endl;
}

// Calculate total profit
int calculateTotalProfit(const vector<Job>& jobs) {

    int totalProfit = 0;
    for (const auto& job : jobs) {
        if (job.status == 1) {
            totalProfit += job.profit;
        }
    }
    return totalProfit;
}
