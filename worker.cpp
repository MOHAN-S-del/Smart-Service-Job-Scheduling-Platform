// worker.cpp
// Implementation of Worker Management Functions
// Design and Analysis of Algorithms (DAA) Project

#include "worker.h"
#include <iostream>
using namespace std;

/**
 * LOAD BALANCING CONCEPT:
 * 
 * Load balancing distributes jobs across multiple workers to:
 * - Maximize resource utilization
 * - Prevent worker overload
 * - Optimize system performance
 * - Ensure fair distribution of work
 * 
 * KEY METRICS:
 * - Current Load: Number of jobs assigned to worker
 * - Max Capacity: Maximum jobs worker can handle
 * - Available Capacity: maxCapacity - currentLoad
 * - Overloaded: currentLoad > maxCapacity (system stress)
 */

/**
 * Assigns a job to a worker by increasing their workload
 * @param worker: Reference to Worker object
 * @param jobCount: Number of jobs to assign (default = 1)
 * @return: true if assignment successful, false if worker at/over capacity
 * 
 * TIME COMPLEXITY: O(1) - constant time operation
 * 
 * GREEDY APPROACH:
 * - Check if worker has available capacity
 * - If yes, assign job and increment load
 * - If no, reject assignment to prevent overload
 */
bool assignJob(Worker& worker, int jobCount = 1) {
    // Validate input
    if (jobCount <= 0) {
        cout << "Error: Invalid job count (must be positive)" << endl;
        return false;
    }
    
    // Check if worker can accept the job(s)
    if (worker.currentLoad + jobCount <= worker.maxCapacity) {
        // Worker has capacity - assign the job(s)
        worker.currentLoad += jobCount;
        
        cout << "Worker " << worker.workerId 
             << ": Assigned " << jobCount << " job(s). "
             << "Load: " << worker.currentLoad << "/" << worker.maxCapacity 
             << " (" << worker.getLoadPercentage() << "%)" << endl;
        
        return true;
    } else {
        // Worker at/over capacity - cannot assign
        cout << "Worker " << worker.workerId 
             << ": Cannot assign " << jobCount << " job(s). "
             << "Current load: " << worker.currentLoad 
             << ", Max capacity: " << worker.maxCapacity << endl;
        
        return false;
    }
}

/**
 * Checks if a worker is overloaded (exceeds maximum capacity)
 * @param worker: Worker object to check
 * @return: true if overloaded (currentLoad > maxCapacity), false otherwise
 * 
 * TIME COMPLEXITY: O(1) - simple comparison
 * 
 * USE CASES:
 * - System health monitoring
 * - Alert generation for overloaded resources
 * - Load rebalancing trigger
 * - Performance optimization decisions
 */
bool isOverloaded(const Worker& worker) {
    bool overloaded = worker.currentLoad > worker.maxCapacity;
    
    if (overloaded) {
        int excess = worker.currentLoad - worker.maxCapacity;
        cout << "WARNING: Worker " << worker.workerId 
             << " is OVERLOADED by " << excess << " job(s)!" << endl;
        cout << "         Current Load: " << worker.currentLoad 
             << " | Max Capacity: " << worker.maxCapacity << endl;
    }
    
    return overloaded;
}

/**
 * Removes/completes a job from worker's load
 * @param worker: Reference to Worker object
 * @param jobCount: Number of jobs completed (default = 1)
 * @return: true if removal successful, false if invalid
 * 
 * TIME COMPLEXITY: O(1)
 * 
 * Used when jobs are completed and worker capacity is freed
 */
