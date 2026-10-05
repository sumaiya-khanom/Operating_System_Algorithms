#include<iostream>
using namespace std;

int main()
{
    int n;
    cout<<"Enter number of Processes : ";
    cin>>n;

    int pid[n],at[n],bt[n],wt[n],tat[n];
    for(int i=0;i<n;i++){
        pid[i] = i+1;

    cout<<"Enter Arrival Time and Burst Time for process "<<pid[i]<<": ";
    cin>>at[i]>>bt[i];
}

for(int i=0;i<n-1;i++)
{
    for(int j=0;j<n-i-1;j++){
        if (at[j]>at[j+1]){
        swap(at[j], at[j+1]);
        swap(bt[j],bt[j+1]);
        swap(pid[j],pid[j+1]);
        }
    }
}

int time = 0;

float total_wt =0;
float total_tat = 0;

cout<<"\nGantt Chart: ";

for(int i=0;i<n;i++)
{
    if(time < at[i])
        time = at[i];
    wt[i] = time - at[i];
    tat[i] = wt[i] + bt[i];
    time += bt[i];
    total_wt += wt[i];
    total_tat += tat[i];
    cout <<"| P"<<pid[i]<<" ";
}
cout <<"|\n";

cout<<"\nProcess\tAT\tBT\tTAT\n";

  for(int i =0;i<n;i++){
    cout << "P" << pid[i]
         << "\t" << at[i]
         << "\t" << bt[i]
         << "\t" << wt[i]
         << "\t" << tat[i] << "\n";
  }

float avg_wt = total_wt / n;
float avg_tat = total_tat / n;
float throughput = (float)n / time;
float total_burst_time = 0;
for(int i=0;i<n;i++)
{
    total_burst_time += bt[i];
}
float cpu_utilization = (total_burst_time / time)*100;

cout << "\n===== Performance Matrics =====\n";
cout << "Average waiting Time = "
     << avg_wt << endl;
cout << "Average Turnaround Time = "
     << avg_tat << endl;
cout << "Throughput = "
     << throughput << " processes/unit time" << endl;
cout << "CPU Utilization = "
     << cpu_utilization << "%" << endl;

return 0;
}
