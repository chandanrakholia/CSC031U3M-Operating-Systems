#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int n=256;
vector<unsigned int>directory;
class metaData{
public:
    char name;
    int next;
    vector<int>Indexes;
    metaData(){
        name='*';
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
    int p=1;
    int ans=-1;
    int indexNode=-1;
    for(int i=0;i<n && size;i++){
        if(disk[i].name=='*'){
            if(indexNode==-1){
                disk[i].name='#';
                indexNode=i;
                if(ans==-1){
                    ans=i;
                }
            }
            else{
                size--;
                disk[i].name=name;
                disk[indexNode].Indexes.push_back(i);
            }
        }
    }
    vector<int>v=disk[indexNode].Indexes;
    for(int i=0;i<v.size();i++){
        disk[v[i]].next=v[i+1];
    }
    return ans;
}
void deallocate(int i){
    disk[i].name='*';
    disk[i].next=-1;
    disk[i].Indexes.clear();
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
            unsigned int indexBlock=creation(name[0],size);
            unsigned int nameOfFile=int(name[0]);
            nameOfFile=nameOfFile<<16;
            unsigned int bitMask=nameOfFile+indexBlock;
            directory.push_back(bitMask);
            print(disk);
        }
        else if(request=='M'){
            for(int i=0;i<directory.size();i++){
                char fileName=char(directory[i]>>16);
                unsigned int indexBlock=directory[i]<<24;
                indexBlock=indexBlock>>24;
                if(fileName==name[0]){
                    int sizeOfFile=disk[indexBlock].Indexes.size();
                    if(sizeOfFile>=size){
                        vector<int>&v=disk[indexBlock].Indexes;
                        disk[v[size-1]].next=-1;
                        for(int i=size;i<v.size();i++){
                            deallocate(v[i]);
                        }
                        while(v.size()>size){
                            v.pop_back();
                        }
                    }
                    else{
                        int count=size-disk[indexBlock].Indexes.size();
                        int temp=disk[indexBlock].Indexes.back();
                        for(int i=0;i<n;i++){
                            if( count && disk[i].name=='*'){
                                count--;
                                disk[i].name=name[0];
                                disk[indexBlock].Indexes.push_back(i);
                            }
                        }
                        vector<int>&v=disk[indexBlock].Indexes;
                        for(int i=0;i<v.size();i++){
                            disk[v[i]].next=v[i+1];
                        }
                    }
                }
            }
            print(disk);
        }
        else if(request=='D'){
            for(int i=0;i<directory.size();i++){
                char fileName=char(directory[i]>>16);
                unsigned int indexBlock=directory[i]<<24;
                indexBlock=indexBlock>>24;
                if(fileName==name[0]){
                    int tm=indexBlock;
                    for(int j=0;j<disk[tm].Indexes.size();j++){
                        deallocate(disk[tm].Indexes[j]);
                    }
                    deallocate(tm);
                    directory.erase(directory.begin()+i);
                    break;
                }
            }
            print(disk);
        }
    }
    return 0;
}
//use print(disk) to print disk of 256 block in matrix of 16x16;