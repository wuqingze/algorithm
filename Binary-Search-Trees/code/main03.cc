#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node{
    int val;
    Node(int val_){val = val_;}
    ~Node(){
//        cout<<"release "<<val<<" ..."<<endl;
    }
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

void insert(int val, shared_ptr<Node> root){
    auto ptr = root;
    while(ptr){
        if(ptr->val == val) return;
        else if(not ptr->left and ptr->val > val){
            ptr->left = shared_ptr<Node>(new Node(val));
            return;
        }else if(not ptr->right and ptr->val < val){
            ptr->right = shared_ptr<Node>(new Node(val));
            return;
        }
        ptr = ptr->val < val ? ptr->right : ptr->left;
    }
}

void test00(int n){
        auto root = shared_ptr<Node>(new Node(n/2));
        for(int i=0;i<n;i++) insert(rand()%n, root);
        root = nullptr;
        cout<<"insert finished..."<<endl;
}

void test01(int n){
        auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        auto root = shared_ptr<Node>(new Node(n/2));
        for(int i=0;i<n;i++) insert(rand()%n, root);
        root = nullptr;
        cout<<"insert finished..."<<endl;
        auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout<<"cost times: "<<end-start<<" milliseconds"<<endl;
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    test01(n);
    while(1);
    return 0;

    {
        auto root = shared_ptr<Node>(new Node(n/2));
        for(int i=0;i<n;i++) insert(rand()%n, root);
        root = nullptr;
        cout<<"insert finished..."<<endl;
    }
    while(1);
    return 0;
}
