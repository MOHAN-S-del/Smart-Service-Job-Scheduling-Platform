/*
 * main.cpp
 * Main program to test Greedy Job Scheduling with Deadlines
 * Design & Analysis of Algorithms (DAA)
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include "job_scheduler.h"

using namespace std;

int main() {

    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║     GREEDY JOB SCHEDULING WITH DEADLINES          ║\n";
    cout << "║           Design & Analysis of Algorithms         ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    // Sample job data
    vector<Job> jobs = {
        {1, 2, 100, 0},  // Job 1
        {2, 1, 19, 0},   // Job 2
        {3, 2, 27, 0},   // Job 3
        {4, 1, 25, 0},   // Job 4
        {5, 3, 15, 0},   // Job 5
        {6, 3, 50, 0},   // Job 6
        {7, 2, 40, 0}    // Job 7
    };

    // Display initial job list
    cout << "\n=== INITIAL JOB LIST ===\n";
    cout << left << setw(10) << "Job ID"
         << setw(12) << "Deadline"
         << setw(10) << "Profit"
         << setw(12) << "Status\n";
    cout << "---------------------------------------------------\n";

    for (const auto& job : jobs) {
        cout << setw(10) << job.jobId
             << setw(12) << job.deadline
             << setw(10) << job.profit
             << "Pending\n";
    }

    // Execute greedy job scheduling algorithm
    scheduleJobs(jobs);

    // Display final schedule
    displaySchedule(jobs);

    // Calculate total profit
    int totalProfit = calculateTotalProfit(jobs);

    cout << "\n=== SUMMARY ===\n";
    cout << "Total Profit Earned: " << totalProfit << endl;

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║           Program Execution Complete              ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    return 0;
}
