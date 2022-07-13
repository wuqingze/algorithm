#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>

using namespace std;

struct Node{
    int t;//child up limit
    int n;//key count
    vector<Node*> children;
    vector<int> key;
    Node* p;
    bool isleaf;
    Node(){}
    Node(int t_){
        t = t_;
        n = 0;
        children =vector<Node*>(t+1, nullptr);
        key = vector<int>(t);
        p = nullptr;
    }

    Node(int val, int t_):Node(t_){
        this->key[0] = val;
        this->n += 1;
    }
};

class BTree{
public:
    Node* root = nullptr;
    int t;
    BTree(int t_){
        t = t_;
    }

    void insert(int val){
        if(root == nullptr){
            root = new Node(t);
            root->isleaf = true;
            root->key[0] = val;
            root->n = 1;
            return;
        }

        auto ptr = root;
        while(not ptr->isleaf){
            int i = 0;
            while(i<ptr->n and ptr->key[i] < val){
                i+=1;
            }
            ptr = ptr->children[i];
        }
        fixup(ptr, val, {});
   }

    void fixup(Node* ptr, int val, pair<Node*, Node*> nodes){
        int i = ptr->n;
        int j = i+1;
        while(i>0){
            if(ptr->key[i-1] > val){
                ptr->key[i] = ptr->key[i-1];
                ptr->children[j] = ptr->children[j-1];
                i -= 1;
                j -= 1;
            }else break;
        }
        ptr->key[i] = val;
        ptr->n += 1;
        if(not ptr->isleaf){
            ptr->children[j] = nodes.second;
            ptr->children[j-1] = nodes.first;
        }

        if(ptr->n == t){
           int mid = ptr->key[t/2];
           auto snode = split(ptr);
           if(ptr == root){
               root = new Node(mid, t);
               root->children[0] = snode.first;
               root->children[1] = snode.second;
               snode.first->p = root;
               snode.second->p = root;
               delete ptr;
               return;
           }else{
               fixup(ptr->p, mid, snode);
               delete ptr;
           }
        }
    }

    pair<Node*, Node*> split(Node* node){
        pair<Node*, Node*> result = {};
        result.first = new Node(t);
        result.second = new Node(t);
        for(int i=0;i<t/2;i++){
            result.first->key[i] = node->key[i];
            result.first->children[i] = node->children[i];
        }
        result.first->children[t/2] = node->children[t/2];
        result.first->n = t/2;

        for(int i=t/2+1, j=0;i<node->n;i++,j++){
            result.second->key[j] = node->key[i];
            result.second->children[j] = node->children[i];
        }
        result.second->children[(node->n-1)/2] = node->children[node->n];
        result.second->n = (node->n-1)-(t/2);
        result.first->p = node->p;
        result.second->p = node->p;

        for(int i=0;i<t;i++){
            if(result.first->children[i] != nullptr){
                result.first->children[i]->p = result.first;
            }else break;
        }
        for(int i=0;i<t;i++){
            if(result.second->children[i] != nullptr){
                result.second->children[i]->p = result.second;
            }else break;
        }
        if(node->isleaf){
            result.first->isleaf = true;
            result.second->isleaf = true;
        }
        return result;
    }

    void remove(int key){
        auto ptr = find(key);
        if(ptr == nullptr) return;

        if(ptr->isleaf){
            int i=0;
            while(ptr->key[i] != key) i+=1;
            for(int j=i;j<ptr->n-1;j++) ptr->key[j] = ptr->key[j+1];
            ptr->n -=1;
            fixremove(ptr);
        }else{
            int i=0;
            while(ptr->key[i] != key) i+=1;
            auto nextnode = next(ptr->children[i+1]);
            ptr->key[i] = nextnode->key[0];
            for(int j=0;j<nextnode->n-1;j++){
                nextnode->key[j] = nextnode->key[j+1];
            }
            nextnode->n -=1 ;
            fixremove(nextnode);
        }
    }

