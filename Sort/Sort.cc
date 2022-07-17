#include <vector>
#include <iostream>
#include <functional>
#include <time.h>
#include <stdlib.h>

using namespace std;

template<typename T>
void traverse(vector<T> &l, int &j){
    for(int i=0;i<l.size();i++){
        if(i<j){
            cout<<" <TR><TD PORT=\""+to_string(i)+"\" BGCOLOR=\"gray\">"+to_string(l[i])+"</TD></TR>"<<endl;
        }else{
            cout<<" <TR><TD PORT=\""+to_string(i)+"\" >"+to_string(l[i])+"</TD></TR>"<<endl;
        }
    }
}

template<typename T>
void traverse(vector<T> &l, int i, int j){
    cout<<"t"+to_string(i)+" [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">"<<endl;
    traverse(l, i);
    cout<<"</TABLE>>];"<<endl;
    cout<<"t"+to_string(i)+":"+to_string(i)+" -> t"+to_string(i)+":"+to_string(j)+" [dir=both];"<<endl;
}

template<typename T, typename F>
void selection_sort(vector<T> &l, F less){
    int n = l.size();
    if(n == 0) return;
    cout<<"digraph{ node [shape=plaintext] edge [style=dashed] "<<endl;
    for(int i=0;i<n;i++){
        int mn = i;
        for(int j=i;j<n;j++){
            if(less(l[j], l[mn])) mn = j;
        }
        traverse(l, i, mn);
        swap(l[i], l[mn]);
    }
    cout<<"}"<<endl;
}

template<typename T>
void selection_sort(vector<T> &l){
    selection_sort(l, [](const T &o1, const T &o2){ return o1<o2;});
}

template<typename T, typename F>
void bubble_sort(vector<T> &l, F less){
    int n = l.size();
    if(n<2) return ;

    int j=n;
    while(j>1){
        int i=0;
        while(i<j-1){
            if(less(l[i+1], l[i])){
                swap(l[i], l[i+1]);
            }
            i += 1;
        }
        j -= 1;
    }
}

template<typename T>
void bubble_sort(vector<T> &l){
    bubble_sort(l, [](const T&o1, const T&o2){return o1<o2;});
}

template<typename T, typename F>
void insert_sort(vector<T> &l, F less){
    int n = l.size();
    if(n<2) return;
    int i = -1;
    while(i<n-1){
        int j=i+1;
        while(j>0 and less(l[j], l[j-1])){
            swap(l[j-1], l[j]);
            j -= 1;
        }
        i += 1;
    }
}

template<typename T>
void insert_sort(vector<T> &l){
    insert_sort(l, [](const T&o1, const T&o2){ return o1<o2;});
}

template<typename T,typename F>
void merge_sort(vector<T> &l, F less, int i, int j){
    if(i>=j) return;
    if(i==j-1){
        if(less(l[j], l[i])) swap(l[i],l[j]);
        return;
    }
    int mid = i+(j-i)/2;
    merge_sort(l, less, i, mid);
    merge_sort(l, less, mid+1, j);
    vector<T> temp = vector<T>(j-i+1);
    int k1 = i;
    int k2 = mid+1;
    int c= 0;
    while(k1<=mid and k2<=j){
        if(less(l[k1], l[k2])){
            temp[c] = l[k1];
            k1 += 1;
            c += 1;
        }else{
            temp[c] = l[k2];
            k2 += 1;
            c += 1;
        }
    }
    while(k1<=mid){
        temp[c] = l[k1];
        k1 +=1;
        c += 1;
    }
    while(k2<=j){
        temp[c] = l[k2];
        k2 += 1;
        c += 1;
    }

    for(int k=i;k<=j;k++){
        l[k] = temp[k-i];
    }
}

template<typename T, typename F>
void merge_sort(vector<T> &l, F less){
    merge_sort(l, less, 0, l.size()-1);
}

template<typename T>
void merge_sort(vector<T> &l){
    merge_sort(l, [](const T&o1, const T&o2){ return o1<o2;});
}

template<typename T, typename F>
void quick_sort(vector<T> &l, F less, int i, int j){
    if(i>=j) return;
    if(i == j-1){
        if(less(l[j], l[i])) swap(l[i], l[j]);
        return;
    }

    int k1 = i;
    int k2  = j;
    int empty = j;
    bool right = true;
    T mark = l[j];
    k2 -=1 ;
    while(k1<=k2){
        if(right){
            while(k1<=k2){
                if(less(mark, l[k1])){
                    l[empty] = l[k1];
                    empty = k1;
                    k1 += 1;
                    break;
                }
                k1 += 1;
            }
            right = false;
        }else{
            while(k1<=k2){
                if(less(l[k2], mark)){
                    l[empty] = l[k2];
                    empty = k2;
                    k2 -=1;
                    break;
                }
                k2 -= 1;
            }
            right = true;
        }
    }
    l[empty] = mark;
    quick_sort(l, less, i, empty-1);
    quick_sort(l, less, empty+1, j);
}

