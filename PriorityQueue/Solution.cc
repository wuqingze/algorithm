#include<iostream>
#include <queue>
using namespace std;
int main() 
{
    //���ڻ������� Ĭ���Ǵ󶥶�
    priority_queue<int> a; 
    //��ͬ�� priority_queue<int, vector<int>, less<int> > a;
    
    //             ����һ��Ҫ�пո񣬲�Ȼ���������������
    priority_queue<int, vector<int>, greater<int> > c;  //��������С����
    priority_queue<string> b;

    auto cmp = [](int &a, int &b) { return a>b;};
    priority_queue<int, vector<int>, decltype(cmp)> d(cmp);

    for (int i = 0; i < 5; i++) 
    {
        a.push(i);
        c.push(i);
        d.push(i);
    }
    while (!a.empty()) 
    {
        cout << a.top() << ' ';
        a.pop();
    } 
    cout << endl;

    while (!c.empty()) 
    {
        cout << c.top() << ' ';
        c.pop();
    }
    cout << endl;

    while (!d.empty()) 
    {
        cout << d.top() << ' ';
        d.pop();
    } 
    cout << endl;

    b.push("abc");
    b.push("abcd");
    b.push("cbd");
    while (!b.empty()) 
    {
        cout << b.top() << ' ';
        b.pop();
    } 
    cout << endl;
    return 0;
}
