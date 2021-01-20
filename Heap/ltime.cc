#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(){
    auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<ms<<endl;
    return 0;
}

