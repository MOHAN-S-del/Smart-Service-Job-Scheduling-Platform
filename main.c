/* main.c - Main program to test greedy job scheduling algorithm */

#include <stdio.h>
#include "job_scheduler.h"

int main() {
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║     GREEDY JOB SCHEDULING WITH DEADLINES          ║\n");
    printf("║           Design & Analysis of Algorithms         ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    
    /* Sample job data */
    /* Format: Job ID, Deadline, Profit */
    int n = 7; /* Number of jobs */
    
    Job jobs[] = {
        {1, 2, 100, 0},  /* Job 1: Deadline=2, Profit=100 */
        {2, 1, 19, 0},   /* Job 2: Deadline=1, Profit=19 */
        {3, 2, 27, 0},   /* Job 3: Deadline=2, Profit=27 */
        {4, 1, 25, 0},   /* Job 4: Deadline=1, Profit=25 */
        {5, 3, 15, 0},   /* Job 5: Deadline=3, Profit=15 */
        {6, 3, 50, 0},   /* Job 6: Deadline=3, Profit=50 */
        {7, 2, 40, 0}    /* Job 7: Deadline=2, Profit=40 */
    };
    
    /* Display initial job list */
    printf("\n=== INITIAL JOB LIST ===\n");
    printf("%-10s %-12s %-10s %-12s\n", "Job ID", "Deadline", "Profit", "Status");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-12d %-10d Pending\n", 
               jobs[i].jobId, jobs[i].deadline, jobs[i].profit);
    }
    
    /* Execute greedy job scheduling algorithm */
    scheduleJobs(jobs, n);
    
    /* Display final schedule */
    displaySchedule(jobs, n);
    
    /* Calculate and display total profit */
    int totalProfit = calculateTotalProfit(jobs, n);
    printf("\n=== SUMMARY ===\n");
    printf("Total Profit Earned: %d\n", totalProfit);
    
    /* Additional test case - uncomment to run */
    /*
    printf("\n\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║              TEST CASE 2                          ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    
    int n2 = 5;
    Job jobs2[] = {
        {1, 4, 70, 0},
        {2, 2, 60, 0},
        {3, 4, 50, 0},
        {4, 3, 40, 0},
        {5, 1, 30, 0}
    };
    
    printf("\n=== INITIAL JOB LIST ===\n");
    printf("%-10s %-12s %-10s %-12s\n", "Job ID", "Deadline", "Profit", "Status");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < n2; i++) {
        printf("%-10d %-12d %-10d Pending\n", 
               jobs2[i].jobId, jobs2[i].deadline, jobs2[i].profit);
    }
    
    scheduleJobs(jobs2, n2);
    displaySchedule(jobs2, n2);
    
    int totalProfit2 = calculateTotalProfit(jobs2, n2);
    printf("\n=== SUMMARY ===\n");
    printf("Total Profit Earned: %d\n", totalProfit2);
    */
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║           Program Execution Complete              ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    
    return 0;
}