    Node* next(Node* ptr){
        if(ptr->children[ptr->n] == nullptr) return ptr;
        return next(ptr->children[0]);
    }

    void fixremove(Node* ptr){
        if(ptr->n >= t/2-1) return;
        if(ptr == root){
            if(ptr->n == 0){
                if(ptr->children[0] == nullptr) return;
                else{
                    auto nroot = ptr->children[0];
                    delete root;
                    root = nroot; 
                }
                return;
            }else return;
        }

        int i=0;
        while(ptr->p->children[i] != ptr) i+=1;

        if(i == ptr->p->n and ptr->p->children[i-1]->n >= t/2){
            auto bro = ptr->p->children[i-1];
            auto p = ptr->p;
            int j = ptr->n;
            while(j>=1){
                ptr->key[j] = ptr->key[j-1];
                j-=1;
            }
            ptr->key[0] = p->key[p->n-1];
            ptr->n += 1;
            j = ptr->n;
            while(j>=1){
                ptr->children[j] = ptr->children[j-1];
                j-=1;
            }
            ptr->children[0] = bro->children[bro->n];
            if(bro->children[bro->n] != nullptr) bro->children[bro->n]->p = ptr;
            p->key[p->n-1] = bro->key[bro->n-1];
            bro->children[bro->n] = nullptr;
            bro->n -= 1;
            return;
        }else if(i<ptr->p->n and ptr->p->children[i+1]->n>=t/2){
            auto bro = ptr->p->children[i+1];
            auto p = ptr->p;
            ptr->key[ptr->n] = p->key[i];
            ptr->n += 1;
            ptr->children[ptr->n] = bro->children[0];
            if(bro->children[0] != nullptr) bro->children[0]->p = ptr;
            p->key[i] = bro->key[0];
            for(int j=0;j<bro->n-1;j++){
                bro->key[j] = bro->key[j+1];
            }
            bro->n -=1;
            for(int j=0;j<=bro->n;j++){
                bro->children[j] = bro->children[j+1];
            }
            bro->children[bro->n+1] = nullptr;
            return;
        }else{
            if(i==ptr->p->n){
                auto p = ptr->p;
                auto bro = ptr->p->children[i-1];
                bro->key[bro->n] = p->key[p->n-1];
                bro->n += 1;
                for(int j=0;j<ptr->n;j++){
                    bro->key[bro->n+j] = ptr->key[j];
                    bro->children[bro->n+j] = ptr->children[j];
                    if(ptr->children[j] != nullptr) ptr->children[j]->p = bro;
                }
                bro->n += ptr->n;
                bro->children[bro->n] = ptr->children[ptr->n];
                if(ptr->children[ptr->n] != nullptr) ptr->children[ptr->n]->p = bro;
                p->children[p->n] = nullptr;
                p->n -=1;
                delete ptr;
                fixremove(p);
            }else{
                auto p = ptr->p;
                auto bro = ptr->p->children[i+1];
                ptr->key[ptr->n] = p->key[i];
                ptr->n += 1;
                for(int j=0;j<bro->n;j++){
                    ptr->key[ptr->n+j] = bro->key[j];
                    ptr->children[ptr->n+j] = bro->children[j];
                    if(bro->children[j] != nullptr) bro->children[j]->p = ptr;
                }
                ptr->n += bro->n;
                ptr->children[ptr->n] = bro->children[bro->n];
                if(bro->children[bro->n] != nullptr) bro->children[bro->n]->p = ptr;
                for(int j=i;j<p->n-1;j++){
                    p->key[j] = p->key[j+1];
                }
                for(int j=i+1;j<p->n;j++){
                    p->children[j] = p->children[j+1];
                }
                p->children[p->n] = nullptr;
                p->n -= 1;
                delete bro;
                fixremove(p);
            }
        }
    }

