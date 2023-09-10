#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define endl "\n"

class proc {
public:
    int id;
    int burstTime;
    int burstTimeRemaining;
    int ticket;
    int from;
    int to;
};

void print(int time, int id) {
    if (id == -1) {
        cout << "time: " << time + 1 << " id: -" << endl;
    }
    else {
        cout << "time: " << time + 1 << " id:" << id << endl;
    }
}

void giveticket(proc process[], int n) {
    // Calculate the total burst time
    int burstTotal = 0;
    for (int i = 0; i < n; i++) {
        burstTotal += process[i].burstTimeRemaining;
    }

    // Distribute tickets based on the burst time
    int given = 0;
    for (int i = 0; i < n; i++) {
        if (process[i].burstTimeRemaining == 0) {
            process[i].from=-1;
            process[i].to = -1;
            continue;
        }

        double ratio = (double)process[i].burstTimeRemaining / burstTotal;
        process[i].from = given;
        process[i].to = given + ratio * 100;
        process[i].ticket = process[i].to - process[i].from;
        given = process[i].to;
    }
}

int main() {
    int n = 3;
    proc process[n];
    process[0].burstTime = 2;
    process[1].burstTime = 1;
    process[2].burstTime = 5;

    for (int i = 0; i < n; i++) {
        process[i].id = i;
        process[i].burstTimeRemaining = process[i].burstTime;
    }
    giveticket(process, n);

    int burstTotal = 0;
    for (int i = 0; i < n; i++) {
        burstTotal += process[i].burstTime;
    }

    srand(time(0));
    for (int time = 0; time <burstTotal; time++) {
    	cout<<"time: "<<time+1<<"\tid:";
        int randomTicket = rand() % 100;
        // for(int i=0;i<n;i++){
        // 	cout<<i<<" "<<process[i].from<<" "<<process[i].to<<" "<< randomTicket<<endl;
        // }
        // cout<<endl;
        
        for (int i = 0; i < n; i++) {
            if (process[i].from <= randomTicket && randomTicket < process[i].to) {
                cout<<i<<endl;
                process[i].burstTimeRemaining--;
                giveticket(process, n);
                break;
            }
        }
    }
    cout<<endl;
    return 0;
}
