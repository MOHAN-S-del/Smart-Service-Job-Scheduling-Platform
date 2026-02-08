/*
 * load_balancer.cpp
 *
 * Implementation of Load Balancing using Greedy Algorithm
 * Design and Analysis of Algorithms (DAA) Project
 */

#include "load_balancer.h"
#include <vector>
using namespace std;

/**
 * GREEDY ALGORITHM IMPLEMENTATION
 *
 * WHY THIS IS GREEDY:
 * - Makes a locally optimal choice at each step
 * - Assigns each job to the least loaded worker
 * - Does not reconsider previous assignments
 * - Assumes local optimum leads to global balance
 */

/**
 * Find Least Loaded Worker
 *
 * Core greedy selection logic.
 *
 * ALGORITHM:
 * 1. Assume first worker has minimum load
 * 2. Compare with all other workers
 * 3. Update minimum when a lighter-loaded worker is found
 * 4. Return index of worker with minimum load
 *
 * TIME COMPLEXITY: O(m)
 * SPACE COMPLEXITY: O(1)
 */
int findLeastLoadedWorker(const vector<Worker>& workers) {
    int minIndex = 0;
    int minLoad = workers[0].currentLoad;

    // Greedy selection: linear scan
    for (int i = 1; i < workers.size(); i++) {
        if (workers[i].currentLoad < minLoad) {
            minLoad = workers[i].currentLoad;
            minIndex = i;
        }
    }

    return minIndex;
}

/**
 * Balance Load using Greedy Algorithm
 *
 * GREEDY STRATEGY:
 * Assign each incoming job to the worker
 * who currently has the minimum load.
 *
 * HOW IT PREVENTS OVERLOAD:
 * - Continuously checks worker loads
 * - Always selects least busy worker
 * - Automatically balances workload
 *
 * ALGORITHM STEPS:
 * 1. For each job:
 *    a. Find least loaded worker
 *    b. Assign job
 *    c. Increment load
 *
 * TIME COMPLEXITY:
 * O(n × m)
 * n = jobs, m = workers
 *
 * SPACE COMPLEXITY:
 * O(1) (in-place update)
 */
void balanceLoadGreedy(vector<Worker>& workers, int jobCount) {

    // Assign jobs one by one
    for (int job = 1; job <= jobCount; job++) {

        // GREEDY CHOICE
        int leastLoadedIndex = findLeastLoadedWorker(workers);

        // Assign job
        workers[leastLoadedIndex].currentLoad++;

        // Optional extensions:
        // - weighted balancing using rating
        // - job tracking
        // - debug output
    }

    // After completion:
    // - Jobs are evenly distributed
    // - Load difference between workers is minimal
}
