#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template<typename T>
void exchange(vector<T> &arr, int i, int j){
    auto t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

template<typename T>
void MaxHeap(vector<T> &arr, int i, int len){
    if(i>=len) return;

    auto largest = i;
    auto left = 2*i+1, right = 2*i+2;
    if(left<len and arr[left] > arr[largest]) largest = left;
    if(right<len and arr[right] > arr[largest]) largest = right;
    if(largest != i) {
        exchange(arr, i, largest);
        MaxHeap(arr, largest, len);
    }
}

template<typename T>
void BuildHeap(vector<T> &arr){
    int n = arr.size();
    for(int i=n/2-1; i>=0; i--){
        MaxHeap(arr, i, n);
    }
}

template<typename T>
void HeapSort(vector<T> &arr){
    if(arr.size() == 0) return;
    int n = arr.size();
    BuildHeap(arr);
    for(int i=n-1;i>=1;i--){
        exchange(arr, 0, i);
        MaxHeap(arr, 0, i);
    }
}

int main(){
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
