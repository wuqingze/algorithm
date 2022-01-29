#include <iostream>
#include <vector>

struct Node{
    Node* left;
    Node* right;
    int sum;
    Node(){
        left = NULL;
        right = NULL;
        sum = 0;
    }
};

using namespace std;
class DSTree{
public:
    Node* root;
    //int LEN = 1000000000;
    int LEN = 10;
    DSTree(){
        root = new Node();
    }

    void insert(int x){
        insert(0, LEN, x, root);
    }

    void insert(int l, int r, int x, Node* p){
        if(x == l and x == r){
            p->sum += 1;
            return;
        }

        int mid = l + (r-l)/2;
        if(x<=mid){
            if(not p->left) p->left = new Node();
            insert(l, mid, x, p->left);
        }else{
            if(not p->right) p->right = new Node();
            insert(mid+1, r, x, p->right);
        }
        int sum = 0;
        if(p->left) sum += p->left->sum;
        if(p->right) sum += p->right->sum;
        p->sum = sum;
    }

    int query(int x){
        int rank = query(0, x-1, 0, LEN, root)+1;
        if(rank==0) return 0x80000000;
        return rank;
    }

    int query(int nl, int nr, int l, int r, Node* p){
        if(nl<= l and nr >= r){
            return p->sum;
        }

        int mid = l + (r-l)/2;
        int sum = 0;
        if(nl <= mid){
            if(p->left){
                sum += query(nl, nr, l, mid, p->left);
            }
        }

        if(nr > mid){
            if(p->right){
                sum += query(nl, nr, mid+1, r, p->right);
            }
        }
        return sum;
    }

    int queryn(int x){
        return queryn(x, 0, LEN, root);
    }

    int queryn(int x, int l, int r, Node* p){
        if(x>p->sum) return 0x7fffffff;
        if(l==r){
            return l;
        }
        int mid = l+(r-l)/2;
        if(p->left and x<= p->left->sum){
            return queryn(x, l, mid, p->left);
        }else{
            if(p->left) x -= p->left->sum;
            return queryn(x, mid+1, r, p->right);
        }
    }

    int querypren(int x){
        if(root->sum == 0) return 0x80000000;
        int rank = query(x);
        if(rank == 0x80000000) return 0x80000000;
        if(rank == 0x7fffffff) return queryn(root->sum);
        return queryn(rank-1);
    }

    int querypostn(int x){
        if(root->sum == 0) return 0x7fffffff;
        int rank = query(x);
        if(rank == 0x80000000) return queryn(1);
        if(rank == 0x7fffffff) return 0x7fffffff;
        return queryn(rank+1);
    }
};


int main(){
    DSTree tree;
    int n;
    cin>>n;
    while(n-->0){
        int opt, x;
        cin>>opt>>x;
        if(opt == 1){
            cout<<tree.query(x)<<endl;
        }else if(opt == 2){
            cout<<tree.queryn(x)<<endl;
        }else if(opt == 3){
            cout<<tree.querypren(x)<<endl;
        }else if(opt == 4){
            cout<<tree.querypostn(x)<<endl;
        }else if(opt == 5){
            tree.insert(x);
        }
    }
    return 0;
}
