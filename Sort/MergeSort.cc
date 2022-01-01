#include <iostream>
#include <vector>

using namespace std;

class MergeSort{
public:
    void f(int i, int j, vector<int> &l){
        if(i>=j) return;
        if(i == j-1){
            if(l[i]>l[j]) swap(l[i], l[j]);
            return;
        }

        int mid = (j-i)/2+i;
        f(i, mid, l);
        f(mid+1, j, l);
        int k1 = i;
        int k2 = mid+1;
        vector<int> temp;
        while(k1<=mid and k2<=j){
            if(l[k1]>l[k2]){
                temp.push_back(l[k2]);
                k2 += 1;
            }else{
                temp.push_back(l[k1]);
                k1 += 1;
            }
        }
        if(k1>mid){
            while(k2<=j){
                temp.push_back(l[k2]);
                k2 += 1;
            }
        }else{
            while(k1<=mid){
                temp.push_back(l[k1]);
                k1 += 1;
            }
        }
        for(int k=i;k<=j;k++){
            l[k] = temp[k-i];
        }
    }

    void sort(vector<int> &l){
        f(0, l.size()-1, l);
    }
};

int main(int argc, char* argv[]){
    if(argc<2) return 0;
    vector<int> l;
    for(int i=1;i<argc;i++){
        l.push_back(atoi(argv[i]));
    }
    MergeSort s;
    s.sort(l);
    for(auto i:l)
        cout<<i<< " ";
    cout<<endl;
    return 0;
};
