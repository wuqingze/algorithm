#include <iostream>
#include <vector>
#include <memory>
#include <string.h>

using namespace std;

template<typename T>
struct Node{
    T val;
    Node *left;
    Node *right;
    Node(T val_){val = val_;}
};

template<typename T>
struct NodeSharedPtr{
    T val;
    shared_ptr<NodeSharedPtr<T>> left;
    shared_ptr<NodeSharedPtr<T>> right;
    NodeSharedPtr(T val_){val = val_;}
};

template<typename T>
struct NodeSharedPtr1{
    T val;
    unique_ptr<NodeSharedPtr1<T>> left;
    unique_ptr<NodeSharedPtr1<T>> right;
    NodeSharedPtr1(T val_){val = val_;}
};


void test00_ptr(){
    Node<int> root(1);
    root.left = new Node<int>(1);
    root.right = new Node<int>(1);
}

struct N{
    int val;
    N(int val_){val = val_;
    }
};

void test01_ptr(){
    NodeSharedPtr<int> root(1);
    root.left = shared_ptr<NodeSharedPtr<int>>(new NodeSharedPtr<int>(1024));
    root.right = shared_ptr<NodeSharedPtr<int>>(new NodeSharedPtr<int>(1024));
}

void test02_ptr(){
    NodeSharedPtr1<int> root(1);
    root.left = unique_ptr<NodeSharedPtr1<int>>(new NodeSharedPtr1<int>(1024));
    root.right = unique_ptr<NodeSharedPtr1<int>>(new NodeSharedPtr1<int>(1024));
    root.left = unique_ptr<NodeSharedPtr1<int>>(new NodeSharedPtr1<int>(1024));
}

void test03_ptrmove(){
    shared_ptr<int[]> p(new int[10]);
    shared_ptr<int[]> p1;
}

int main(){
    while(1) test02_ptr();

    return 0;
}
