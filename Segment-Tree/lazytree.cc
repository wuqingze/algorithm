#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int val;
    bool tag;
    Node(){
        val = 0;
        tag = false;
    }
};

class STree{
public:
    vector<int> arr;
    vector<Node> tree;

    STree(vector<int> &&arr_){
        arr = arr_;
        int n = arr.size();
        tree = vector<Node>(4*n, Node());
        build(0, n-1, 0);
    }

    void build(int l, int r, int p){
        if(l == r){
            tree[p].val = arr[l];
            return;
        }
        int mid = l + (r-l)/2;
        build(l, mid, 2*p+1);
        build(mid+1, r, 2*p+2);
        tree[p].val = max(tree[p*2+1].val, tree[2*p+2].val);
    }

    void pushtagdown(int p){
        if(tree[p].tag){
            int l = 2*p+1;
            int r = 2*p+2;
            tree[l].val = tree[p].val;
            tree[r].val = tree[p].val;
            tree[l].tag = true;
            tree[r].tag = true;
            tree[p].tag = false;
        }
    }

    int query(int index){
        return query(index, index);
    }

    int query(int l, int r){
        return query(l, r, 0, arr.size()-1, 0);
    }

    int query(int nl, int nr, int l, int r, int p){
        if(nl<=l and nl>=r){
            return tree[p].val;
        }
        pushtagdown(p);
        int mid = l + (r-l)/2;
        int mx = 0;
        if(nl<=mid) mx = max(mx, query(nl, nr, l, mid, 2*p+1));
        if(nr>mid)  mx = max(mx, query(nl, nr, mid+1, r, 2*p+2));
        return mx;
    }

    void update(int index, int v){
        update(index, index, v);
    }

    void update(int l, int r, int v){
/        update(l, r, 0, arr.size()-1, v, 0);
    }

    void update(int nl, int nr, int l, int r, int v, int p){
        if(nl<=l and nr>=r){
            tree[p].val = v;
            tree[p].tag = true;
            return;
        }

        pushtagdown(p);
        int mid = l + (r-l)/2;
        if(nl<=mid) update(nl, nr, l, mid, v, 2*p+1);
        if(nr>mid) update(nl, nr, mid+1, l, v, 2*p+2);
        tree[p].val = max(tree[p*2+1].val, tree[2*p+2].val);
    }
};

int main(){return 0;}
