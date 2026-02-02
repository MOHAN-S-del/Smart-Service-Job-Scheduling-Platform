/* job_scheduler.h - Function prototypes for greedy job scheduling */

#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#include "job.h"

/* Schedule jobs using greedy algorithm to maximize profit */
void scheduleJobs(Job jobs[], int n);

/* Sort jobs by profit in descending order (helper function) */
void sortJobsByProfit(Job jobs[], int n);

/* Find maximum deadline among all jobs */
int findMaxDeadline(Job jobs[], int n);

/* Display scheduled jobs */
void displaySchedule(Job jobs[], int n);

/* Display job details */
void displayJob(Job job);

/* Calculate total profit from scheduled jobs */
int calculateTotalProfit(Job jobs[], int n);

#endif