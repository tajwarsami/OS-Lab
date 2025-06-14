#include <bits/stdc++.h>
using namespace std;

struct Process {
    string name;
    vector<int> max_demand, allocation, remaining;
};

bool isSafe(vector<int> available, vector<Process> processes) {
    string order = "";
    int m = available.size(), n = processes.size();
    vector<bool> done(n, false);

    while (true) {
        bool progress = false;
        for (int i = 0; i < n; i++) {
            if (done[i]) continue;

            bool canProceed = true;
            for (int j = 0; j < m; j++) {
                if (processes[i].remaining[j] > available[j]) {
                    canProceed = false;
                    break;
                }
            }

            if (canProceed) {
                for (int j = 0; j < m; j++)
                    available[j] += processes[i].allocation[j];
                order += processes[i].name + " ";
                done[i] = true;
                progress = true;
            }
        }
        if (!progress) break;
    }

    for (bool status : done) {
        if (!status) return false;
    }

    cout << order << "\n";
    return true;
}

int main() {
    int resourceCount;
    cin >> resourceCount;

    vector<int> available(resourceCount);
    for (int &r : available) cin >> r;

    int processCount;
    cin >> processCount;

    vector<Process> proc(processCount);

    for (int i = 0; i < processCount; i++) {
        proc[i].max_demand.resize(resourceCount);
        proc[i].allocation.resize(resourceCount);
        proc[i].remaining.resize(resourceCount);

        cin >> proc[i].name;
        for (int j = 0; j < resourceCount; j++) cin >> proc[i].allocation[j];
        for (int j = 0; j < resourceCount; j++) {
            cin >> proc[i].max_demand[j];
            proc[i].remaining[j] = proc[i].max_demand[j] - proc[i].allocation[j];
        }
    }

    if (isSafe(available, proc)) {
        cout << "System is currently in a safe condition\n";
    } else {
        cout << "Unsafe state! Possible deadlock detected\n";
    }

    // Resource Request Handling
    int reqProcess;
    cin >> reqProcess;

    vector<int> request(resourceCount);
    for (int i = 0; i < resourceCount; i++) {
        cin >> request[i];
        if (request[i] > proc[reqProcess].remaining[i]) {
            cout << "Request exceeds declared need. Rejected!";
            return 0;
        }
        if (request[i] > available[i]) {
            cout << "Not enough resources available. Request cannot be granted!";
            return 0;
        }
    }

    // Try allocating requested resources temporarily
    for (int i = 0; i < resourceCount; i++) {
        available[i] -= request[i];
        proc[reqProcess].allocation[i] += request[i];
        proc[reqProcess].remaining[i] -= request[i];
    }

    if (isSafe(available, proc)) {
        cout << "Resources have been safely allocated.\n";
    } else {
        cout << "Unsafe state after request. Rolling back allocation.\n";
        for (int i = 0; i < resourceCount; i++) {
            available[i] += request[i];
            proc[reqProcess].allocation[i] -= request[i];
            proc[reqProcess].remaining[i] += request[i];
        }
    }
}
