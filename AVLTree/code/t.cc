#include <iostream>
#include <iterator>
#include <set>
#include <string>
 
using namespace std;
int main(int argc, char* argv[])
{
    const std::multiset<int> nums = {
        0,9,8,7,6,5,4,3,2,1
    };

    auto ptr = nums.find(atoi(argv[1]));
    auto gap = ptr - nums.begin();
    cout<<gap<<endl;
}
