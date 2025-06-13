#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 10;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    if (n > MAX) {
        cout << "Error: Maximum number of processes is " << MAX << ".\n";
        return 1;
    }

    int bt[MAX], at[MAX], wt[MAX], tat[MAX], pid[MAX];
    int start[MAX];

    for (int i = 0; i < n; ++i) {
        pid[i] = i + 1;
        cout << "Enter burst time for Process P" << pid[i] << ": ";
        cin >> bt[i];
        cout << "Enter arrival time for Process P" << pid[i] << ": ";
        cin >> at[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    start[0] = at[0];
    wt[0] = 0;
    tat[0] = bt[0];
    float total_wt = 0, total_tat = tat[0];

    for (int i = 1; i < n; ++i) {
        start[i] = max(at[i], start[i - 1] + bt[i - 1]);
        wt[i] = start[i] - at[i];
        tat[i] = wt[i] + bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "\nPID\tBT\tAT\tWT\tTAT\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << pid[i] << "\t" << bt[i] << "\t" << at[i] << "\t" << wt[i] << "\t" << tat[i] << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;

    return 0;
}
