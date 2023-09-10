#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class proc {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int burstTimeRemaining;
    int restTime;

    proc() {
        restTime = -1;
    }
};

void print(int time, int id) {
    if (id == -1) {
        cout << "time: " << time + 1 << " id: -" << endl;
    }
    else {
        cout << "time: " << time + 1 << " id:" << id << endl;
    }
}

void moveProcesses(queue<int> &sourceQueue, queue<int> &targetQueue, proc process[]) {
    while (!sourceQueue.empty()) {
        int processId = sourceQueue.front();
        sourceQueue.pop();
        targetQueue.push(processId);
        // Reset restTime when moving processes between queues
        process[processId].restTime = -1;
    }
}

int main() {
    int n=3;
    proc process[n];
    int timer1 = 2;
    int timer2 = 5;
    int timer3 = 10;
    int mlfqTime = 20;
    process[0].arrivalTime = 1;
    process[0].burstTime = 3;
    process[1].arrivalTime = 2;
    process[1].burstTime = 5;
    process[2].arrivalTime = 2;
    process[2].burstTime = 2;

    for (int i = 0; i < n; i++) {
        process[i].id = i;
        process[i].burstTimeRemaining = process[i].burstTime;
    }

    vector<queue<int> > q(3);
    int remaining = n;
    int globalInd = 0;
    int prev = -1;
    for (int time = 0; remaining != 0; time++)
    {
        // cout<<time+1<<endl;
        while (globalInd < n && process[globalInd].arrivalTime == time)
        {
            q[0].push(process[globalInd].id);
            globalInd++;
        }

        if (time!=0 && time%mlfqTime==0) {
            moveProcesses(q[1], q[0], process);
            moveProcesses(q[2], q[0], process);
            prev=-1;
        }
        // cout<<q[0].size()<<endl;
        if (!q[0].empty() && (prev == 0 || prev == -1))
        {
            int currId = q[0].front();
            proc &current = process[currId];

            if (current.restTime == 0)
            {
                q[0].pop();
                q[1].push(currId);
                current.restTime = -1;
                prev=-1;
                time--;
            }
            else if (current.restTime == -1)
            {
                print(time, currId);
                current.burstTimeRemaining--;
                current.restTime = min(timer1 - 1, current.burstTimeRemaining);
            }
            else
            {
                print(time, currId);
                current.burstTimeRemaining--;
                current.restTime--;
            }

            if (current.burstTimeRemaining == 0)
            {
                q[0].pop();
                remaining--;
                prev = -1;
            }
        }
        else if (!q[1].empty() && (prev == 1 || prev == -1))
        {
            int currId = q[1].front();
            proc &current = process[currId];
            // cout<<process[currId].burstTimeRemaining<<endl;
            // cout<<process[currId].burstTimeRemaining<<endl;
            if (current.restTime == 0)
            {
                q[1].pop();
                q[2].push(currId);
                current.restTime = -1;
                prev=-1;
                time--;
            }
            else if (current.restTime == -1)
            {
                print(time, currId);
                current.burstTimeRemaining--;
                current.restTime = min(timer2 - 1, current.burstTimeRemaining);
                prev = 1;
            }
            else
            {
                print(time, currId);
                current.burstTimeRemaining--;
                current.restTime--;
                prev = 1;
            }

            if (current.burstTimeRemaining == 0)
            {
                q[1].pop();
                remaining--;
                prev = -1;
            }
        }
        else if (!q[2].empty() && (prev == 2 || prev == -1))
        {
            // cout<<q[2].front().burstTimeRemaining<<endl;
            int currId = q[2].front();
            proc &current = process[currId];
            // cout<<current.burstTimeRemaining<<endl;
            if (current.restTime == 0)
            {
                q[2].pop();
                q[2].push(currId);
                
                current.restTime = -1;
                prev=-1;
                time--;
                
            }
            else if (current.restTime == -1)
            {
                print(time, currId);
                current.burstTimeRemaining--;
                current.restTime = min(timer3 - 1, current.burstTimeRemaining);
                prev = 2;
                
            }
            else
            {
                print(time, currId);
                current.burstTimeRemaining--;
                current.restTime--;
                prev = 2;
                
            }

            if (current.burstTimeRemaining == 0)
            {
                q[2].pop();
                remaining--;
                prev = -1;
                
            }
            // cout<<q[2].size()<<endl;
        }
        else
        {
            print(time, -1);
        }
    }

    return 0;
}
