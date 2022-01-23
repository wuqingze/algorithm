#include <iostream>
#include <vector>

using namespace std;

class STree{
public:
    vector<int> arr;
    vector<int> tree;
    STree(vector<int> &arr_){
        arr = arr_;
        int n = arr.size();
        tree = vector<int>(2*n-1);
        build(0, arr.size()-1);
    }

    void build(int left, int right, int p=0){
        if(left == right){
            tree[p] = arr[right];
            return;
        }
        int mid = left + (right-left)/2;
        build(left, mid, 2*p+1);
        build(mid+1, right, 2*p+2);
        tree[p] = tree[2*p+1] + tree[2*p+2];
    }

    int search(int i, int j){
        return query(i, j, 0, arr.size()-1, 0);
    }

    int query(int nl, int nr, int l, int r, int p=0){
        if(nl<= l and nr >=r){
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
    if(argc<2) return 0;
    vector<int> arr = {1,2 ,3,4};
    STree tree(arr);
    cout<<tree.search(atoi(argv[1]), atoi(argv[2]))<<endl;
    return 0;
}
