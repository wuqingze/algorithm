#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;
class STree{
public:
    vector<int> arr;
    vector<int> tree;
    STree(vector<int> &&arr_){
        arr = arr_;
        int n = arr.size();
        tree = vector<int>(4*n);
        build(0, n-1);
    }

    void build(int l, int r, int p=0){
        if(l==r){
            tree[p] = arr[l];
            return ;
        }

        int mid = l+(r-l)/2;
        build(l, mid, 2*p+1);
        build(mid+1, r, 2*p+2);

        tree[p] = tree[2*p+1]+tree[2*p+2];
    }

    void update(int i){
        update(i, 0, arr.size()-1); 
    }

    void update(int i, int l, int r, int p=0){
        if(i == l and i==r){
            tree[p] += 1;
            return ;
        }
        int mid = l + (r-l)/2;
        if(i<=mid){
            update(i, l, mid, 2*p+1);
        }else{
            update(i, mid+1, r, 2*p+2);
        }
        tree[p] = tree[p*2+1] + tree[2*p+2];
    }

    int query(int l, int r){
        return query(l, r, 0, arr.size()-1);
    }

    int query(int nl, int nr, int l, int r, int p=0){
        if(nl<=l and nr>=r){
            return tree[p];
        }

        int sum = 0;
        int mid = l + (r-l)/2;
        if(nl<=mid){
            sum += query(nl, nr, l, mid, 2*p+1);
        }
        if(nr>mid){
            sum += query(nl, nr, mid+1, r, 2*p+2);
        }
        return sum;
    }
};

vector<int> f(vector<int> &l){
    vector<int> result;
    result.push_back(0);
    int n = l.size();
    for(int i=1;i<n;i++){
        int cnt = 0;
        for(int j=0;j<i;j++){
            if(l[j] < l[i]) cnt += 1;
        }
        result.push_back(cnt);
    }
    return result;
}

int main(int argc, char* argv[]){
    if(argc<2) return 0;
    int n = atoi(argv[1]);
    vector<int> arr(n);
    srand(time(NULL));
    for(int i=0;i<n;i++){
        //arr[i] = rand()%n;
        arr[i] = rand();
    }
    auto start = chrono::system_clock::now();
    auto ret1 = f(arr);
    cout<<"time for using n**2 method is "<<(chrono::system_clock::now()-start).count()<<endl;
    start = chrono::system_clock::now();
    /**
    for(auto i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<time(NULL)<<endl;;
    cout<<(chrono::system_clock::now()-start).count()<<endl;
    **/
    vector<int> l1 = vector<int>(arr.begin(), arr.end());
    sort(l1.begin(), l1.end());
    map<int, int> indexm;
    int cnt = 0;
    n = l1.size();
    int i=0;
    while(i<n){
        int j = i;
        while(j<n and l1[i] == l1[j]) j += 1;
        indexm[l1[i]] = cnt;
        cnt += 1;
        i = j;
    }
    STree tree(vector<int>(cnt, 0));
    vector<int> ret2;
    for(int i=0;i<n;i++){
        int index = indexm[arr[i]];
        index == 0?ret2.push_back(0):ret2.push_back(tree.query(0, index-1));
        /**
        if(index == 0){
            cout<<0<<" ";
        }else{
            int v = tree.query(0, index-1);
            cout<<v<<" ";
        }
        **/
        tree.update(index);
    }
//    cout<<endl;
    cout<<"time for using n*ln method is "<<(chrono::system_clock::now()-start).count()<<endl;
    for(int i=0;i<n;i++){
        if(ret1[i] != ret2[i]){
            cout<<"result comflict"<<endl;
            break;
        }
    }
    return 0;
}
