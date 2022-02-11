#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
struct Node{
    int v;
    Node* l;
    Node* r;
    Node(){
        l = NULL;
        r = NULL;
    }

    Node(int v_){
        v = v_;
        Node();
    }
};

class Tree{
public:
    Node* root;

    Tree(){
        root = NULL;
    }

    void insert(int v){
        if(not root){
            root = new Node(v);
            return;
        }
        insert(root, v);
    }

    void insert(Node* node, int v){
        if(node->v > v){
            if(not node->l){
                node->l = new Node(v);
                return;
            }else{
                insert(node->l, v);
            }
        }else{
            if(not node->r){
                node->r = new Node(v);
                return;
            }else{
                insert(node->r, v);
            }
        }
    }

    void traverse(int i=0){
        if(i == 0){
            recursion(root);
            cout<<endl;
        }else{
            iterate();
            cout<<endl;
        }
    }

    void iterate(){
        vector<Node*> l;
        auto node = root;
        while(node){
            l.push_back(node);
            node = node->l;
        }
        while(not l.empty()){
            auto node = l.back();
            l.pop_back();
            cout<<node->v<<" ";
            if(node->r){
                l.push_back(node->r);
                node = node->r->l;
                while(node){
                    l.push_back(node);
                    node = node->l;
                }
            }
        }
    }

    void recursion(Node* node){
        if(not node) return;
        if(not node->l){
            cout<<node->v<<" ";
            recursion(node->r);
        }else{
            recursion(node->l);
            cout<<node->v<<" ";
            recursion(node->r);
        }
    }
};

int main(int argc, char* argv[]){
    int len = 20;
    if(argc>1) len = atoi(argv[1]);
    srand(time(NULL));
    vector<int> l(len);
    for(int i=0;i<len;i++) l[i] = i+1;
    for(int i=0;i<len;i++){
        int j = rand()%len;
        swap(l[i],l[j]);
    }
    /**
    for(auto i:l){
        cout<<i<<" ";
    }
    cout<<endl;
    sort(l.begin(), l.end());
    for(auto i:l){
        cout<<i<<" ";
    }
    cout<<endl;
    **/
    Tree tree;
    for(int i:l) tree.insert(i);
    tree.traverse(1);
    return 0;
}
