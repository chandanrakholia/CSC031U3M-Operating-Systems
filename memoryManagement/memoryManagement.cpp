#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int n=500;
int total;
vector<pair<int,int>>all(n,pair<int,int>(0,0));
queue<pair<int,pair<int,int>>>q;
int first=1;
int nextfitptr=0;
void printall(){
    int i=0;
    for(auto it: all){
        cout<<i++<<" ";
        cout<<it.first<<" "<<it.second<<endl;
    }
}
void timer(){
    bool flag=false;
    for(int i=0;i<n;i++){
        if(all[i].first==first){
            all[i].second--;
            if(all[i].second==0){
                all[i].first=0;
                flag=true;
            }
        }
    }
    if(flag){
        first++;
    }
}
int findptrff(int size) {
    int ptr1=-1,ptr2=-1;
    for(int i=0;i<n;i++){
        if(all[i].first==0){
            if(ptr1==-1){
                ptr1=i;
            }
            ptr2=i;
            if(ptr2-ptr1+1>=size){
                return ptr1;
            }
        }
        else{
            ptr1=-1;
        }
    }
    return -1;
}
int findptrbf(int size){
    int ptr1=-1,ptr2=-1;
    vector<pair<int,int>>block;
    bool flag=false;
    for(int i=0;i<n;i++){
        if(all[i].first==0){
            if(ptr1==-1){
                ptr1=i;
            }
            ptr2=i;
            if(ptr2-ptr1+1>=size){
                if(flag){
                    block.pop_back();
                }
                block.push_back({ptr2-ptr1+1,ptr1});
                flag=true;
                // return ptr1;
            }
        }
        else{
            flag=false;
            ptr1=-1;
        }
    }
    if(!block.empty()){
        sort(block.begin(),block.end());
        return block[0].second;
    }
    return -1;
}
int findptrwf(int size){
    int ptr1=-1,ptr2=-1;
    vector<pair<int,int>>block;
    bool flag=false;
    for(int i=0;i<n;i++){
        if(all[i].first==0){
            if(ptr1==-1){
                ptr1=i;
            }
            ptr2=i;
            if(ptr2-ptr1+1>=size){
                if(flag){
                    block.pop_back();
                }
                block.push_back({ptr2-ptr1+1,ptr1});
                flag=true;
            }
        }
        else{
            flag=false;
            ptr1=-1;
        }
    }
    if(!block.empty()){
        sort(block.begin(),block.end());
        return block[block.size()-1].second;
    }
    return -1;
}
int findptrnf(int size){
    int ptr1=-1,ptr2=-1;
    for(int i=nextfitptr;i<n;i++){
        if(all[i].first==0){
            if(ptr1==-1){
                ptr1=i;
            }
            ptr2=i;
            if(ptr2-ptr1+1>=size){
                nextfitptr = (ptr2 + 1) % n;
                return ptr1;
            }
        }
        else{
            ptr1=-1;
        }
    }
    for(int i=0;i<nextfitptr;i++){
        if(all[i].first==0){
            if(ptr1==-1){
                ptr1=i;
            }
            ptr2=i;
            if(ptr2-ptr1+1>=size){
                nextfitptr = (ptr2 + 1) % n;
                return ptr1;
            }
        }
        else{
            ptr1=-1;
        }
    }
    return -1;
}
void memoryManagement(string str="ff"){
    while(!q.empty()){
        // printall();
        auto front=q.front();
        int id=q.front().first;
        int size=q.front().second.first;
        int exTime=q.front().second.second;
        int ptr;
        if(str=="ff"){
            ptr=findptrff(size);
        }
        else if(str=="bf"){
            ptr=findptrbf(size);
        }
        else if(str=="wf"){
            ptr=findptrwf(size);
        }
        else if(str=="nf"){
            ptr=findptrnf(size);
        }
        if(ptr==-1){
            // printall();
            timer();
            continue;
        }
        else{
            q.pop();
            for(int i=0;i<size;i++){
                all[ptr+i].first=id;
                all[ptr+i].second=exTime;
            }
        }
    }
    printall();
}
int main(){
    //for first fit, use ff in argument, in line number 143
    //for worst fit, use wf in argument, in line number 143
    //for best fit, use bf in argument, in line number 143
    //for next fit, use nf in argument, in line number 143

    ifstream file("req.txt");
    int size,exTime;
    int id=1;
    while(file>>size>>exTime) {
        if(size==-1){
            break;
        }
        total=id;
        q.push({id++,{size,exTime}});
    }
    memoryManagement();
    return 0;
}