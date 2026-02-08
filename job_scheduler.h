/*
 * job_scheduler.h
 * Function declarations for Greedy Job Scheduling Algorithm
 * Design and Analysis of Algorithms (DAA) Project
 */

#ifndef JOB_SCHEDULER_H
#define JOB_SCHEDULER_H

#include <vector>
#include "job.h"

using namespace std;

/**
 * Schedule jobs using greedy algorithm to maximize profit
 * Greedy choice: select highest-profit job first
 */
void scheduleJobs(vector<Job>& jobs);

/**
 * Display scheduled and missed jobs
 */
void displaySchedule(const vector<Job>& jobs);

/**
 * Display details of a single job
 */
void displayJob(const Job& job);

/**
 * Calculate total profit from scheduled jobs
 */
int calculateTotalProfit(const vector<Job>& jobs);

#endif // JOB_SCHEDULER_H
