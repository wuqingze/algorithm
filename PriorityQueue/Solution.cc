#include<iostream>
#include <queue>
using namespace std;
int main() 
{
    //对于基础类型 默认是大顶堆
    priority_queue<int> a; 
    //等同于 priority_queue<int, vector<int>, less<int> > a;
    
    //             这里一定要有空格，不然成了右移运算符↓
    priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆
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
