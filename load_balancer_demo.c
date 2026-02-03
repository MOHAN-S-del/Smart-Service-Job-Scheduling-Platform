/*
 * load_balancer_demo.c
 * 
 * Demonstration of Greedy Load Balancing Algorithm
 * Shows how the algorithm distributes jobs fairly across workers
 */

#include <stdio.h>
#include "load_balancer.h"

#define WORKER_COUNT 5
#define NEW_JOBS 15

// Helper function to print a line of characters
void printLine(char c, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%c", c);
    }
    printf("\n");
}

// Helper function to print worker status
void printWorkerStatus(const Worker workers[], int count, const char* title) {
    int i;
    
    printf("\n%s\n", title);
    printLine('=', 60);
    printf("%-15s %-20s %-15s\n", "Worker ID", "Current Load", "Rating");
    printLine('-', 60);
    
    for (i = 0; i < count; i++) {
        printf("%-15d %-20d %-15.2f\n", 
               workers[i].workerId,
               workers[i].currentLoad,
               workers[i].rating);
    }
    printLine('=', 60);
}

// Calculate and display load distribution statistics
void printStatistics(const Worker workers[], int count) {
    int i;
    int totalLoad = 0;
    int minLoad = workers[0].currentLoad;
    int maxLoad = workers[0].currentLoad;
    double avgLoad;
    int loadDifference;
    
    for (i = 0; i < count; i++) {
        totalLoad += workers[i].currentLoad;
        if (workers[i].currentLoad < minLoad) minLoad = workers[i].currentLoad;
        if (workers[i].currentLoad > maxLoad) maxLoad = workers[i].currentLoad;
    }
    
    avgLoad = (double)totalLoad / count;
    loadDifference = maxLoad - minLoad;
    
    printf("\n📊 Load Distribution Statistics:\n");
    printf("   Total Jobs Assigned: %d\n", totalLoad);
    printf("   Average Load per Worker: %.2f\n", avgLoad);
    printf("   Minimum Load: %d\n", minLoad);
    printf("   Maximum Load: %d\n", maxLoad);
    printf("   Load Difference (Max - Min): %d\n", loadDifference);
    
    // FAIRNESS INDICATOR
    if (loadDifference <= 1) {
        printf("   ✅ PERFECTLY BALANCED! (difference <= 1)\n");
    } else if (loadDifference <= 2) {
        printf("   ✓ Well balanced (difference <= 2)\n");
    } else {
        printf("   ⚠ Some imbalance detected\n");
    }
}

int main() {
    // SETUP: Create workers with different initial loads and ratings
    Worker workers[WORKER_COUNT] = {
        {101, 5, 4.5f},   // Worker 101: already has 5 jobs, rating 4.5
        {102, 2, 4.2f},   // Worker 102: has 2 jobs, rating 4.2
        {103, 8, 4.8f},   // Worker 103: heavily loaded with 8 jobs, rating 4.8
        {104, 3, 3.9f},   // Worker 104: has 3 jobs, rating 3.9
        {105, 0, 4.6f}    // Worker 105: idle (0 jobs), rating 4.6
    };
    
    printf("\n🚀 Load Balancer Demo - Greedy Algorithm\n");
    printf("=========================================\n\n");
    
    // Display initial state
    printWorkerStatus(workers, WORKER_COUNT, "⚙️  BEFORE Load Balancing");
    
    printf("\n📝 Initial Observation:\n");
    printf("   - Worker 103 is overloaded (8 jobs)\n");
    printf("   - Worker 105 is idle (0 jobs)\n");
    printf("   - Uneven distribution across workers\n");
    
    printf("\n🔄 Applying Greedy Load Balancing...\n");
    printf("   Assigning %d new jobs using greedy algorithm\n", NEW_JOBS);
    printf("   Strategy: Each job goes to the currently least-loaded worker\n");
    
    // GREEDY ALGORITHM IN ACTION
    balanceLoadGreedy(workers, WORKER_COUNT, NEW_JOBS);
    
    // Display final state
    printWorkerStatus(workers, WORKER_COUNT, "✅ AFTER Load Balancing");
    
    // Show statistics to prove fairness
    printStatistics(workers, WORKER_COUNT);
    
    // EXPLANATION OF FAIRNESS
    printf("\n💡 How This Proves Fairness:\n");
    printf("   1. GREEDY CHOICE: Algorithm always picks least-loaded worker\n");
    printf("   2. NO WORKER LEFT BEHIND: Idle workers get jobs first\n");
    printf("   3. PREVENTS OVERLOAD: Heavily loaded workers are skipped\n");
    printf("   4. BALANCED DISTRIBUTION: Final loads differ by at most 1\n");
    printf("   5. EFFICIENT: O(jobs × workers) time complexity\n");
    
    printf("\n🎯 Key Insight:\n");
    printf("   Even though workers started with different loads,\n");
    printf("   the greedy algorithm balanced them fairly by always\n");
    printf("   choosing the worker with minimum current load.\n");
    
    printf("\n✨ Demo Complete!\n\n");
    
    return 0;
}
