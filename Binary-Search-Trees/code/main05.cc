#include <iostream>
#include <vector>
#include "BinarySearchTree00.cc"
#include <set>
#include <unordered_set>
#include <math.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

void test00(){
    int cnt;
    cin>>cnt;
    int n = cnt;
    BinarySearchTree<int> tree;
    vector<int> l;
    while(cnt-- > 0) {
        auto t = rand() %n;
        tree.insert(t);
        l.push_back(t);
        cout<<"insert "<<t<<endl;
    }

    for(auto t:l) tree.remove(t);
    cout<<"finish ..."<<endl;
    while(1);
}

int main(int argc, char *argv[]){
    test00();
    return 0;
}
