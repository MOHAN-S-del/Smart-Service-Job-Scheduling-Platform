/*
 * load_balancer.c
 * 
 * Implementation of Load Balancing using Greedy Algorithm
 * Design and Analysis of Algorithms (DAA) Project
 */

#include "load_balancer.h"

/**
 * GREEDY ALGORITHM IMPLEMENTATION
 * 
 * WHY THIS IS GREEDY:
 * - Makes locally optimal choice at each step (assigns job to least loaded worker)
 * - Never reconsiders previous decisions
 * - Doesn't look ahead to future jobs
 * - Hopes that local optimum leads to global optimum
 * 
 * GREEDY CHOICE PROPERTY:
 * At each step, choosing the worker with minimum load is the best immediate
 * decision for maintaining balance across all workers.
 */

/**
 * Find Least Loaded Worker
 * 
 * Core of the greedy selection strategy.
 * 
 * ALGORITHM:
 * 1. Assume first worker has minimum load
 * 2. Compare with all other workers
 * 3. Update minimum when a lighter-loaded worker is found
 * 4. Return index of worker with absolute minimum load
 * 
 * TIME COMPLEXITY: O(m) where m = number of workers
 * - Single pass through all workers
 * - Linear scan to find minimum
 * 
 * SPACE COMPLEXITY: O(1)
 * - Only uses constant extra space (minIndex, minLoad)
 */
int findLeastLoadedWorker(const Worker workers[], int workerCount) {
    int minIndex = 0;  // Start with first worker as candidate
    int minLoad = workers[0].currentLoad;
    int i;
    
    // Linear search for worker with minimum current load
    // This is the GREEDY SELECTION step
    for (i = 1; i < workerCount; i++) {
        if (workers[i].currentLoad < minLoad) {
            minLoad = workers[i].currentLoad;
            minIndex = i;  // Update to new minimum
        }
    }
    
    return minIndex;
}

/**
 * Balance Load using Greedy Algorithm
 * 
 * GREEDY STRATEGY:
 * For each job, assign it to the worker who currently has the least load.
 * This ensures no worker gets overwhelmed while others sit idle.
 * 
 * HOW IT PREVENTS WORKER OVERLOAD:
 * - Continuously monitors each worker's current load
 * - Always selects the least busy worker for the next job
 * - Distributes jobs evenly across all available workers
 * - Self-balancing: if a worker gets too many jobs, they won't be selected
 *   until their load drops below others
 * 
 * ALGORITHM STEPS:
 * 1. For each job (from 1 to jobCount):
 *    a. Find worker with minimum current load (greedy choice)
 *    b. Assign job to that worker
 *    c. Increment that worker's load counter
 *    d. Repeat for next job
 * 
 * TIME COMPLEXITY ANALYSIS:
 * - Outer loop: O(n) where n = jobCount
 * - Inner operation (findLeastLoadedWorker): O(m) where m = number of workers
 * - Total: O(n × m) = O(jobs × workers)
 * 
 * SPACE COMPLEXITY: O(1)
 * - No additional data structures needed
 * - Modifies worker loads in-place
 * 
 * GREEDY VS OPTIMAL:
 * This greedy approach gives near-optimal results for load balancing.
 * It may not always produce the absolute optimal solution (especially if
 * jobs have different processing times), but it's efficient and performs
 * well in practice.
 * 
 * @param workers - Array of workers (modified in-place)
 * @param workerCount - Number of workers in the array
 * @param jobCount - Total number of jobs to distribute
 */
void balanceLoadGreedy(Worker workers[], int workerCount, int jobCount) {
    int job;
    int leastLoadedIndex;
    
    // Assign jobs one by one using greedy approach
    for (job = 1; job <= jobCount; job++) {
        // GREEDY CHOICE: Find worker with minimum current load
        leastLoadedIndex = findLeastLoadedWorker(workers, workerCount);
        
        // Assign the job to the selected worker
        workers[leastLoadedIndex].currentLoad++;
        
        // NOTE: We could add additional logic here to:
        // - Consider worker ratings for weighted balancing
        // - Track which specific jobs are assigned to which worker
        // - Print assignment details for debugging
        // But for the basic greedy algorithm, we just increment the load
    }
    
    // After this function completes:
    // - All jobs are distributed
    // - Load is balanced across workers (difference <= 1 for equal-length jobs)
    // - No worker is significantly overloaded compared to others
}
