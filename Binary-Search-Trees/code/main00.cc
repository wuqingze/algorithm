#include <iostream>
#include <sstream>
#include <vector>
#include "BinarySearchTree.cc"

using namespace std;

void test00_insert(){
    string line;
    while(getline(cin, line)){
        istringstream is(line);
        int n;
        BinarySearchTree<int> tree;
        while(is>>n) tree.insert(n);
    }
}

void test01_insert(){
    BinarySearchTree<int> tree;
    int n;
    cin>>n;
    for(int i=0;i<n;i++) tree.insert(rand());
}

void test02_vector_pop(){
    vector<int> l;
    l.push_back(1);
    cout<<l.empty()<<endl;
    auto t = l.back();
    l.pop_back();
    cout<<t<<endl;
    cout<<l.empty()<<endl;
}

void test03_traverse(){
    BinarySearchTree<int> tree;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        auto t = rand()%n;
        cout<<t<<endl;
        tree.insert(t);
    }
    cout<<"===================="<<endl;
    tree.traverse(
            [](int a){ cout<<a<<endl;}
            );
}

void test04_find(){
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(6);
    tree.insert(1);
    tree.insert(9);

    cout<<tree.find(4)<<endl;
    cout<<tree.find(6)<<endl;
    cout<<tree.find(1)<<endl;
    cout<<tree.find(9)<<endl;
    cout<<tree.find(8)<<endl;
    cout<<tree.find(2)<<endl;

    BinarySearchTree<string> tree00([](string s1, string s2) { return -1;});
//    tree00.insert("hello1");
//    tree00.insert("hello2");
//    tree00.insert("hello3");
//    tree00.insert("hello4");
}

void test05_remove(){
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(6);
    tree.insert(1);
    tree.insert(9);
    cout<<"traverse=================="<<endl;
    tree.traverse([](int a){cout<<a<<endl;});

    cout<<"remove 4 =================="<<endl;
    tree.remove(4);
    tree.traverse([](int a){ cout<<a<<endl;});

    cout<<"remove 6 =================="<<endl;
    tree.remove(6);
    tree.traverse([](int a) { cout<<a<<endl;});

    cout<<"remove 1 =================="<<endl;
    tree.remove(1);
    tree.traverse([](int a){cout<<a<<endl;});

    cout<<"remove 9 =================="<<endl;
    tree.remove(9);
    tree.traverse([](int a){cout<<a<<endl;});

}

int main(){
    test05_remove();
    return 0;

    test04_find();
    return 0;

    test03_traverse();
    return 0;

    test02_vector_pop();
    return 0;

    test01_insert();
    return 0;

    test00_insert();
    return 0;
}
