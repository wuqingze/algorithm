#include "Solution.cc"
#include "PriorityQueue.cc"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

template<typename T>
void test00(){
    T *arr = (T *) malloc(sizeof(T) *100);
    arr[0].apple = 1;
}

void test01_priorityqueue(){
    PriorityQueue<int> l;

    for(int i=0;i<10;i++) l.insert(rand()%10);
    while(!l.empty()){
        cout<<l.top()<<" ";
    }
    cout<<endl;
}

void test02_priorityqueue(int size){
    PriorityQueue<int> l(size);

    for(int i=0;i<size;i++){
        int t = rand()%size;
        cout<<t<<" ";
        l.insert(t);
    }
    cout<<endl<<"-----"<<endl;

    while(!l.empty()){
        cout<<l.top()<<endl;
    }
}

void test03_priorityqueue_exception(){
    PriorityQueue<int> l;

    for(int i=0;i<10;i++) l.insert(rand()%10);
    while(1){
        try{
            cout<<l.top()<<" ";
        }catch(const char *msg){
            cerr<<msg<<endl;
            break;
        }
    }
    cout<<endl;
}

int main(){
    test03_priorityqueue_exception();
    return 0;

    int n;
    cin>>n;
    test02_priorityqueue(n);
    return 0;

    test01_priorityqueue();
    return 0;

    int *l7 = (int *)  malloc(sizeof(int) *100);
    l7[0] = 0;
    l7[1] = 1;
    l7[2] = 2;
    l7[3] = 3;
    l7[4] = 4;

    for(int i=0;i<5;i++)cout<<l7[i]<<" ";
    cout<<endl;
    return 0;

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
