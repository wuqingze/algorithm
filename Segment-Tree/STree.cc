#include <iostream>
#include <vector>

using namespace std;

class STree{
public:
    vector<int> tree;
    vector<int> arr;

    STree(const vector<int> &arr_){
        arr = arr_;
        int n = arr.size();
        tree = vector<int>(4*n);
        build(0, n-1, 0);
    }

    void build(int l, int r, int p=0){
        if(l == r){
            tree[p] = arr[l];
            return;
        }
        int mid = l + (r-l)/2;
        build(l, mid, 2*p+1);
        build(mid+1, r, 2*p+2);
        tree[p] = tree[2*p+1]+tree[2*p+2];
    }

    int query(int l, int r){
        return query(l, r, 0, arr.size()-1); 
    }

    int query(int nl, int nr, int l, int r, int p=0){
        if(nl<= l and nr>=r){
            return tree[p];
        }

        int mid = l + (r-l)/2;

        int sum = 0;
        if(nl<=mid){
            sum += query(nl, nr, l, mid, 2*p+1);
        }
        if(nr>mid){
            sum += query(nl, nr, mid+1, r, 2*p+2);
        }
        return sum;
    }
};

int main(int argc, char* argv[]){
    vector<int> arr = {1, 2, 3, 4};
    STree tree(arr);
    cout<<tree.query(atoi(argv[1]), atoi(argv[2]))<<endl;
    return 0;
}
