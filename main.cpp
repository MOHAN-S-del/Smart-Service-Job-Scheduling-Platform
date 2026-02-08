// main.cpp
// SkillConnect DAA Project - Job Scheduling with Deadline Management
// Design and Analysis of Algorithms (DAA) Project

#include <iostream>
#include <vector>
#include <fstream>   // ✅ Added for frontend linking
#include "job_scheduler.h"
#include "deadline_manager.h"

using namespace std;

/**
 * Displays job details in formatted manner
 */
void displayJob(const Job& job) {
    cout << "Job ID: " << job.jobId
         << " | Deadline: " << job.deadline
         << " | Profit: " << job.profit
         << " | Priority: " << job.priority << endl;
}

/**
 * Displays all jobs in a vector
 */
void displayJobList(const vector<Job>& jobs, const string& title) {
    cout << "\n" << title << endl;
    cout << string(60, '=') << endl;

    if (jobs.empty()) {
        cout << "No jobs to display." << endl;
    } else {
        for (int i = 0; i < jobs.size(); i++) {
            cout << (i + 1) << ". ";
            displayJob(jobs[i]);
        }
    }
    cout << string(60, '=') << endl;
}

/**
 * Calculates total profit from scheduled jobs
 */
int calculateTotalProfit(const vector<Job>& jobs) {
    int total = 0;
    for (int i = 0; i < jobs.size(); i++) {
        total += jobs[i].profit;
    }
    return total;
}

int main() {

    cout << "\n=====================================================\n";
    cout << "     SKILLCONNECT - JOB SCHEDULING SYSTEM (DAA)\n";
    cout << "=====================================================\n\n";

    // ============================================================
    // STEP 1: Create sample job data
    // ============================================================
    cout << "STEP 1: Creating Sample Jobs...\n";

    vector<Job> jobs;

    jobs.push_back(Job(1, 2, 100, 7));
    jobs.push_back(Job(2, 1, 19, 3));
    jobs.push_back(Job(3, 2, 27, 2));
    jobs.push_back(Job(4, 1, 25, 6));
    jobs.push_back(Job(5, 3, 15, 4));
    jobs.push_back(Job(6, 3, 50, 8));
    jobs.push_back(Job(7, 2, 35, 5));
    jobs.push_back(Job(8, 1, 20, 2));

    displayJobList(jobs, "ALL AVAILABLE JOBS");

    cout << "\nPriority >= 5 → HARD deadline\n";
    cout << "Priority < 5  → SOFT deadline\n";

    // ============================================================
    // STEP 2: Greedy Scheduling
    // ============================================================
    cout << "\nSTEP 2: Applying Greedy Job Scheduling...\n";

    vector<Job> scheduledJobs = scheduleJobsGreedy(jobs);
    displayJobList(scheduledJobs, "SCHEDULED JOBS");

    int totalProfit = calculateTotalProfit(scheduledJobs);

    // ============================================================
    // STEP 3: Unscheduled Jobs
    // ============================================================
    vector<Job> unscheduledJobs;

    for (int i = 0; i < jobs.size(); i++) {
        bool found = false;
        for (int j = 0; j < scheduledJobs.size(); j++) {
            if (jobs[i].jobId == scheduledJobs[j].jobId) {
                found = true;
                break;
            }
        }
        if (!found) unscheduledJobs.push_back(jobs[i]);
    }

    displayJobList(unscheduledJobs, "UNSCHEDULED JOBS");

    // ============================================================
    // STEP 4: Deadline Checking
    // ============================================================
    int currentTime = 3;
    vector<Job> missedJobs = getMissedDeadlineJobs(unscheduledJobs, currentTime);

    // ============================================================
    // STEP 5: Reassignment
    // ============================================================
    vector<Job> reassignedJobs = reassignExpiredJobs(missedJobs, scheduledJobs);
    int reassignedProfit = calculateTotalProfit(reassignedJobs);

    // ============================================================
    // FINAL SUMMARY (Console)
    // ============================================================
    cout << "\n================ FINAL SUMMARY ================\n";
    cout << "Total Jobs:            " << jobs.size() << endl;
    cout << "Scheduled Jobs:        " << scheduledJobs.size() << endl;
    cout << "Reassigned Jobs:       " << reassignedJobs.size() << endl;
    cout << "Total Profit Earned:   " << (totalProfit + reassignedProfit) << endl;
    cout << "================================================\n";

    // ============================================================
    // ✅ FRONTEND LINK FILE (VERY IMPORTANT)
    // ============================================================
    ofstream fout("frontend_result.txt");

    fout << "SKILLCONNECT - GREEDY JOB SCHEDULING RESULT\n";
    fout << "-------------------------------------------\n";
    fout << "Total Jobs: " << jobs.size() << "\n";
    fout << "Scheduled Jobs: " << scheduledJobs.size() << "\n";
    fout << "Reassigned Jobs: " << reassignedJobs.size() << "\n";
    fout << "Total Profit: " << (totalProfit + reassignedProfit) << "\n\n";

    if (!scheduledJobs.empty()) {
        fout << "Top Scheduled Job\n";
        fout << "Job ID: " << scheduledJobs[0].jobId << "\n";
        fout << "Deadline: " << scheduledJobs[0].deadline << "\n";
        fout << "Profit: " << scheduledJobs[0].profit << "\n";
        fout << "Selected using Greedy Algorithm\n";
    }

    fout.close();

    cout << "\nFrontend result file generated: frontend_result.txt\n";
    cout << "Program completed successfully!\n\n";

    return 0;
}
