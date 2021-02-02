#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node{
    int val;
    Node(int val_){val = val_;}
    Node *left;
    Node *right;
    ~Node(){
//        cout<<"delete "<<val<<endl;
        delete left;
        delete right;
    }
};

void insert(int val, Node* root){
    auto ptr = root;
    while(ptr){
        if(ptr->val == val) return;
        else if(not ptr->left and ptr->val > val){
            ptr->left = new Node(val);
            return;
        }else if(not ptr->right and ptr->val < val){
            ptr->right = new Node(val);
            return;
        }
        ptr = ptr->val < val ? ptr->right : ptr->left;
    }
}

void test00(int n){
        auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        auto root = new Node(n/2);
        for(int i=0;i<n;i++) insert(rand()%n, root);
        delete root;
        cout<<"insert finished..."<<endl;
        auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout<<"cost times: "<<end-start<<" milliseconds"<<endl;
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    test00(n);
    while(1);
    return 0;
}
