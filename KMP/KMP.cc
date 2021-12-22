#include <iostream>
#include <vector>
#include <string>

using namespace std;
class KMP{
public:
    void search(string &txt, string &pattern){
        auto prefix = computerPrefix(pattern);
        for(int i=0;i<prefix.size();i++)
            cout<<prefix[i]<<" ";
        cout<<endl;
        int n = txt.length();
        int m = pattern.length();
        int q = -1;
        for(int i=0;i<n;i++){
            while(q>=0 and txt[i] != pattern[q+1]){
                q = prefix[q];
            }
            if(txt[i] == pattern[q+1]){
                q += 1;
            }
            if(q == m-1){
                cout<<i-m+1<<endl;
                q = -1;
            }
        }
    }

    vector<int> computerPrefix(string &pattern){
        int n = pattern.length();
        vector<int> ret(n);
        if(n==0) return ret;
        int k=-1;
        int q=1;
        ret[0] = -1;
        while(q<n){
            while(k>=0 and pattern[k+1] != pattern[q]){
                k = ret[k];
            }
            if(pattern[k+1] == pattern[q]){
                k = k+1;
            }
            ret[q] = k;
            q += 1;
        }
        return ret;
    }
};

int main(int argc, char* argv[]){
    if(argc<1) return 0;
    string txt= string(argv[1]);
    string word = string(argv[2]);
    KMP kmp;
    kmp.search(txt, word);
    return  0;
}
