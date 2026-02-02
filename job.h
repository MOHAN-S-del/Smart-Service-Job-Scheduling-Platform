/* job.h - Job structure for greedy job scheduling */

#ifndef JOB_H
#define JOB_H

/* Job structure for job sequencing with deadlines */
typedef struct {
    int jobId;      
    int deadline;   
    int profit;     
    int status;     /* 0=Pending, 1=Scheduled, 2=Missed */
} Job;

/* Function to initialize a job */
void initJob(Job* job, int id, int deadline, int profit);

#endif