bool completeJob(Worker& worker, int jobCount = 1) {
    // Validate input
    if (jobCount <= 0) {
        cout << "Error: Invalid job count (must be positive)" << endl;
        return false;
    }
    
    // Check if worker has enough jobs to complete
    if (worker.currentLoad >= jobCount) {
        worker.currentLoad -= jobCount;
        
        cout << "Worker " << worker.workerId 
             << ": Completed " << jobCount << " job(s). "
             << "Remaining load: " << worker.currentLoad << "/" 
             << worker.maxCapacity << endl;
        
        return true;
    } else {
        cout << "Error: Worker " << worker.workerId 
             << " has only " << worker.currentLoad 
             << " job(s), cannot complete " << jobCount << endl;
        
        return false;
    }
}

/**
 * Displays detailed information about a worker
 * @param worker: Worker object to display
 * 
 * Shows: ID, current load, capacity, availability, utilization
 */
void displayWorkerInfo(const Worker& worker) {
    cout << "\n--- Worker " << worker.workerId << " Info ---" << endl;
    cout << "Current Load:     " << worker.currentLoad << endl;
    cout << "Max Capacity:     " << worker.maxCapacity << endl;
    cout << "Available Slots:  " << worker.getAvailableCapacity() << endl;
    cout << "Utilization:      " << worker.getLoadPercentage() << "%" << endl;
    cout << "Can Accept Job:   " << (worker.canAcceptJob() ? "Yes" : "No") << endl;
    cout << "Status:           ";
    
    if (isOverloaded(worker)) {
        cout << "OVERLOADED" << endl;
    } else if (worker.currentLoad == worker.maxCapacity) {
        cout << "AT CAPACITY" << endl;
    } else if (worker.currentLoad == 0) {
        cout << "IDLE" << endl;
    } else {
        cout << "ACTIVE" << endl;
    }
    
    cout << "-------------------------" << endl;
}

/**
 * Finds the worker with minimum load (for load balancing)
 * @param workers: Vector of Worker objects
 * @return: Index of worker with minimum current load
 * 
 * TIME COMPLEXITY: O(n) where n = number of workers
 * 
 * GREEDY STRATEGY: Always assign to least loaded worker
 * This ensures balanced distribution and prevents bottlenecks
 */
int findMinLoadWorker(const Worker workers[], int numWorkers) {
    if (numWorkers <= 0) {
        return -1;
    }
    
    int minIndex = 0;
    int minLoad = workers[0].currentLoad;
    
    // Find worker with minimum current load
    for (int i = 1; i < numWorkers; i++) {
        if (workers[i].currentLoad < minLoad) {
            minLoad = workers[i].currentLoad;
            minIndex = i;
        }
    }
    
    return minIndex;
}

/**
 * Calculates total load across all workers
 * @param workers: Array of Worker objects
 * @param numWorkers: Number of workers
 * @return: Total jobs assigned across all workers
 * 
 * TIME COMPLEXITY: O(n)
 */
int calculateTotalLoad(const Worker workers[], int numWorkers) {
    int totalLoad = 0;
    
    for (int i = 0; i < numWorkers; i++) {
        totalLoad += workers[i].currentLoad;
    }
    
    return totalLoad;
}

/**
 * Calculates average load across all workers
 * @param workers: Array of Worker objects
 * @param numWorkers: Number of workers
 * @return: Average load per worker
 * 
 * Used to measure load balance quality
 */
double calculateAverageLoad(const Worker workers[], int numWorkers) {
    if (numWorkers <= 0) {
        return 0.0;
    }
    
    int totalLoad = calculateTotalLoad(workers, numWorkers);
    return (double)totalLoad / numWorkers;
}

/**
 * ALGORITHM APPLICATIONS:
 * 
 * 1. OPERATING SYSTEMS:
 *    - CPU scheduling across cores
 *    - Thread pool management
 * 
 * 2. DISTRIBUTED SYSTEMS:
 *    - Server load balancing
 *    - Database query distribution
 * 
 * 3. CLOUD COMPUTING:
 *    - Virtual machine allocation
 *    - Container orchestration (Kubernetes)
 * 
 * 4. PROJECT MANAGEMENT:
 *    - Team workload distribution
 *    - Resource allocation optimization
 */
