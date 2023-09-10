#include <iostream>
#include <queue>
using namespace std;

class proc
{
public:
    int id;
    int arrivalTime;
    int burstTime;
    int burstTimeRemaining;
};

void print(int time, int id)
{
    if (id == -1)
    {
        cout << "time: " << time+1 << " id: "
             << "idle" << endl;
    }
    else
    {
        cout << "time: " << time+1 << " id: " << id +1<< endl;
    }
}

int main()
{

    /*
    Testcase-1
    5 3
    1 10
    2 2
    2 4
    4 9
    5 1
    */

   /*
   Testcase-2
    2 2
    1 5
    2 10
   */
    int n;
    cout<<"enter number of process: ";
    cin >> n;
    int timer;
    cout<<"enter timer value: ";
    cin >> timer;
    proc process[n];
    for (int i = 0; i < n; i++)
    {
        process[i].id = i;
        cout<<"enter arrivalTime and burstTime for process["<<i<<"]: ";
        cin >> process[i].arrivalTime;
        cin >> process[i].burstTime;
        process[i].burstTimeRemaining = process[i].burstTime;
    }
    cout<<endl;
    int remaining = n;
    queue<proc> queue;
    int globalInd = 0;
    for (int time = 0; remaining != 0; time++)
    {
        while (globalInd < n && process[globalInd].arrivalTime == time)
        {
            queue.push(process[globalInd]);
            globalInd++;
        }
        if (queue.empty())
        {
            print(time, -1);
        }
        if (!queue.empty())
        {
            if (process[queue.front().id].burstTimeRemaining <= timer)
            {
                int executionTime = process[queue.front().id].burstTimeRemaining;
                for (int i = 0; i < executionTime; i++)
                {
                    while (globalInd < n && process[globalInd].arrivalTime == time + 1)
                    {
                        queue.push(process[globalInd]);
                        globalInd++;
                    }
                    print(time + i, queue.front().id);
                }
                time += executionTime - 1;
                queue.pop();
                remaining--;
            }
            else
            {
                int oldTime = time;
                for (int i = 0; i < timer; i++)
                {
                    while (globalInd < n && process[globalInd].arrivalTime == time + i)
                    {
                        queue.push(process[globalInd]);
                        globalInd++;
                    }
                    print(time + i, queue.front().id);
                }
                time += timer - 1;
                process[queue.front().id].burstTimeRemaining -= timer;
                queue.push(process[queue.front().id]);
                queue.pop();
            }
        }
    }
    return 0;
}
