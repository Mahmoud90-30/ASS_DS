#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <climits>
#include <string>
using namespace std;

class Process {
public:
    int id,
        arrival_time,
        burst_time,
        remaining_time,
        completion_time,
        turnaround_time,
        waiting_time;

    Process(int id, int at, int bt) : 
        id(id),  
        arrival_time(at),
        burst_time(bt),
        remaining_time(bt),
        completion_time(0), 
        turnaround_time(0),
        waiting_time(0) {}

    bool isDone() { return remaining_time == 0; } 
    void calcTimes() 
    { turnaround_time = completion_time - arrival_time; waiting_time = turnaround_time - burst_time; }
    
    void print() {      
        cout << "P" << id << "\t\t"
            << completion_time << "\t\t"
            << turnaround_time << "\t\t"
            << waiting_time << "\n";
    }
};

class RoundRobinScheduler {
private:
    vector<Process> procs;
    queue<int> rq;
    vector<bool> inQ, done;
    int quantum, time, doneCount;

    void printQueue() {
        if (rq.empty()) { cout << "[ Empty ]\n"; return; }
        queue<int> tmp = rq;
        cout << "[ ";
        while (!tmp.empty()) {   
            cout << "P" << tmp.front();
            tmp.pop(); 
            if (!tmp.empty()) cout << ", ";
        }
        cout << " ]\n";
    }

    void addArrivals(int from, int to) {
        for (int i = 0; i < (int)procs.size(); i++)
            if (!done[i] && !inQ[i] && procs[i].arrival_time > from && procs[i].arrival_time <= to)
            { ا
                rq.push(procs[i].id); inQ[i] = true; 
            }
    }

    void jumpToNext() {
        int next = INT_MAX; 
        for (int i = 0; i < (int)procs.size(); i++)
            if (!done[i] && !inQ[i]) next = min(next, procs[i].arrival_time);
        time = next;
        for (int i = 0; i < (int)procs.size(); i++)
            if (!done[i] && !inQ[i] && procs[i].arrival_time <= time)  
            {
                rq.push(procs[i].id); inQ[i] = true;
            }
        printQueue();
    }

public:
    RoundRobinScheduler(int q) : quantum(q), time(0), doneCount(0) {}

    void addProcess(int id, int at, int bt) {
        procs.push_back(Process(id, at, bt));
        inQ.push_back(false);
        done.push_back(false);
    }
    void run() {
        int n = procs.size();
        for (int i = 0; i < n; i++)
            if (procs[i].arrival_time == 0) { rq.push(procs[i].id); inQ[i] = true; }

        cout << "\nQueue updates:\n"; 
        if (!rq.empty()) printQueue();

        while (doneCount < n) {
            if (rq.empty()) { jumpToNext(); continue; }
            int pid = rq.front(); rq.pop();
            int idx = pid - 1;
            int exec = min(procs[idx].remaining_time, quantum); 
            int prev = time;
            time += exec;
            procs[idx].remaining_time -= exec; 
            addArrivals(prev, time); 
            if (procs[idx].isDone()) { 
                procs[idx].completion_time = time;
                procs[idx].calcTimes();
                done[idx] = true; inQ[idx] = false; doneCount++;
            }
            else {
                rq.push(pid);
            }
            printQueue();
        }
    }

    void printResults() {
        int n = procs.size(), totalWt = 0;  
        cout << "\nProcess\t\tCompletion Time\t\tTurnaround Time\t\tWaiting Time\n";
        for (int i = 0; i < n; i++) { procs[i].print();
        totalWt += procs[i].waiting_time; 
        }
        cout << "\nAverage Waiting Time: " << (float)totalWt / n << "\n";
    }
};


int main() {
    int n, q;
    cout << "Time Quantum: "; cin >> q;
    cout << "Number of Processes: "; cin >> n;

    RoundRobinScheduler scheduler(q);
    for (int i = 1; i <= n; i++) {
        int at, bt;
        cout << "Arrival Time, Needed Time P" << i << ": "; cin >> at >> bt;
        scheduler.addProcess(i, at, bt);  
    }

    scheduler.run();
    scheduler.printResults();
    return 0;
}
