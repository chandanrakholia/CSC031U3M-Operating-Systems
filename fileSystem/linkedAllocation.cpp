#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int n=256;
vector<unsigned int>directory;
class metaData{
public:
    char name;
    int prev,next;
    metaData(){
        name='*';
        prev=-1;
        next=-1;
    }
};
vector<metaData>disk(n);
void print(vector<metaData>&disk){
    for(int i=0;i<256;i+=16){
        for(int j=i;j<i+16;j++){
            cout<<disk[j].name;
        }
        cout<<endl;
    }
}
int creation(char name, int size){
    int prev=-1;
    vector<int>next;
    int p=1;
    int ans=-1;
    for(int i=0;i<n && size;i++){
        if(disk[i].name=='*'){
            size--;
            disk[i].name=name;
            disk[i].prev=prev;
            prev=i;
            next.push_back(i);
            if(ans==-1){
                ans=i;
            }
        }
    }
    if(next.size()<=1) return ans;
    for(int i=0;i<n;i++){
        if(disk[i].name==name){
            disk[i].next=next[p++];
            if(p>=next.size()) return ans;
        }
    }
    return ans;
}
void deallocate(int i){
    disk[i].name='*';
    disk[i].prev=-1;
    disk[i].next=-1;
}
int main(){
    ifstream file("input.dat");
    string name;
    char request;
    int size;
    while(file>>name>>request>>size) {
        if(name=="-1"){
            break;
        }
		cout<<name<<" "<<request<<" "<<size<<endl;
        if(request=='C'){
            int first=creation(name[0],size);
            unsigned int nameOfFile=int(name[0]);
            nameOfFile=nameOfFile<<16;
            unsigned int sizeOfFile=size;
            sizeOfFile=sizeOfFile<<8;
            unsigned int firstBlock=first;
            unsigned int bitMask=nameOfFile+sizeOfFile+firstBlock;
            directory.push_back(bitMask);
            print(disk);
        }
        else if(request=='M'){
            for(int i=0;i<directory.size();i++){
                char fileName=char(directory[i]>>16);
                int sizeOfFile=directory[i]<<16;
                sizeOfFile=sizeOfFile>>24;
                int firstblock=directory[i]<<24;
                firstblock=firstblock>>24;
                if(fileName==int(name[0])){
                    if(sizeOfFile>=size){
                        int count=sizeOfFile-size;
                        int temp=firstblock;
                        while(disk[temp].next!=-1){
                            temp=disk[temp].next;
                        }
                        while(count--){
                            int nx=temp;
                            temp=disk[temp].prev;
                            deallocate(nx);
                            disk[temp].next=-1;
                        }
                    }
                    else{
                        int count=size-sizeOfFile;
                        int temp=firstblock;
                        while(disk[temp].next!=-1){
                            temp=disk[temp].next;
                        }
                        int prev=temp;
                        vector<int>next;
                        for(int i=0;i<n;i++){
                            if( count && disk[i].name=='*'){
                                count--;
                                disk[i].name=name[0];
                                disk[i].prev=prev;
                                prev=i;
                                next.push_back(i);
                            }
                        }
                        if(next.size()<=1){
                            break;
                        }
                        temp=firstblock;
                        while(disk[temp].next!=-1){
                            temp=disk[temp].next;
                        }
                        temp=disk[temp].prev;
                        while(!next.empty()){
                            disk[temp].next=next.back();
                            next.pop_back();
                        }
                    }
                    unsigned int newSizeOfFile=size;
                    newSizeOfFile=newSizeOfFile<<8;
                    unsigned int oldSizeOfFile=directory[i] && 0x00f0;
                    directory[i]=directory[i]-oldSizeOfFile+newSizeOfFile;
                }
            }
            print(disk);
        }
        else if(request=='D'){
            for(int i=0;i<n;i++){
                if(disk[i].name==int(name[0])){
                    deallocate(i);
                }
            }
            for(int i=0;i<directory.size();i++){
                char fileName=char(directory[i]>>16);
                int sizeOfFile=directory[i]<<16;
                sizeOfFile=sizeOfFile>>24;
                int firstblock=directory[i]<<24;
                firstblock=firstblock>>24;
                if(fileName==name[0]){
                    directory.erase(directory.begin()+i);
                }
            }
            print(disk);
        }
    }
    return 0;
}
//use print(disk) to print disk of 256 block in matrix of 16x16;