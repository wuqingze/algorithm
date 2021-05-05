#include <iostream>
#include <vector>
#include <map>

using namespace std;

class UF{
public:
    vector<int> parent;
    vector<int> rank;

    UF(int n){
        parent = vector<int>(n);
        rank = vector<int>(n, 1);
        for(int i=0;i<n;i++) {
            parent[i] = i;
        }
    }

    bool connected(int i, int j){
        return find(i) == find(j);
    }

    int find(int i){
        if(i == parent[i]) return i;
        parent[i] = find(parent[i]);
        return parent[i];
    }

    void merge(int i, int j){
        int ip = find(i);
        int jp = find(j);

        if(rank[ip] <= rank[jp]){
            parent[ip] = jp;
        }else{
            parent[jp] = ip;
        }

        if(rank[ip] == rank[jp]){
            rank[jp] += 1;
        }
    }

    int maxUnion(){
        int mx=0;
        int n = parent.size();
        vector<int> count(n, 0);
        for(int i=0;i<n;i++){
            count[find(i)] +=1;
            mx = max(mx, count[find(i)]);
        }
        return mx;
    }
};
