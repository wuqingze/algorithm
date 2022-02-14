#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Solution{
public:
    set<int> A;
    set<int> B;
    multimap<int, vector<int>> edges;

    void add(int c1, int c2, int w){
        edges.insert({w, {c1, c2}});
    }

    void tree(){
        A.insert(1);
        auto ptr = edges.begin();
        while(ptr != edges.end()){
            auto citys = ptr->second;
            if(A.count(citys[0]) and A.count(citys[1])){
                edges.erase(ptr);
                ptr = edges.begin();
            }else if(not A.count(citys[0]) and not A.count(citys[1])){
                ptr ++;
            }else{
                A.insert(A.count(citys[0])?citys[1]:citys[0]);
                cout<<citys[0]<<"---"<<ptr->first<<"---"<<citys[1]<<endl;
                edges.erase(ptr);
                ptr = edges.begin();
            }
        }
    }

};

int main(){
    /**
    Solution obj;
    obj.add(0,1,3);
    obj.add(0,5,4);
    obj.add(1,2,8);
    obj.add(1,6,6);
    obj.add(1,8,5);
    obj.add(2,3,12);
    obj.add(2,8,2);
    obj.add(3,4,10);
    obj.add(3,6,14);
    obj.add(3,7,6);
    obj.add(3,8,11);
    obj.add(4,5,18);
    obj.add(4,7,1);
    obj.add(5,6,7);
    obj.add(6,7,9);
    **/
    Solution obj;
    obj.add(1,2,5);
    obj.add(1,3,6);
    obj.add(2,3,1);
    obj.tree();
    return 0;
}
