#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct process_struct
{
    int process_id;
    int arrivaltime;
    int bursttime;
    int completiontime, waitingtime, turnaroundtime, rt, start_time;
} processsturct[100];

int main()
{

    int n;
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0;
    ;
    cout << "Enter total number of processes: ";
    cin >> n;
    int sum_tat = 0, sum_wt = 0, sum_rt = 0, total_idle_time = 0, prev = 0, length_cycle;
    float cpu_utilization;
    int max_completion_time, min_arrival_time;

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> processsturct[i].arrivaltime;
        processsturct[i].process_id = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> processsturct[i].bursttime;
    }

    while (completed != n)
    {
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processsturct[i].arrivaltime <= current_time && is_completed[i] == false)
            {
                if (processsturct[i].bursttime < minimum)
                {
                    minimum = processsturct[i].bursttime;
                    min_index = i;
                }
                if (processsturct[i].bursttime == minimum)
                {
                    if (processsturct[i].arrivaltime < processsturct[min_index].arrivaltime)
                    {
                        minimum = processsturct[i].bursttime;
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            processsturct[min_index].start_time = current_time;
            processsturct[min_index].completiontime = processsturct[min_index].start_time + processsturct[min_index].bursttime;
            processsturct[min_index].turnaroundtime = processsturct[min_index].completiontime - processsturct[min_index].arrivaltime;
            processsturct[min_index].waitingtime = processsturct[min_index].turnaroundtime - processsturct[min_index].bursttime;
            processsturct[min_index].rt = processsturct[min_index].waitingtime;

            sum_tat += processsturct[min_index].turnaroundtime;
            sum_wt += processsturct[min_index].waitingtime;

            completed++;
            is_completed[min_index] = true;
            current_time = processsturct[min_index].completiontime;
            prev = current_time;
            is_first_process = false;
        }
    }

    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, processsturct[i].completiontime);
        min_arrival_time = min(min_arrival_time, processsturct[i].arrivaltime);
    }
    length_cycle = max_completion_time - min_arrival_time;

    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << processsturct[i].arrivaltime << "\t" << processsturct[i].bursttime << "\t\t" << processsturct[i].completiontime << "\t" << processsturct[i].turnaroundtime << "\t" << processsturct[i].waitingtime << "\t" << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;

    return 0;
}