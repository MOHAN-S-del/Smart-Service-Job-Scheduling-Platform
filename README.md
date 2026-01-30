#include <bits/stdc++.h>
using namespace std;

struct Worker {
    int id;
    int distance;
    int rating;
    int price;
    int jobsAssigned;
};

struct Job {
    int id;
    int deadline;
    int profit;
};

/* ---------- Sorting Workers (Ranking) ---------- */
bool compareWorkers(Worker a, Worker b) {
    if (a.rating != b.rating)
        return a.rating > b.rating;     // higher rating first
    if (a.price != b.price)
        return a.price < b.price;       // lower price first
    return a.distance < b.distance;     // nearer first
}

/* ---------- Greedy Job Scheduling ---------- */
void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return a.profit > b.profit;
    });

    int maxDeadline = 0;
    for (auto j : jobs)
        maxDeadline = max(maxDeadline, j.deadline);

    vector<int> slot(maxDeadline + 1, -1);
    int totalProfit = 0;

    cout << "\nScheduled Jobs:\n";
    for (auto j : jobs) {
        for (int t = j.deadline; t > 0; t--) {
            if (slot[t] == -1) {
                slot[t] = j.id;
                totalProfit += j.profit;
                cout << "Job " << j.id << " scheduled at time " << t << endl;
                break;
            }
        }
    }

    cout << "Total Profit: " << totalProfit << endl;
}

/* ---------- Nearest Worker Selection ---------- */
Worker findNearestWorker(vector<Worker>& workers) {
    Worker nearest = workers[0];
    for (auto w : workers) {
        if (w.distance < nearest.distance)
            nearest = w;
    }
    return nearest;
}

/* ---------- Load Balancing ---------- */
Worker selectLeastLoadedWorker(vector<Worker>& workers) {
    Worker selected = workers[0];
    for (auto w : workers) {
        if (w.jobsAssigned < selected.jobsAssigned)
            selected = w;
    }
    return selected;
}

int main() {
    /* Workers Data */
    vector<Worker> workers = {
        {1, 5, 4, 300, 1},
        {2, 3, 5, 400, 0},
        {3, 8, 3, 250, 2}
    };

    /* Jobs Data */
    vector<Job> jobs = {
        {1, 2, 100},
        {2, 1, 50},
        {3, 3, 70}
    };

    /* Worker Ranking */
    sort(workers.begin(), workers.end(), compareWorkers);

    cout << "Ranked Workers:\n";
    for (auto w : workers) {
        cout << "Worker " << w.id
             << " | Rating: " << w.rating
             << " | Price: " << w.price
             << " | Distance: " << w.distance << endl;
    }

    /* Nearest Worker */
    Worker nearest = findNearestWorker(workers);
    cout << "\nNearest Worker ID: " << nearest.id << endl;

    /* Job Scheduling */
    jobScheduling(jobs);

    /* Load Balancing */
    Worker balanced = selectLeastLoadedWorker(workers);
    cout << "\nLeast Loaded Worker ID: " << balanced.id << endl;

    return 0;
}
# Smart-Service-Job-Scheduling-Platform
Designed a greedy algorithm-based job scheduling system to optimize worker allocation, deadlines, and service efficiency.
