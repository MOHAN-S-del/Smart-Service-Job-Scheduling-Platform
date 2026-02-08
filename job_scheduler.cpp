// job_scheduler.cpp
// Implementation of Greedy Job Scheduling Algorithm
// Design and Analysis of Algorithms (DAA) Project

#include "job_scheduler.h"
#include <algorithm>
#include <vector>
using namespace std;

/**
 * GREEDY CHOICE PROPERTY:
 * At each step, select the job with maximum profit that can be scheduled
 * before its deadline. This local optimal choice leads to global optimal solution.
 * 
 * STRATEGY:
 * 1. Sort jobs in descending order of profit (highest profit first)
 * 2. For each job, find the latest available time slot before its deadline
 * 3. If slot is free, schedule the job; otherwise skip it
 * 
 * TIME COMPLEXITY: O(n²) where n is number of jobs
 * - Sorting: O(n log n)
 * - Scheduling: O(n²) in worst case (n jobs × n slots to check)
 * - Overall: O(n²)
 * 
 * SPACE COMPLEXITY: O(n) for time slots array and result vector
 */

vector<Job> scheduleJobsGreedy(vector<Job>& jobs) {
    int n = jobs.size();
    
    // If no jobs, return empty vector
    if (n == 0) {
        return vector<Job>();
    }
    
    // Step 1: Sort jobs by profit in descending order (Greedy Choice)
    // Jobs with higher profit are given preference
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        // Primary: Sort by profit (descending)
        if (a.profit != b.profit) {
            return a.profit > b.profit;
        }
        // Secondary: If profit is same, sort by priority (descending)
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }
        // Tertiary: If both same, sort by deadline (ascending - earlier deadline first)
        return a.deadline < b.deadline;
    });
    
    // Step 2: Find maximum deadline to determine time slots needed
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }
    
    // Step 3: Create time slots array to track which slots are occupied
    // slots[i] = -1 means time slot i is free
    // slots[i] = jobId means time slot i is occupied by that job
    vector<int> slots(maxDeadline + 1, -1);
    
    // Vector to store scheduled jobs
    vector<Job> scheduledJobs;
    
    // Step 4: Schedule jobs using greedy approach
    for (int i = 0; i < n; i++) {
        // For current job, find latest available slot before its deadline
        // We search from deadline backwards to maximize flexibility for future jobs
        for (int slot = jobs[i].deadline; slot > 0; slot--) {
            // If this time slot is free, schedule the job here
            if (slots[slot] == -1) {
                slots[slot] = jobs[i].jobId;  // Mark slot as occupied
                scheduledJobs.push_back(jobs[i]);  // Add to scheduled jobs
                break;  // Job scheduled, move to next job
            }
        }
        // If no slot found, job cannot be scheduled (implicitly skipped)
    }
    
    // Step 5: Sort scheduled jobs by their time slot for better presentation
    // This helps display jobs in chronological order
    sort(scheduledJobs.begin(), scheduledJobs.end(), 
         [&slots](const Job& a, const Job& b) {
        // Find which slot each job occupies
        int slotA = 0, slotB = 0;
        for (int i = 1; i < slots.size(); i++) {
            if (slots[i] == a.jobId) slotA = i;
            if (slots[i] == b.jobId) slotB = i;
        }
        return slotA < slotB;
    });
    
    return scheduledJobs;
}

/**
 * ALGORITHM EXPLANATION:
 * 
 * Example: Jobs = [(J1, deadline=2, profit=100), (J2, deadline=1, profit=19),
 *                  (J3, deadline=2, profit=27), (J4, deadline=1, profit=25)]
 * 
 * After sorting by profit: [J1(100), J3(27), J4(25), J2(19)]
 * 
 * Scheduling:
 * - J1 (deadline=2): Schedule at slot 2 → slots = [-, -, J1]
 * - J3 (deadline=2): Slot 2 occupied, schedule at slot 1 → slots = [-, J3, J1]
 * - J4 (deadline=1): Slot 1 occupied, cannot schedule
 * - J2 (deadline=1): Slot 1 occupied, cannot schedule
 * 
 * Result: [J3, J1] with total profit = 127
 * 
 * WHY GREEDY WORKS:
 * - Selecting highest profit job first ensures maximum profit contribution
 * - Scheduling at latest possible slot preserves earlier slots for other jobs
 * - This approach guarantees optimal solution for job scheduling problem
 */
