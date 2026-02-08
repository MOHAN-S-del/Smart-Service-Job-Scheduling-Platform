/*
 * job.h
 * Job structure for Greedy Job Scheduling
 * Design and Analysis of Algorithms (DAA) Project
 */

#ifndef JOB_H
#define JOB_H

/**
 * Job structure
 * Represents a job with deadline and profit
 */
struct Job {
    int jobId;      // Unique job identifier
    int deadline;   // Deadline before which job must be completed
    int profit;     // Profit earned if job is completed
    int status;     // 0 = Pending, 1 = Scheduled, 2 = Missed
};

/**
 * Initialize a job with given values
 */
void initJob(Job& job, int id, int deadline, int profit);

#endif // JOB_H
