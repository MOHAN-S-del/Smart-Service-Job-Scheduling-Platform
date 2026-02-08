/*
 * load_balancer_demo.cpp
 *
 * Demonstration of Greedy Load Balancing Algorithm
 * Shows how the algorithm distributes jobs fairly across workers
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include "load_balancer.h"

using namespace std;

#define NEW_JOBS 15

// Helper function to print a line of characters
void printLine(char c, int length) {
    for (int i = 0; i < length; i++) {
        cout << c;
    }
    cout << endl;
}

// Helper function to print worker status
void printWorkerStatus(const vector<Worker>& workers, const string& title) {

    cout << "\n" << title << endl;
    printLine('=', 60);

    cout << left
         << setw(15) << "Worker ID"
         << setw(20) << "Current Load"
         << setw(15) << "Rating" << endl;

    printLine('-', 60);

    for (const auto& w : workers) {
        cout << left
             << setw(15) << w.workerId
             << setw(20) << w.currentLoad
             << setw(15) << fixed << setprecision(2) << w.rating
             << endl;
    }

    printLine('=', 60);
}

// Calculate and display load di
