#include <iostream>
#include <windows.h>
int main(){

    DWORD t_start, t_end;
    t_start = GetTickCount();//�Ӳ���ϵͳ������������elapsed���ĺ����������ķ���ֵ��DWORD��
    Sleep(3000);
    t_end = GetTickCount();
    std::cout << t_end - t_start << std::endl;
    return 0;
}
