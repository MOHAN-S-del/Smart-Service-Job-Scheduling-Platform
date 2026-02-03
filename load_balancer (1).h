/*
 * load_balancer.h
 * 
 * Load Balancing using Greedy Algorithm
 * Design and Analysis of Algorithms (DAA) Project
 * 
 * GREEDY APPROACH:
 * Load balancing is a classic greedy algorithm problem where we make locally
 * optimal choices at each step. The greedy strategy assigns each incoming job
 * to the worker with the minimum current load, ensuring balanced distribution.
 * 
 * WHY GREEDY WORKS HERE:
 * - At each step, we choose the "best" available option (least loaded worker)
 * - This local optimum leads to a near-optimal global solution
 * - Time complexity: O(n*m) where n = jobs, m = workers
 * - Space complexity: O(m) for storing worker states
 */

#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

/**
 * Worker structure
 * Represents a worker/server in the load balancing system
 */
typedef struct Worker {
    int workerId;       // Unique identifier for the worker
    int currentLoad;    // Number of jobs currently assigned to this worker
    float rating;       // Performance rating (can be used for weighted balancing)
} Worker;

/**
 * Greedy Load Balancing Algorithm
 * 
 * Distributes 'jobCount' jobs across workers using a greedy approach.
 * Each job is assigned to the worker with the minimum current load.
 * 
 * @param workers - Array of Worker structures
 * @param workerCount - Number of workers in the array
 * @param jobCount - Number of jobs to distribute
 * 
 * Greedy Choice: Always assign the next job to the least loaded worker
 */
void balanceLoadGreedy(Worker workers[], int workerCount, int jobCount);

/**
 * Find Least Loaded Worker
 * 
 * Helper function that implements the greedy selection criteria.
 * Scans through all workers to find the one with minimum current load.
 * 
 * @param workers - Array of Worker structures
 * @param workerCount - Number of workers in the array
 * @return Index of the worker with the least current load
 * 
 * Time Complexity: O(m) where m = number of workers
 */
int findLeastLoadedWorker(const Worker workers[], int workerCount);

#endif // LOAD_BALANCER_H
