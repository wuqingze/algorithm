#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct Node{
    int val;
    Node(int val_){val = val_;}
    shared_ptr<Node> next;
};

int main(){
    auto root = shared_ptr<Node>(new Node(0));
    int i=0;
    while(1){
        i += 1;
        auto t = shared_ptr<Node>(new Node(i));
        root->next = t;
        cout<<i<<endl;
    }

    return 0;
}
