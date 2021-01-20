#include "Solution.cc"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;


int main(){
    int size;
    cin>>size;

    vector<int> l4 = vector<int>(size, 0);
    for(int i=0;i<size;i++) l4[i] = rand();
    vector<int> l5 = vector<int>(l4);
    vector<int> l6 = vector<int>(l4);

    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    sort(l5.begin(), l5.end());
    auto stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"sytem sorted time cost: "<<stop - start<<endl;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    HeapSort(l6);
    stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"Heap sorted time cost: "<<stop - start<<endl;

    for(int i=0;i<size; i++) if(l5[i] != l6[i]) cout<<"not equal"<<endl;
    return 0;

    vector<int> l3 = vector<int>(size, 0);
    for(int i=0;i<size;i++) l3[i] = rand();
    cout<<"time cost: "<<stop - start<<endl;
    return 0;


    auto t = time(nullptr);
    cout<<t<<endl;
    return 0;

    int len = 1000;
    vector<int> l = vector<int>(len, 0);
    for(int i=0;i<len;i++) l[i] = rand();
    vector<int> l0 = vector<int>(l);
    vector<int> l1 = vector<int>(l);
    l0[0] = 9;
    l1[0] = 1;
    cout<<l0[0]<<endl;
    cout<<l1[0]<<endl;
    return 0;

    HeapSort(l);
    for(auto i: l) cout<<i<<" "<<endl;;

    return 0;

    string line;
    while(getline(cin, line)){
        istringstream is(line);
        int n;
        vector<int> arr;
        while(is>>n) arr.push_back(n);
        for(auto i: arr) cout<<i<<" ";
        cout<<endl;
        HeapSort(arr);
        for(auto i: arr) cout<<i<<" ";
        cout<<endl<<"------"<<endl;
    }
    return 0;
}
