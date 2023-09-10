#include<bits/stdc++.h>
using namespace std;

//FCFS scheduling algorithm implementation.
int main(){
    int n;
    cout<<"enter number of processes: ";
    cin>>n;
    int burstTime[n];
    for(int i=0;i<n;i++){
        cout<<"enter burst time for P["<<i<<"]: ";
        cin>>burstTime[i];
    }
    int waitTime[n],turnAroundTime[n];
    for(int i=0;i<n;i++){
        if(i==0) waitTime[i]=0;
        else{
            waitTime[i]=waitTime[i-1]+burstTime[i-1];
        }
        turnAroundTime[i]=waitTime[i]+burstTime[i];
    }
    cout<<endl;
    cout<<endl;
    cout<<"process"<<"    "<<"waitTime"<<"  "<<"turnAroundTime"<<endl;
    for(int i=0;i<n;i++){
        cout<<"P["<<i+1<<"]"<<"        "<<waitTime[i]<<"          "<<turnAroundTime[i]<<endl;
    }
    cout<<"---"<<"        "<<"---"<<"         "<<"---"<<endl;
    cout<<"av."<<"         "<<(double)accumulate(waitTime,waitTime+n,0)/n<<"        "<<(double)accumulate(turnAroundTime,turnAroundTime+n,0)/n<<endl;
    return 0;
}