    Node* find(int key){
        if(root == nullptr) return nullptr;

        auto ptr = root;
        while(ptr!=nullptr){
            int i=0;
            while(i<ptr->n){
                if(ptr->key[i] == key) return ptr;
                if(ptr->key[i] > key) break;
                i+= 1;
            }
            ptr = ptr->children[i];
        }
        return nullptr;
    }

    void traverse(){
        cout<<"digraph g {"<<endl;
        cout<<"node [shape = record,height=.1];"<<endl;
        int cnt = 0;
        traverse(root,{}, cnt);
        cout<<"}"<<endl;
    }

    void traverse(Node* node, map<Node*, int> mark, int &cnt){
        cout<<"node"+to_string(cnt)+"[label = \"";
        for(int i=0;i<node->n;i++){
            cout<<"<f"+to_string(i)+">|"+to_string(node->key[i])+"|";
        }
        for(int i=node->n;i<t-1;i++){
            cout<<"<f"+to_string(i)+">||";
        }
        cout<<"<f"+to_string(t-1)+">\"];"<<endl;
        mark[node] = cnt;
        cnt += 1;
        if(node != root){
            cout<<"node"+to_string(mark[node->p])+":";
            int i=0;
            while(node->p->children[i] != node){
                i += 1;
            }
            cout<<"f"+to_string(i)+" -> node"+to_string(cnt-1)+";"<<endl;
        }
        if(not node->isleaf){
            for(int i=0;i<=node->n;i++){
                traverse(node->children[i], mark, cnt);
            }
        }
    }

    void traverse(int index){
        //cout<<"digraph g {"<<endl;
        cout<<"subgraph {"<<endl;
        cout<<"node [shape = record,height=.1];"<<endl;
        int cnt = 0;
        traverse(root,{}, cnt, index);
        cout<<"}"<<endl;
    }

    void traverse(Node* node, map<Node*, int> mark, int &cnt, int index){
        string nodename = "node"+to_string(cnt)+"_"+to_string(index);
        cout<<nodename+" [label = \"";
        for(int i=0;i<node->n;i++){
            cout<<"<f"+to_string(i)+">|"+to_string(node->key[i])+"|";
        }
        for(int i=node->n;i<t-1;i++){
            cout<<"<f"+to_string(i)+">||";
        }
        cout<<"<f"+to_string(t-1)+">\"];"<<endl;
        mark[node] = cnt;
        if(node != root){
            cout<<"node"+to_string(mark[node->p])+"_"+to_string(index)+":";
            int i=0;
            while(node->p->children[i] != node){
                i += 1;
            }
            cout<<"f"+to_string(i)+" -> "+nodename+";"<<endl;
        }
        cnt += 1;
        if(not node->isleaf){
            for(int i=0;i<=node->n;i++){
                traverse(node->children[i], mark, cnt, index);
            }
        }
    }};

int main(int argc, char* argv[]){
    BTree tree(4);
    /**
    for(int i=0;i<atoi(argv[1]);i++){
        tree.insert(i);
    }
    **/

    srand((unsigned)(time(NULL)));
    int n = atoi(argv[1]);
    vector<int> args(n);
    for(int i=1;i<=n;i++) args[i-1] = i;
    for(int i=0;i<n;i++) swap(args[i], args[rand()%n]);
//    args = {1,4,3,2};
//    args = {1,2,3,4};
//    args = {4,3,1,2};
//    args = {3,4,5,6,7,1,2};
//    args = { 8,5,4,10,7,1,3,9,2,11,13,6,12};
    cout<<"// ";
    for(int i=0;i<n;i++) cout<<args[i]<<",";
    cout<<endl;
    for(int i=0;i<n;i++) tree.insert(args[i]);
//    cout<<"digraph {"<<endl;
//    tree.traverse(100);
//    for(int i=0;i<n/2;i++) {
//    for(int i=0;i<n;i++) {
//        tree.remove(args[i]);
//        tree.traverse(i);
//    }
    for(int i=0;i<n;i++) swap(args[i], args[rand()%n]);
    tree.traverse();
//    cout<<"}"<<endl;
    return 0;
}
