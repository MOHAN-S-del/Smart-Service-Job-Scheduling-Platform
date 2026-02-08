// job_scheduler.h
// Header file for Job Scheduling using Greedy Algorithm
// Design and Analysis of Algorithms (DAA) Project

#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#include <vector>
using namespace std;

// Structure to represent a Job
struct Job {
    int jobId;      // Unique identifier for the job
    int deadline;   // Deadline by which job must be completed
    int profit;     // Profit earned if job is completed
    int priority;   // Priority level of the job (higher value = higher priority)
    
    // Constructor for easy initialization
    Job(int id = 0, int dl = 0, int pr = 0, int pri = 0) 
        : jobId(id), deadline(dl), profit(pr), priority(pri) {}
};

// Function declarations

/**
 * Schedules jobs using Greedy Algorithm to maximize profit
 * @param jobs: Vector of Job objects to be scheduled
 * @return: Vector of scheduled Job objects in optimal order
 * 
 * Algorithm approach:
 * - Sorts jobs by profit (descending order)
 * - Assigns each job to latest available time slot before deadline
 * - Maximizes total profit by selecting highest profit jobs first
 */
vector<Job> scheduleJobsGreedy(vector<Job>& jobs);

#endif // JOB_SCHEDULER_H
