#include <iostream>
#include <vector>
#include "BinarySearchTree.cc"
#include <set>
#include <unordered_set>
#include <math.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

bool find(vector<int> &l, int i){
    for(auto a:l) if(a==i) return true;
    return false;
}

int strtoint(char *s){
    int c = 0;
    int result = 0;
    while(s[c] != '\0') c += 1;
    for(int i=0;i<c;i++)
        result += (s[c-i-1]-'0')*pow(10, i);
    return result;
}

void test00(int n){
    BinarySearchTree<int> tree;

    vector<int> l;
    for(int i=0;i<n;){
        auto t = rand()%n;
        if(not find(l, t)){
            l.push_back(t);
            i+= 1;
        }
    }

    for(int i=0;i<n;i++) tree.insert(l[i]);
    for(int i=0;i<n;i++){
        tree.traverse([](decltype(tree.getRoot()) node){
//            cout<<node->val<<" [ label="<<node->val<<" ]"<<endl;
//            if(node->left) cout<<node->val<<" -> "<<node->left->val<<endl;
//            if(node->right) cout<<node->val<<" -> "<<node->right->val<<endl;
                cout<<node->val<<endl;
        });
        cout<<"=============after remove"<<endl;
        tree.remove(l[i]);
    }
    for(auto i:l) cout<<i<<" ";
}

void test01(){
    BinarySearchTree<int> tree;

    auto print = [](decltype(tree.getRoot()) node){
            cout<<node->val<<" [ label="<<node->val<<" ]"<<endl;
            if(node->left) cout<<node->val<<" -> "<<node->left->val<<endl;
            if(node->right) cout<<node->val<<" -> "<<node->right->val<<endl;

        };

    tree.insert(2);
    tree.traverse(print);

    tree.insert(0);
    tree.traverse(print);

    tree.insert(4);
    tree.traverse(print);

    tree.insert(5);
    tree.traverse(print);

    tree.remove(2);
    tree.traverse(print);
}

void test02(){
    BinarySearchTree<int> tree;

    auto print = [](decltype(tree.getRoot()) node){
            cout<<node->val<<" [ label="<<node->val<<" ]"<<endl;
            if(node->left) cout<<node->val<<" -> "<<node->left->val<<endl;
            if(node->right) cout<<node->val<<" -> "<<node->right->val<<endl;

        };

    tree.insert(2);
    tree.traverse(print);

    tree.insert(0);
    tree.traverse(print);

    tree.insert(4);
    tree.traverse(print);

    tree.insert(5);
    tree.traverse(print);

    tree.remove(2);
    tree.traverse(print);
    cout<<"kfjalj"<<endl;
}

void test03(int n){
    BinarySearchTree<int> tree;

    unordered_set<int> l;
    for(int i=0;i<n;){
        auto t = rand()%n;
        if(0 == l.count(t)){
            l.insert(t);
            i+= 1;
        }
    }

    for(auto i: l){
        tree.insert(i);
        cout<<"insert "<<i<<endl;
    }

    for(auto i: l){
        tree.remove(i);
        cout<<"remove "<<i<<endl;
    }

    cout<<"traverse ..."<<endl;
    tree.traverse([](decltype(tree.getRoot()) node){
        cout<<node->val<<endl;
    });
    while(1){}
}

void test04(){
    while(1){}
}

void test05(int n){
    BinarySearchTree<int> tree;
    for(int i=0;i<n;i++){
        tree.insert(rand()%n);
    }
    cout<<"insert finished...."<<endl;
    tree.getRoot() = nullptr;
    cout<<"root = nullptr..."<<endl;
    while(true);
}

int main(int argc, char *argv[]){

//    test02();
//    return 0;

    if(argc<1) return 0;
    int n = strtoint(argv[1]);

    test05(n);
    return 0;

    test03(n);
    return 0;

    test00(n);
    return 0;

    cout<<"=============================="<<endl;
    set<int> s;
    BinarySearchTree<int> tree;

    vector<int> l;
    for(int i=0;i<n;){
        auto t = rand()%n;
        if(not find(l, t)){
            l.push_back(t);
            i+= 1;
        }
    }

    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(int i=0;i<n;i++) s.insert(l[i]);
    auto stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"set insert time cost "<<stop-start<<" milliseconds"<<endl;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(int i=0;i<n;i++) tree.insert(l[i]);
    stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"tree insert time cost "<<stop-start<<" milliseconds"<<endl;

    tree.traverse([](decltype(tree.getRoot()) node){
            cout<<node->val<<" [ label="<<node->val<<" ]"<<endl;
            if(node->left) cout<<node->val<<" -> "<<node->left->val<<endl;
            if(node->right) cout<<node->val<<" -> "<<node->right->val<<endl;

    });
    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(int i=0;i<n;i++) s.erase(l[i]);
    stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"set remove time cost "<<stop-start<<" milliseconds"<<endl;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
//    for(int i=0;i<n;i++) tree.remove_(l[i]);
//    for(int i=0;i<n;i++) tree.remove_(l[i], [](int i){cout<<"remove "<<i<<endl;});
    stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"tree remove time cost "<<stop-start<<" milliseconds"<<endl;
//    tree.traverse([](int a){cout<<a<<endl;});

    return 0;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(int i=0;i<n;i++) s.insert(rand());
    stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"set insert time cost "<<stop-start<<" milliseconds"<<endl;

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for(int i=0;i<n;i++) tree.insert(rand());
    stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<"tree insert time cost "<<stop-start<<" milliseconds"<<endl;
    
    return 0;
}
