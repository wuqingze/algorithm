#include <iostream>
#include <queue>

using namespace std;

void f(vector<vector<int>> &nums, int n, int s, vector<int> &path, vector<int> &dist){
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> nums(n, vector<int>(n, 0));
    for(int i=0; i<n;i++) for(int j=0;j<n;j++) cin>>nums[i][j];
    for(int i=0; i<n;i++) for(int j=0;j<n;j++) cout<<nums[i][j]<<",";
    return 0;
    vector<int> path(n, 0);
    vector<int> dist(n, 0x7fffffff);
    f(nums, n, 0, path, dist);
    for(auto c:path) cout<<c<<" ";
    cout<<endl;
    for(auto c:dist) cout<<c<<" ";
    cout<<endl;
    return 0;
}
