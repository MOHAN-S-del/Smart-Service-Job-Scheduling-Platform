// main.cpp
// SkillConnect DAA Project - Job Scheduling with Deadline Management
// Design and Analysis of Algorithms (DAA) Project

#include <iostream>
#include <vector>
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
    cout << "\n";
    cout << "=====================================================" << endl;
    cout << "     SKILLCONNECT - JOB SCHEDULING SYSTEM (DAA)     " << endl;
    cout << "=====================================================" << endl;
    cout << "\n";
    
    // ============================================================
    // STEP 1: Create sample job data
    // ============================================================
    cout << "STEP 1: Creating Sample Jobs..." << endl;
    
    vector<Job> jobs;
    
    // Adding sample jobs with different deadlines, profits, and priorities
    // Job(jobId, deadline, profit, priority)
    jobs.push_back(Job(1, 2, 100, 7));  // High profit, high priority (Hard deadline)
    jobs.push_back(Job(2, 1, 19, 3));   // Low profit, low priority (Soft deadline)
    jobs.push_back(Job(3, 2, 27, 2));   // Medium profit, low priority (Soft deadline)
    jobs.push_back(Job(4, 1, 25, 6));   // Medium profit, high priority (Hard deadline)
    jobs.push_back(Job(5, 3, 15, 4));   // Low profit, medium priority (Soft deadline)
    jobs.push_back(Job(6, 3, 50, 8));   // High profit, high priority (Hard deadline)
    jobs.push_back(Job(7, 2, 35, 5));   // Medium profit, high priority (Hard deadline)
    jobs.push_back(Job(8, 1, 20, 2));   // Low profit, low priority (Soft deadline)
    
    displayJobList(jobs, "ALL AVAILABLE JOBS");
    
    cout << "\nNote: Priority >= 5 indicates HARD deadline" << endl;
    cout << "      Priority < 5 indicates SOFT deadline" << endl;
    
    // ============================================================
    // STEP 2: Apply Greedy Job Scheduling Algorithm
    // ============================================================
    cout << "\n\nSTEP 2: Applying Greedy Job Scheduling Algorithm..." << endl;
    cout << "Strategy: Select jobs with maximum profit first" << endl;
    cout << "Schedule at latest available slot before deadline\n" << endl;
    
    vector<Job> scheduledJobs = scheduleJobsGreedy(jobs);
    
    displayJobList(scheduledJobs, "SCHEDULED JOBS (Greedy Algorithm)");
    
    // Calculate and display total profit
    int totalProfit = calculateTotalProfit(scheduledJobs);
    cout << "\nTotal Profit from Scheduled Jobs: " << totalProfit << endl;
    cout << "Number of Jobs Scheduled: " << scheduledJobs.size() 
         << " out of " << jobs.size() << endl;
    
    // ============================================================
    // STEP 3: Identify jobs that couldn't be scheduled
    // ============================================================
    cout << "\n\nSTEP 3: Identifying Unscheduled Jobs..." << endl;
    
    vector<Job> unscheduledJobs;
    
    // Find jobs that were not scheduled
    for (int i = 0; i < jobs.size(); i++) {
        bool isScheduled = false;
        for (int j = 0; j < scheduledJobs.size(); j++) {
            if (jobs[i].jobId == scheduledJobs[j].jobId) {
                isScheduled = true;
                break;
            }
        }
        if (!isScheduled) {
            unscheduledJobs.push_back(jobs[i]);
        }
    }
    
    displayJobList(unscheduledJobs, "UNSCHEDULED JOBS (Missed Deadlines)");
    
    // ============================================================
    // STEP 4: Check for deadline misses (simulate current time)
    // ============================================================
    cout << "\n\nSTEP 4: Checking Deadline Status..." << endl;
    
    int currentTime = 3; // Simulate that we are at time unit 3
    cout << "Current Time: " << currentTime << " time units" << endl;
    
    vector<Job> missedJobs = getMissedDeadlineJobs(unscheduledJobs, currentTime);
    
    cout << "\nJobs with missed deadlines: " << missedJobs.size() << endl;
    
    // Display deadline status for each unscheduled job
    for (int i = 0; i < unscheduledJobs.size(); i++) {
        cout << "Job " << unscheduledJobs[i].jobId << " (Deadline: " 
             << unscheduledJobs[i].deadline << "): ";
        
        if (hasDeadlineMissed(unscheduledJobs[i], currentTime)) {
            if (isHardDeadline(unscheduledJobs[i])) {
                cout << "MISSED - HARD DEADLINE (Cannot reschedule)" << endl;
            } else {
                cout << "MISSED - SOFT DEADLINE (Can reschedule with penalty)" << endl;
            }
        } else {
            cout << "Within deadline" << endl;
        }
    }
    
    // ============================================================
    // STEP 5: Reassign expired jobs (soft deadlines only)
    // ============================================================
    cout << "\n\nSTEP 5: Reassigning Expired Jobs..." << endl;
    
    vector<Job> reassignedJobs = reassignExpiredJobs(missedJobs, scheduledJobs);
    
    displayJobList(reassignedJobs, "REASSIGNED JOBS (With Penalties)");
    
    // Calculate profit from reassigned jobs
    int reassignedProfit = calculateTotalProfit(reassignedJobs);
    cout << "\nProfit from Reassigned Jobs: " << reassignedProfit << endl;
    
    // ============================================================
    // FINAL SUMMARY
    // ============================================================
    cout << "\n\n";
    cout << "=====================================================" << endl;
    cout << "                  FINAL SUMMARY                      " << endl;
    cout << "=====================================================" << endl;
    cout << "Total Jobs Available:        " << jobs.size() << endl;
    cout << "Jobs Scheduled (Greedy):     " << scheduledJobs.size() << endl;
    cout << "Jobs Unscheduled:            " << unscheduledJobs.size() << endl;
    cout << "Jobs Reassigned:             " << reassignedJobs.size() << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Profit from Scheduled Jobs:  " << totalProfit << endl;
    cout << "Profit from Reassigned Jobs: " << reassignedProfit << endl;
    cout << "Total Profit Earned:         " << (totalProfit + reassignedProfit) << endl;
    cout << "=====================================================" << endl;
    
    cout << "\n\nKEY CONCEPTS DEMONSTRATED:" << endl;
    cout << "1. Greedy Algorithm for Job Scheduling" << endl;
    cout << "2. Hard vs Soft Deadline Management" << endl;
    cout << "3. Deadline Checking and Validation" << endl;
    cout << "4. Job Reassignment with Penalty Calculation" << endl;
    cout << "5. Profit Maximization Strategy" << endl;
    
    cout << "\n\nProgram completed successfully!" << endl;
    cout << "\n";
    
    return 0;
}
