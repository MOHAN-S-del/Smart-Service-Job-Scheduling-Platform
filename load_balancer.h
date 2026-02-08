// load_balancer.h
// Header file for Greedy Load Balancing Algorithm
// Design and Analysis of Algorithms (DAA) Project

#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "worker.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * GREEDY LOAD BALANCING CONCEPT:
 * 
 * OBJECTIVE:
 * Distribute jobs among workers to minimize imbalance and maximize efficiency
 * 
 * GREEDY STRATEGY:
 * At each step, assign the next job to the worker with minimum current load
 * This local optimal choice leads to globally balanced distribution
 * 
 * ADVANTAGES:
 * - Simple and efficient: O(n log m) where n=jobs, m=workers
 * - Near-optimal solution for most cases
 * - Prevents bottlenecks and overload
 * - Fair distribution of workload
 * 
 * APPLICATIONS:
 * - Web server load balancing
 * - CPU task scheduling
 * - Database query distribution
 * - Cloud resource allocation
 */

// Function declarations

/**
 * Distributes jobs among workers using Greedy Algorithm
 * @param workers: Vector of Worker objects (modified in-place)
 * @param totalJobs: Total number of jobs to distribute
 * @return: Vector of pairs <workerID, jobsAssigned> showing final distribution
 * 
 * ALGORITHM:
 * 1. For each job to be assigned:
 *    a. Find worker with minimum current load
 *    b. Check if worker has available capacity
 *    c. Assign job to that worker (increment load)
 * 2. Repeat until all jobs assigned or all workers at capacity
 * 
 * GREEDY CHOICE PROPERTY:
 * Always selecting the least loaded worker ensures balanced distribution
 * and minimizes maximum load across all workers
 * 
 * TIME COMPLEXITY: O(n * m) where n=jobs, m=workers
 * - Can be optimized to O(n log m) using min-heap
 */
vector<pair<int, int>> balanceLoadGreedy(vector<Worker>& workers, int totalJobs);

/**
 * Displays load distribution statistics
 * @param workers: Vector of Worker objects
 * 
 * Shows: individual loads, average load, load variance
 */
void displayLoadStatistics(const vector<Worker>& workers);

/**
 * Checks if load is balanced across workers
 * @param workers: Vector of Worker objects
 * @return: true if load variance is within acceptable threshold
 * 
 * A balanced system has minimal difference between
 * maximum and minimum worker loads
 */
bool isLoadBalanced(const vector<Worker>& workers);

/**
 * Calculates load balance quality metric
 * @param workers: Vector of Worker objects
 * @return: Balance score (0-100, higher is better)
 * 
 * Score = 100 - (variance from average * 10)
 * Perfect balance = 100, highly unbalanced = 0
 */
int calculateBalanceScore(const vector<Worker>& workers);

#endif // LOAD_BALANCER_H
