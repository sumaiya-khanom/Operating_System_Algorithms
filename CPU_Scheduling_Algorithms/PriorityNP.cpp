
#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[n], at[n], bt[n], priority[n];
    int wt[n], tat[n];
    bool completed[n] = {false};


    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        cout << "Enter Arrival Time, Burst Time and Priority "
             << "for Process " << pid[i] << ": ";

        cin >> at[i] >> bt[i] >> priority[i];
    }

    int time = 0;
    int completedCount = 0;

    float total_wt = 0;
    float total_tat = 0;
    float total_burst_time = 0;

    cout << "\nGantt Chart: ";

    while (completedCount < n) {

        int selected = -1;
        int highest_priority = 999999;


        for (int i = 0; i < n; i++) {

            if (!completed[i] && at[i] <= time) {

                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    selected = i;
                }
            }
        }


        if (selected == -1) {
            time++;
        }

        else {


            wt[selected] = time - at[selected];

            tat[selected] = wt[selected] + bt[selected];

            time += bt[selected];

            completed[selected] = true;
            completedCount++;


            total_wt += wt[selected];
            total_tat += tat[selected];
            total_burst_time += bt[selected];


            cout << "| P" << pid[selected] << " ";
        }
    }

    cout << "|\n";


    cout << "\nProcess\tAT\tBT\tPriority\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {

        cout << "P" << pid[i]
             << "\t" << at[i]
             << "\t" << bt[i]
             << "\t" << priority[i]
             << "\t\t" << wt[i]
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
         << throughput
         << " processes/unit time" << endl;

    cout << "CPU Utilization = "
         << cpu_utilization << "%" << endl;

    return 0;
}
