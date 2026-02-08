// deadline_manager.cpp
// Implementation of Deadline Management for Job Scheduling
// Design and Analysis of Algorithms (DAA) Project

#include "deadline_manager.h"
#include <iostream>
#include <algorithm>
using namespace std;

/**
 * HARD DEADLINE CONCEPT:
 * - Job MUST be completed by the deadline
 * - Missing deadline = 0 profit (complete failure)
 * - No rescheduling or late submission possible
 * - Critical in real-time systems, contracts, legal deadlines
 * 
 * SOFT DEADLINE CONCEPT:
 * - Job CAN be completed after deadline with penalty
 * - Late completion still earns reduced profit
 * - Allows flexibility in scheduling
 * - Common in project management, academic assignments
 */

/**
 * Checks if a single job has missed its deadline
 * @param job: Job to check
 * @param currentTime: Current time unit
 * @return: true if missed, false otherwise
 */
bool hasDeadlineMissed(const Job& job, int currentTime) {
    // Job misses deadline if current time exceeds its deadline
    return currentTime > job.deadline;
}

/**
 * Finds all jobs that have missed their deadlines
 * @param jobs: List of all jobs
 * @param currentTime: Current time unit
 * @return: Vector of jobs with missed deadlines
 */
vector<Job> getMissedDeadlineJobs(const vector<Job>& jobs, int currentTime) {
    vector<Job> missedJobs;
    
    // Check each job against current time
    for (int i = 0; i < jobs.size(); i++) {
        if (hasDeadlineMissed(jobs[i], currentTime)) {
            missedJobs.push_back(jobs[i]);
        }
    }
    
    return missedJobs;
}

/**
 * Calculates reduced profit after deadline miss (for soft deadlines)
 * @param job: The job
 * @param delay: Time units past deadline
 * @return: Reduced profit value
 * 
 * PENALTY FORMULA:
 * - 10% profit reduction per time unit of delay
 * - Minimum profit = 10% of original (max 90% penalty)
 */
int calculatePenalty(const Job& job, int delay) {
    // Hard deadline: No profit if missed
    if (isHardDeadline(job)) {
        return 0;
    }
    
    // Soft deadline: Apply penalty (10% per time unit delay)
    int penaltyPercent = delay * 10;
    
    // Cap penalty at 90% (keep at least 10% profit)
    if (penaltyPercent > 90) {
        penaltyPercent = 90;
    }
    
    // Calculate reduced profit
    int reducedProfit = job.profit - (job.profit * penaltyPercent / 100);
    
    return reducedProfit;
}

/**
 * Determines if job has hard or soft deadline
 * @param job: Job to check
 * @return: true if hard deadline, false if soft
 * 
 * CONVENTION:
 * - priority >= 5: Hard deadline (strict, no late submission)
 * - priority < 5: Soft deadline (flexible, late with penalty)
 */
bool isHardDeadline(const Job& job) {
    // High priority jobs are treated as hard deadlines
    return job.priority >= 5;
}

/**
 * Reassigns expired jobs using greedy approach
 * @param expiredJobs: Jobs that missed deadlines
 * @param scheduledJobs: Currently scheduled jobs
 * @return: Vector of successfully reassigned jobs
 * 
 * GREEDY STRATEGY:
 * 1. Filter out hard deadline jobs (cannot be rescheduled)
 * 2. Sort soft deadline jobs by profit (descending)
 * 3. Extend deadline by small increment
 * 4. Apply penalty based on delay
 * 5. Attempt to reschedule with new parameters
 */
vector<Job> reassignExpiredJobs(vector<Job>& expiredJobs, 
                                const vector<Job>& scheduledJobs) {
    vector<Job> reassignedJobs;
    
    cout << "\n=== REASSIGNING EXPIRED JOBS ===" << endl;
    
    // Process each expired job
    for (int i = 0; i < expiredJobs.size(); i++) {
        Job& job = expiredJobs[i];
        
        // Check if it's a hard deadline
        if (isHardDeadline(job)) {
            // Hard deadline: Cannot reschedule
            cout << "Job " << job.jobId << ": HARD DEADLINE - Cannot reschedule (Profit lost: " 
                 << job.profit << ")" << endl;
            continue;
        }
        
        // Soft deadline: Attempt to reschedule
        cout << "Job " << job.jobId << ": SOFT DEADLINE - Attempting reassignment..." << endl;
        
        // Calculate delay (how much past original deadline)
        int delay = 1; // Assume 1 time unit delay for simplicity
        
        // Extend deadline by 2 time units (greedy: minimal extension)
        int oldDeadline = job.deadline;
        job.deadline = oldDeadline + 2;
        
        // Calculate new profit with penalty
        int oldProfit = job.profit;
        job.profit = calculatePenalty(job, delay);
        
        // Add to reassigned list
        reassignedJobs.push_back(job);
        
        // Display reassignment details
        cout << "  - Old Deadline: " << oldDeadline 
             << " -> New Deadline: " << job.deadline << endl;
        cout << "  - Old Profit: " << oldProfit 
             << " -> New Profit: " << job.profit 
             << " (Penalty: " << (oldProfit - job.profit) << ")" << endl;
        cout << "  - Status: REASSIGNED SUCCESSFULLY" << endl;
    }
    
    // Sort reassigned jobs by new profit (for optimal rescheduling)
    sort(reassignedJobs.begin(), reassignedJobs.end(), 
         [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });
    
    cout << "\nTotal Reassigned Jobs: " << reassignedJobs.size() << endl;
    cout << "================================\n" << endl;
    
    return reassignedJobs;
}

/**
 * ALGORITHM SUMMARY:
 * 
 * DEADLINE CHECKING:
 * - Compare current time with job deadline
 * - O(1) for single job, O(n) for all jobs
 * 
 * REASSIGNMENT STRATEGY:
 * - Hard deadlines: Reject (profit = 0)
 * - Soft deadlines: Extend deadline + Apply penalty
 * - Greedy: Prioritize high-profit jobs even after penalty
 * 
 * PRACTICAL APPLICATION:
 * - Operating systems: Process scheduling with deadlines
 * - Project management: Task rescheduling
 * - Real-time systems: Hard deadline enforcement
 * - Cloud computing: Job queue management with SLA
 */
