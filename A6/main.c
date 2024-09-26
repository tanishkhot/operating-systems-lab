#include<bits/stdc++.h>
using namespace std;
 
bool find(vector<int> &memory, int page){
    for(auto x : memory){
        if(x == page){
            return true;
        }
    }
    return false;
}
 
void fifo(vector<int> &pr, int n, int pfs){
    vector<int> memory(pfs, -1);
    vector<vector<int>> frames;
    float hit = 0, miss = 0;
    int idx = 0;
 
    for(int page : pr){
        if(find(memory, page)){
            hit++;
        }
        else{
            memory[idx] = page;
            miss++;
            idx = (idx + 1) % pfs;
        }
        frames.push_back(memory);
    }
    cout<<endl;
    for(auto frame: frames){
        for(auto x: frame){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
 
    float missRatio = miss / (miss + hit);
    float hitRatio = hit / (miss + hit);
 
    cout<<"Page Fault: "<< miss << endl;
    cout<<"Miss Ratio: "<<missRatio<<endl;
    cout<<"Hit Ratio: "<<hitRatio<<endl;
 
 
}
 
int main(){
    int pfs; // PageFrameSize
    int n; // PageReferenceSize 
    cin>>n;
 
    vector<int> pr(n); // PageReference
 
    for(int i = 0; i < n; i++){
        cin>>pr[i];
    }
 
    cin>>pfs;
 
    fifo(pr, n, pfs);
 
    return 0;
}
 
/*
size
Page Reference
no of page frame
 
Testcase 1:
14
7 0 1 2 0 3 0 4 2 3 0 3 2 3
4
 
7
1 3 0 3 5 6 3
3
 
*/