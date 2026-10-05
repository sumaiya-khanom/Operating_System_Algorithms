
#include <iostream>
using namespace std;

int main() {
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], at[n], bt[n];
    int remaining[n], wt[n], tat[n];

    // Input
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        cout << "Enter Arrival Time and Burst Time "
             << "for Process " << pid[i] << ": ";

        cin >> at[i] >> bt[i];

        remaining[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int time = 0;
    int completedCount = 0;

    float total_wt = 0;
    float total_tat = 0;
    float total_burst_time = 0;

    bool visited[n] = {false};

    // Ready Queue
    int queue[1000];
    int front = 0;
    int rear = 0;

    cout << "\nGantt Chart: ";

    while (completedCount < n) {

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {

            if (at[i] <= time &&
                remaining[i] > 0 &&
                !visited[i]) {

                queue[rear++] = i;
                visited[i] = true;
            }
        }

        // If queue is empty, CPU is idle
        if (front == rear) {
            time++;
            continue;
        }

        // Take process from front
        int current = queue[front++];

        cout << "| P" << pid[current] << " ";

        // Execute for Time Quantum or remaining time
        int executionTime;

        if (remaining[current] > quantum)
            executionTime = quantum;
        else
            executionTime = remaining[current];

        remaining[current] -= executionTime;
        time += executionTime;

        // Add newly arrived processes during execution
        for (int i = 0; i < n; i++) {

            if (at[i] <= time &&
                remaining[i] > 0 &&
                !visited[i]) {

                queue[rear++] = i;
                visited[i] = true;
            }
        }

        // Process completed
        if (remaining[current] == 0) {

            completedCount++;

            // Turnaround Time
            tat[current] = time - at[current];

            // Waiting Time
            wt[current] = tat[current] - bt[current];

            total_wt += wt[current];
            total_tat += tat[current];

            total_burst_time += bt[current];

        } else {

            // Process not completed
            // Put it back into the queue
            queue[rear++] = current;
        }
    }

    cout << "|\n";

    // Process Table
    cout << "\nProcess\tAT\tBT\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {

        cout << "P" << pid[i]
             << "\t" << at[i]
             << "\t" << bt[i]
             << "\t" << wt[i]
             << "\t" << tat[i] << "\n";
    }

    // Average Waiting Time
    float avg_wt = total_wt / n;

    // Average Turnaround Time
    float avg_tat = total_tat / n;

    // Throughput
    float throughput = (float)n / time;

    // CPU Utilization
    float cpu_utilization =
        (total_burst_time / time) * 100;

    // Final Results
    cout << "\n===== Performance Metrics =====\n";

    cout << "Average Waiting Time = "
         << avg_wt << endl;

    cout << "Average Turnaround Time = "
         << avg_tat << endl;

    cout << "Throughput = "
         << throughput
         << " processes/unit time" << endl;

    cout << "CPU Utilization = "
         << cpu_utilization << "%" << endl;

    return 0;
}
