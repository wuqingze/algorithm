#include <algorithm>

template<typename T, class RandomIt, class Compare>
void sort(RandomIt first, RandomIt end, Compare less = 
        [](const T& o1, const T& o2){ return o1<o2;}){
    int n = end - first;
    if(n == 0) return;
    auto arr = first;
    auto fixup = [arr, less](int i){
        while(i>0){
            int parent = (i-1)/2;
            if(less(arr[parent], arr[i])){
                std::swap(arr[parent], arr[i]);
                i = parent;
            }else return;
        }
    };
    for(int i=1;i<n;i++) fixup(i);
    auto fixdown = [arr, less](int len){
        int i=0;
        while(i<len){
            int mx = i;
            int left = 2*i+1;
            int right = 2*i+2;
            if(left<len and less(arr[mx], arr[left])){
                mx = left;
            }
            if(right<len and less(arr[mx], arr[right])){
                mx = right;
            }
            if(mx != i){
                std::swap(arr[i], arr[mx]);
                i = mx;
            }else return;
        }
    };
    int len = n;
    for(int i=n-1;i>=0; i--){
        std::swap(arr[0], arr[i]);
        len -= 1;
        fixdown(len);
    }
}

int main(){
    return 0;
}