template<typename T, typename F>
void quick_sort(vector<T> &l, F less){
    quick_sort(l, less, 0, l.size()-1);
}

template<typename T>
void quick_sort(vector<T> &l){
    quick_sort(l, [](const T&o1, const T&o2){ return o1<o2;});
}

template<typename T, typename F>
void heap_sort(vector<T> &l, F less){
    int n = l.size();
    if(n<2) return;
    if(n == 2){
        if(less(l[1], l[0])){
            swap(l[0], l[1]);
        }
        return;
    }

    vector<T> heap = vector<T>(n);
    int hn = 1;
    heap[0] = l[0];
    for(int i=1;i<n;i++){
        heap[hn] = l[i];
        hn += 1;
        int j = hn-1;
        int p = (j-1)/2;
        while(j>0 and less(heap[j], heap[p])){
            swap(heap[p], heap[j]);
            j = p;
            p = (j-1)/2;
        }
    }

    int k = 0;
    while(hn>0){
        l[k] = heap[0];
        k += 1;
        heap[0] = heap[hn-1];
        hn -= 1;

        int j = 0;
        while(j<hn){
            int left = j*2+1;
            int right = j*2+2;
            int mn = j;
            if(left<hn and less(heap[left],heap[mn])) mn = left;
            if(right<hn and less(heap[right], heap[mn])) mn = right;

            if(mn == j) break;
            else{
                swap(heap[j], heap[mn]);
                j = mn;
            }
        }
    }
}

template<typename T>
void heap_sort(vector<T> &l){
    heap_sort(l, [](const T&o1, const T&o2){ return o1<o2;});
}

void f(int a, int b=1){
    cout<<a+b<<endl;
}

void test00(int n){
    srand(time(NULL));
    vector<int> l(n);
    for(int i=1;i<=n;i++){
        l[i-1] = i;
    }
    for(int i=0;i<n;i++){
        int j = rand()%n; 
        swap(l[i], l[j]);
    }
    for(auto i:l) cout<<i<<",";
    cout<<endl;
    bubble_sort(l);
    for(auto i:l) cout<<i<<",";
    cout<<endl;
}

void test01(int n){
    srand(time(NULL));
    vector<int> l(n);
    for(int i=1;i<=n;i++){
        l[i-1] = i;
    }
    for(int i=0;i<n;i++){
        int j = rand()%n; 
        swap(l[i], l[j]);
    }
    for(auto i:l) cout<<i<<",";
    cout<<endl;
    insert_sort(l);
    for(auto i:l) cout<<i<<",";
    cout<<endl;
}

void test02(int n){
    srand(time(NULL));
    vector<int> l(n);
    for(int i=1;i<=n;i++){
        l[i-1] = i;
    }
    for(int i=0;i<n;i++){
        int j = rand()%n; 
        swap(l[i], l[j]);
    }
    for(auto i:l) cout<<i<<",";
    cout<<endl;
    merge_sort(l);
    for(auto i:l) cout<<i<<",";
    cout<<endl;
}

void test03(int n){
    srand(time(NULL));
    vector<int> l(n);
    for(int i=1;i<=n;i++){
        l[i-1] = i;
    }
    for(int i=0;i<n;i++){
        int j = rand()%n; 
        swap(l[i], l[j]);
    }
    for(auto i:l) cout<<i<<",";
    cout<<endl;
    quick_sort(l);
    for(auto i:l) cout<<i<<",";
    cout<<endl;
}

void test04(int n){
    srand(time(NULL));
    vector<int> l(n);
    for(int i=1;i<=n;i++){
        l[i-1] = i;
    }
    for(int i=0;i<n;i++){
        int j = rand()%n; 
        swap(l[i], l[j]);
    }
    for(auto i:l) cout<<i<<",";
    cout<<endl;
    heap_sort(l);
    for(auto i:l) cout<<i<<",";
    cout<<endl;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    int n = atoi(argv[1]);
    test04(n);
    return 0;

    test03(n);
    return 0;

    test02(n);
    return 0;

    test01(n);
    return 0;

    test00(n);
    return 0;

    vector<int> l(n);
    for(int i=1;i<=n;i++){
        l[i-1] = i;
    }
    for(int i=0;i<n;i++){
        int j = rand()%n; 
        swap(l[i], l[j]);
    }
    selection_sort(l);
    return 0;
}
