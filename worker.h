// worker.h
// Header file for Worker/Resource Management in Job Scheduling
// Design and Analysis of Algorithms (DAA) Project

#ifndef WORKER_H
#define WORKER_H

/**
 * Structure to represent a Worker/Resource in the scheduling system
 * Used for load balancing and resource allocation algorithms
 */
struct Worker {
    int workerId;       // Unique identifier for the worker
    int currentLoad;    // Current number of jobs/tasks assigned to worker
    int maxCapacity;    // Maximum number of jobs worker can handle
    
    /**
     * Constructor for easy initialization
     * @param id: Worker identifier
     * @param load: Initial current load (default = 0)
     * @param capacity: Maximum capacity (default = 10)
     */
    Worker(int id = 0, int load = 0, int capacity = 10)
        : workerId(id), currentLoad(load), maxCapacity(capacity) {}
    
    /**
     * Checks if worker can accept more jobs
     * @return: true if currentLoad < maxCapacity, false otherwise
     */
    bool canAcceptJob() const {
        return currentLoad < maxCapacity;
    }
    
    /**
     * Gets available capacity for the worker
     * @return: Number of additional jobs worker can handle
     */
    int getAvailableCapacity() const {
        return maxCapacity - currentLoad;
    }
    
    /**
     * Calculates load percentage
     * @return: Percentage of capacity currently utilized (0-100)
     */
    int getLoadPercentage() const {
        if (maxCapacity == 0) return 0;
        return (currentLoad * 100) / maxCapacity;
    }
};

#endif // WORKER_H
