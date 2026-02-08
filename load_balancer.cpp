// load_balancer.cpp
// Implementation of Greedy Load Balancing Algorithm
// Design and Analysis of Algorithms (DAA) Project

#include "load_balancer.h"
#include "worker.h"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

/**
 * GREEDY CHOICE PROPERTY:
 * At each step, assign the job to the worker with MINIMUM current load.
 * This ensures that no worker gets unfairly overloaded while others are idle.
 * 
 * WHY THIS ENSURES FAIRNESS:
 * - Each job goes to the least busy worker
 * - Prevents concentration of work on few workers
 * - Distributes load evenly across all available resources
 * - Minimizes the maximum load on any single worker
 * - Optimal for minimizing completion time (makespan)
 * 
 * PROOF OF CORRECTNESS:
 * If we always choose the minimum load worker, the difference between
 * maximum and minimum loads never exceeds 1 job (in ideal case).
 * This is the best possible balance we can achieve.
 */

/**
 * Finds the worker with minimum current load
 * @param workers: Vector of Worker objects
 * @return: Index of worker with minimum load (-1 if all overloaded)
 * 
 * TIME COMPLEXITY: O(m) where m = number of workers
 */
int findMinLoadWorker(const vector<Worker>& workers) {
    int minIndex = -1;
    int minLoad = -1;
    
    // Find worker with minimum load who can still accept jobs
    for (int i = 0; i < workers.size(); i++) {
        // Check if worker can accept more jobs
        if (workers[i].canAcceptJob()) {
            // First valid worker or found one with smaller load
            if (minIndex == -1 || workers[i].currentLoad < minLoad) {
                minIndex = i;
                minLoad = workers[i].currentLoad;
            }
        }
    }
    
    return minIndex;
}

/**
 * Greedy Load Balancing Algorithm
 * @param workers: Vector of Worker objects (modified in-place)
 * @param totalJobs: Total number of jobs to distribute
 * @return: Vector of pairs <workerID, jobsAssigned>
 * 
 * ALGORITHM STEPS:
 * 1. For each job (from 1 to totalJobs):
 *    a. Find worker with minimum current load
 *    b. If worker found and has capacity, assign job
 *    c. Increment that worker's load by 1
 * 2. Return final distribution
 * 
 * TIME COMPLEXITY: O(n * m)
 * - n = number of jobs
 * - m = number of workers
 * - For each job, we scan all workers to find minimum
 * 
 * SPACE COMPLEXITY: O(m) for storing distribution results
 */
vector<pair<int, int>> balanceLoadGreedy(vector<Worker>& workers, int totalJobs) {
    cout << "\n=== GREEDY LOAD BALANCING ===" << endl;
    cout << "Total Jobs to Distribute: " << totalJobs << endl;
    cout << "Number of Workers: " << workers.size() << endl;
    cout << "Strategy: Assign each job to least loaded worker\n" << endl;
    
    int jobsAssigned = 0;
    int jobsRejected = 0;
    
    // Distribute jobs one by one (Greedy approach)
    for (int job = 1; job <= totalJobs; job++) {
        // GREEDY CHOICE: Find worker with minimum load
        int minWorkerIndex = findMinLoadWorker(workers);
        
        // Check if any worker can accept the job
        if (minWorkerIndex != -1) {
            // Assign job to the least loaded worker
            workers[minWorkerIndex].currentLoad++;
            jobsAssigned++;
            
            cout << "Job " << job << " -> Worker " 
                 << workers[minWorkerIndex].workerId 
                 << " (Load: " << workers[minWorkerIndex].currentLoad 
                 << "/" << workers[minWorkerIndex].maxCapacity << ")" << endl;
        } else {
            // All workers are at capacity
            jobsRejected++;
            cout << "Job " << job << " -> REJECTED (All workers at capacity)" << endl;
        }
    }
    
    // Prepare result: vector of <workerID, jobsAssigned>
    vector<pair<int, int>> distribution;
    
    cout << "\n--- Final Distribution ---" << endl;
    for (int i = 0; i < workers.size(); i++) {
        distribution.push_back(make_pair(workers[i].workerId, workers[i].currentLoad));
        cout << "Worker " << workers[i].workerId 
             << ": " << workers[i].currentLoad << " jobs assigned" << endl;
    }
    
    cout << "\nJobs Successfully Assigned: " << jobsAssigned << endl;
    cout << "Jobs Rejected: " << jobsRejected << endl;
    cout << "============================\n" << endl;
    
    return distribution;
}

