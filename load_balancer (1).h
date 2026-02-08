/*
 * load_balancer.h
 *
 * Load Balancing using Greedy Algorithm
 * Design and Analysis of Algorithms (DAA) Project
 *
 * GREEDY APPROACH:
 * Load balancing is a classic greedy algorithm problem where we make
 * locally optimal choices at each step.
 * The greedy strategy assigns each incoming job to the worker
 * with the minimum current load.
 *
 * WHY GREEDY WORKS HERE:
 * - At each step, we choose the least loaded worker
 * - This local optimum leads to fair global distribution
 * - Time Complexity: O(n * m)
 *   n = number of jobs, m = number of workers
 * - Space Complexity: O(m)
 */

#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
using namespace std;

/**
 * Worker structure
 * Represents a worker/server in the load balancing system
 */
struct Worker {
    int workerId;        // Unique identifier
    int currentLoad;     // Number of assigned jobs
    float rating;        // Worker rating (optional use)
};

/**
 * Find Least Loaded Worker
 *
 * Implements the greedy choice:
 * Select the worker with minimum current load.
 *
 * @param workers - Vector of workers
 * @return Index of least loaded worker
 *
 * Time Complexity: O(m)
 */
int findLeastLoadedWorker(const vector<Worker>& workers);

/**
 * Greedy Load Balancing Algorithm
 *
 * Distributes jobs across workers by always assigning
 * the next job to the least loaded worker.
 *
 * @param workers - Vector of workers
 * @param jobCount - Number of jobs to distribute
 */
void balanceLoadGreedy(vector<Worker>& workers, int jobCount);

#endif // LOAD_BALANCER_H
