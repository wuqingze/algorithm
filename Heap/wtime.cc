#include <iostream>
#include <windows.h>
int main(){

    DWORD t_start, t_end;
    t_start = GetTickCount();//从操作系统启动所经过（elapsed）的毫秒数，它的返回值是DWORD。
    Sleep(3000);
    t_end = GetTickCount();
    std::cout << t_end - t_start << std::endl;
    return 0;
}