/**
 * Displays load distribution statistics
 * @param workers: Vector of Worker objects
 * 
 * Shows: min load, max load, average load, variance
 */
void displayLoadStatistics(const vector<Worker>& workers) {
    if (workers.empty()) {
        cout << "No workers available." << endl;
        return;
    }
    
    int minLoad = workers[0].currentLoad;
    int maxLoad = workers[0].currentLoad;
    int totalLoad = 0;
    
    // Calculate min, max, and total load
    for (int i = 0; i < workers.size(); i++) {
        int load = workers[i].currentLoad;
        totalLoad += load;
        
        if (load < minLoad) minLoad = load;
        if (load > maxLoad) maxLoad = load;
    }
    
    double avgLoad = (double)totalLoad / workers.size();
    
    cout << "\n=== LOAD STATISTICS ===" << endl;
    cout << "Minimum Load:    " << minLoad << " jobs" << endl;
    cout << "Maximum Load:    " << maxLoad << " jobs" << endl;
    cout << "Average Load:    " << avgLoad << " jobs" << endl;
    cout << "Load Difference: " << (maxLoad - minLoad) << " jobs" << endl;
    cout << "Total Jobs:      " << totalLoad << endl;
    cout << "======================\n" << endl;
}

/**
 * Checks if load is balanced (difference <= 1)
 * @param workers: Vector of Worker objects
 * @return: true if balanced, false otherwise
 * 
 * BALANCE CRITERION:
 * Load is balanced if (maxLoad - minLoad) <= 1
 * This is the ideal state for greedy load balancing
 */
bool isLoadBalanced(const vector<Worker>& workers) {
    if (workers.empty()) return true;
    
    int minLoad = workers[0].currentLoad;
    int maxLoad = workers[0].currentLoad;
    
    for (int i = 1; i < workers.size(); i++) {
        if (workers[i].currentLoad < minLoad) {
            minLoad = workers[i].currentLoad;
        }
        if (workers[i].currentLoad > maxLoad) {
            maxLoad = workers[i].currentLoad;
        }
    }
    
    int difference = maxLoad - minLoad;
    bool balanced = (difference <= 1);
    
    if (balanced) {
        cout << "Status: BALANCED (difference = " << difference << ")" << endl;
    } else {
        cout << "Status: UNBALANCED (difference = " << difference << ")" << endl;
    }
    
    return balanced;
}

/**
 * Calculates load balance quality score
 * @param workers: Vector of Worker objects
 * @return: Balance score (0-100, higher = better)
 * 
 * SCORING:
 * - Perfect balance (diff = 0): Score = 100
 * - Good balance (diff = 1): Score = 90
 * - Higher difference = lower score
 */
int calculateBalanceScore(const vector<Worker>& workers) {
    if (workers.empty()) return 0;
    
    int minLoad = workers[0].currentLoad;
    int maxLoad = workers[0].currentLoad;
    
    for (int i = 1; i < workers.size(); i++) {
        if (workers[i].currentLoad < minLoad) {
            minLoad = workers[i].currentLoad;
        }
        if (workers[i].currentLoad > maxLoad) {
            maxLoad = workers[i].currentLoad;
        }
    }
    
    int difference = maxLoad - minLoad;
    
    // Score formula: 100 - (difference * 10)
    int score = 100 - (difference * 10);
    
    // Ensure score is between 0 and 100
    if (score < 0) score = 0;
    if (score > 100) score = 100;
    
    cout << "Balance Score: " << score << "/100" << endl;
    
    return score;
}

/**
 * ALGORITHM SUMMARY:
 * 
 * GREEDY APPROACH:
 * 1. Always choose the worker with minimum load
 * 2. Assign one job at a time
 * 3. Update worker's load immediately
 * 
 * FAIRNESS GUARANTEE:
 * - No worker gets 2+ jobs more than any other worker
 * - Even distribution across all resources
 * - Prevents bottlenecks and hotspots
 * 
 * OPTIMALITY:
 * - Minimizes makespan (maximum load on any worker)
 * - Achieves load difference of at most 1 in ideal case
 * - Optimal for identical jobs and workers
 * 
 * REAL-WORLD EXAMPLES:
 * - Round-robin DNS load balancing
 * - Least Connection load balancing in web servers
 * - Task scheduling in operating systems
 * - Request distribution in microservices
 */
