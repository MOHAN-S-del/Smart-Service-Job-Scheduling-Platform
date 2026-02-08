// deadline_manager.h
// Header file for Deadline Management in Job Scheduling
// Design and Analysis of Algorithms (DAA) Project

#ifndef DEADLINE_MANAGER_H
#define DEADLINE_MANAGER_H

#include "job_scheduler.h"
#include <vector>
using namespace std;

/**
 * DEADLINE TYPES:
 * 
 * HARD DEADLINE:
 * - Jobs must be completed before or at the deadline
 * - Missing the deadline results in complete loss of value/profit
 * - No partial credit or late submission allowed
 * - Example: Flight departure, medical surgery, contract deadline
 * 
 * SOFT DEADLINE:
 * - Jobs can be completed after the deadline with reduced profit/penalty
 * - Late completion still provides some value
 * - Profit decreases as delay increases
 * - Example: Assignment submission with late penalty, product delivery
 */

// Function declarations

/**
 * Checks if a job has missed its deadline
 * @param job: The Job object to check
 * @param currentTime: Current time slot/unit
 * @return: true if deadline is missed, false otherwise
 * 
 * A job misses deadline if: currentTime > job.deadline
 */
bool hasDeadlineMissed(const Job& job, int currentTime);

/**
 * Checks multiple jobs for missed deadlines
 * @param jobs: Vector of Job objects to check
 * @param currentTime: Current time slot/unit
 * @return: Vector of jobs that have missed their deadlines
 */
vector<Job> getMissedDeadlineJobs(const vector<Job>& jobs, int currentTime);

/**
 * Reassigns expired/missed deadline jobs to new time slots
 * @param expiredJobs: Vector of jobs that missed their deadlines
 * @param scheduledJobs: Vector of currently scheduled jobs
 * @return: Vector of reassigned jobs with updated deadlines
 * 
 * Strategy:
 * - Can extend deadlines for soft deadline jobs
 * - May reduce profit as penalty for late completion
 * - Attempts to fit jobs in available slots after original deadline
 */
vector<Job> reassignExpiredJobs(vector<Job>& expiredJobs, 
                                const vector<Job>& scheduledJobs);

/**
 * Calculates penalty for missing a deadline
 * @param job: The Job object
 * @param delay: Number of time units past deadline
 * @return: Reduced profit after applying penalty
 * 
 * Used for soft deadline scenarios where late completion is allowed
 */
int calculatePenalty(const Job& job, int delay);

/**
 * Checks if a deadline is hard (no late submission) or soft (late allowed)
 * @param job: The Job object to check
 * @return: true if hard deadline, false if soft deadline
 * 
 * Note: In this implementation, we can use priority field to indicate:
 * - priority >= 5: Hard deadline (no late submission)
 * - priority < 5: Soft deadline (late submission with penalty)
 */
bool isHardDeadline(const Job& job);

#endif // DEADLINE_MANAGER_H
