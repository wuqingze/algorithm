#include <iostream>

using namespace std;
class Node{
    public:
    int t;
    int c;
    Node(int t, int c_ ){
        this->t = t;
    }
};

int main(){

    Node n(10);
    cout<<n.t<<endl;
    return 0;
}
