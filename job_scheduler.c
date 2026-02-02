/* job_scheduler.c - Implementation of greedy job scheduling algorithm */

#include <stdio.h>
#include <stdlib.h>
#include "job_scheduler.h"

/*
 * GREEDY JOB SCHEDULING ALGORITHM
 * 
 * Strategy:
 * 1. Sort all jobs by profit in descending order
 * 2. For each job, try to schedule it in the latest available slot before its deadline
 * 3. If no slot is available, mark the job as missed
 * 
 * Time Complexity: O(n log n) for sorting + O(n^2) for scheduling = O(n^2)
 *                  Can be optimized to O(n log n) using Union-Find
 * Space Complexity: O(n) for storing time slots
 */

/* Initialize a job with given values */
void initJob(Job* job, int id, int deadline, int profit) {
    job->jobId = id;
    job->deadline = deadline;
    job->profit = profit;
    job->status = 0; /* 0 = Pending */
}

/* Comparison function for sorting jobs by profit (descending) */
int compareByProfit(const void* a, const void* b) {
    Job* jobA = (Job*)a;
    Job* jobB = (Job*)b;
    return jobB->profit - jobA->profit; /* Descending order */
}

/* Sort jobs by profit in descending order */
void sortJobsByProfit(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compareByProfit);
}

/* Find maximum deadline among all jobs */
int findMaxDeadline(Job jobs[], int n) {
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }
    return maxDeadline;
}

/* Main greedy job scheduling algorithm */
void scheduleJobs(Job jobs[], int n) {
    /* Step 1: Sort jobs by profit in descending order */
    printf("\n=== GREEDY JOB SCHEDULING ===\n");
    printf("Sorting jobs by profit (descending order)...\n\n");
    sortJobsByProfit(jobs, n);
    
    /* Step 2: Find maximum deadline to create time slots */
    int maxDeadline = findMaxDeadline(jobs, n);
    
    /* Step 3: Create an array to track which job is scheduled in each time slot */
    /* -1 means the slot is free */
    int* timeSlots = (int*)malloc(maxDeadline * sizeof(int));
    for (int i = 0; i < maxDeadline; i++) {
        timeSlots[i] = -1; /* Initially all slots are free */
    }
    
    /* Step 4: Schedule jobs using greedy approach */
    printf("Scheduling jobs...\n");
    for (int i = 0; i < n; i++) {
        /* Try to find a free slot for this job before its deadline */
        /* Start from the latest possible slot (deadline - 1) and move backwards */
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (timeSlots[j] == -1) { /* Slot is free */
                timeSlots[j] = i; /* Schedule this job in slot j */
                jobs[i].status = 1; /* Mark as Scheduled */
                printf("Job %d scheduled in time slot %d (Profit: %d)\n", 
                       jobs[i].jobId, j + 1, jobs[i].profit);
                break;
            }
        }
        
        /* If no slot was found, mark as Missed */
        if (jobs[i].status == 0) {
            jobs[i].status = 2; /* Mark as Missed */
            printf("Job %d MISSED (Deadline: %d, Profit: %d)\n", 
                   jobs[i].jobId, jobs[i].deadline, jobs[i].profit);
        }
    }
    
    free(timeSlots);
}

/* Display scheduled jobs */
void displaySchedule(Job jobs[], int n) {
    printf("\n=== SCHEDULED JOBS ===\n");
    printf("%-10s %-12s %-10s %-12s\n", "Job ID", "Deadline", "Profit", "Status");
    printf("---------------------------------------------------\n");
    
    int scheduledCount = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].status == 1) { /* Scheduled */
            printf("%-10d %-12d %-10d Scheduled\n", 
                   jobs[i].jobId, jobs[i].deadline, jobs[i].profit);
            scheduledCount++;
        }
    }
    
    if (scheduledCount == 0) {
        printf("No jobs scheduled.\n");
    }
    
    printf("\n=== MISSED JOBS ===\n");
    printf("%-10s %-12s %-10s %-12s\n", "Job ID", "Deadline", "Profit", "Status");
    printf("---------------------------------------------------\n");
    
    int missedCount = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].status == 2) { /* Missed */
            printf("%-10d %-12d %-10d Missed\n", 
                   jobs[i].jobId, jobs[i].deadline, jobs[i].profit);
            missedCount++;
        }
    }
    
    if (missedCount == 0) {
        printf("No jobs missed.\n");
    }
}

/* Display individual job details */
void displayJob(Job job) {
    char* statusStr;
    switch (job.status) {
        case 0: statusStr = "Pending"; break;
        case 1: statusStr = "Scheduled"; break;
        case 2: statusStr = "Missed"; break;
        default: statusStr = "Unknown"; break;
    }
    
    printf("Job ID: %d, Deadline: %d, Profit: %d, Status: %s\n", 
           job.jobId, job.deadline, job.profit, statusStr);
}

/* Calculate total profit from scheduled jobs */
int calculateTotalProfit(Job jobs[], int n) {
    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].status == 1) { /* Scheduled */
            totalProfit += jobs[i].profit;
        }
    }
    return totalProfit;
}
