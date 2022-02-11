#include <map>
#include <iostream>

using namespace std;
int main(){
    multimap<int, int> mm;
    mm.insert({1,2});
    mm.insert({1,3});
    /**
    auto node = mm.begin();
    cout<<node->second<<endl;
    mm.erase(node);
    node = mm.begin();
    cout<<node->second<<endl;
    mm.erase(node);
    **/
    if(mm.find(1)) cout<<"find 1"<<endl;
    if(not mm.find(3)) cout<<"not find 3"<<endl;
    return 0;
}
