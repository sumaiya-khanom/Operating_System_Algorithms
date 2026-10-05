#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], at[n], bt[n];
    int remaining[n], wt[n], tat[n];


    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        cout << "Enter Arrival Time and Burst Time for Process "
             << pid[i] << ": ";

        cin >> at[i] >> bt[i];

        remaining[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    int time = 0;
    int completedCount = 0;

    float total_wt = 0;
    float total_tat = 0;
    float total_burst_time = 0;

    cout << "\nGantt Chart: ";

    while (completedCount < n) {

        int shortest = -1;
        int min_remaining = 999999;


        for (int i = 0; i < n; i++) {

            if (at[i] <= time && remaining[i] > 0) {

                if (remaining[i] < min_remaining) {
                    min_remaining = remaining[i];
                    shortest = i;
                }
            }
        }


        if (shortest == -1) {

            time++;

        } else {


            cout << "| P" << pid[shortest] << " ";

            remaining[shortest]--;
            time++;


            if (remaining[shortest] == 0) {

                completedCount++;


                tat[shortest] = time - at[shortest];


                wt[shortest] =
                    tat[shortest] - bt[shortest];


                total_wt += wt[shortest];
                total_tat += tat[shortest];

                total_burst_time += bt[shortest];
            }
        }
    }

    cout << "|\n";


    cout << "\nProcess\tAT\tBT\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {

        cout << "P" << pid[i]
             << "\t" << at[i]
             << "\t" << bt[i]
             << "\t" << wt[i]
             << "\t" << tat[i] << "\n";
    }


    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    float throughput = (float)n / time;
    float cpu_utilization =
        (total_burst_time / time) * 100;


    cout << "\n===== Performance Metrics =====\n";

    cout << "Average Waiting Time = "
         << avg_wt << endl;

    cout << "Average Turnaround Time = "
         << avg_tat << endl;

    cout << "Throughput = "
         << throughput << " processes/unit time" << endl;

    cout << "CPU Utilization = "
         << cpu_utilization << "%" << endl;

    return 0;
}
