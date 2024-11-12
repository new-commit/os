#include <bits/stdc++.h>
using namespace std;

void findAvgTime(int arrivalTime[], int burstTime[], int priority[], int n) {
    deque<int> readyQueue; 
    int time = 0, completed = 0;
    int totalWaitTime = 0, totalTurnAroundTime = 0;

    vector<int> waitTime(n), turnAroundTime(n), startTime(n, -1), completionTime(n);
    vector<int> remainingTime(burstTime, burstTime + n);  // Track remaining burst time for preemption
    vector<bool> isCompleted(n, false);

    int i = 0; // Index to track unprocessed processes

    while (completed < n) {
        // Add all processes that have arrived by current time
        while (i < n && arrivalTime[i] <= time) {
            readyQueue.push_back(i);
            i++;
        }

        // Sort the ready queue by priority (lower number means higher priority)
        sort(readyQueue.begin(), readyQueue.end(), [&](int a, int b) {
            return priority[a] > priority[b];
        });

        if (!readyQueue.empty()) {
            int current = readyQueue.front();
            readyQueue.pop_front();

            if (startTime[current] == -1) {
                startTime[current] = time;  // Set start time for the first execution
            }

            // Process one unit of time
            remainingTime[current] -= 1;
            time++;

            // If the process finishes
            if (remainingTime[current] == 0) {
                completionTime[current] = time;
                turnAroundTime[current] = completionTime[current] - arrivalTime[current];
                waitTime[current] = turnAroundTime[current] - burstTime[current];

                totalWaitTime += waitTime[current];
                totalTurnAroundTime += turnAroundTime[current];

                isCompleted[current] = true;
                completed++;
            }

            // If the process is not completed, push it back to the ready queue
            if (!isCompleted[current] && remainingTime[current] > 0) {
                readyQueue.push_back(current);
            }
        } else {
            // If no process is ready, advance time to the next arrival
            if (i < n) time = arrivalTime[i];
        }
    }

    // Output process details and average times
    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int j = 0; j < n; j++) {
        cout << "P" << (j + 1) << "\t\t" << arrivalTime[j] << "\t\t" << burstTime[j] << "\t\t" << priority[j]
             << "\t\t" << startTime[j] << "\t\t" << completionTime[j] << "\t\t" << turnAroundTime[j] << "\t\t" << waitTime[j] << endl;
    }
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitTime / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnAroundTime / n << endl;
}

int main() {
    int n;
    cout << "Enter the total number of processes: ";
    cin >> n;

    int arrivalTime[n], burstTime[n], priority[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival time, Burst time, and Priority respectively for Process " << (i + 1) << ": ";
        cin >> arrivalTime[i] >> burstTime[i] >> priority[i];
    }

    findAvgTime(arrivalTime, burstTime, priority, n);

    return 0;
}
