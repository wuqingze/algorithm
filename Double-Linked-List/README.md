### 双向链表
双向链表非常直观了，有一个pre指针，一个next指针。需要注意的是
为了避免一系列的空指针和额外操作的问题，需要head和tail两个指针
分别存在头和尾。初始化时，head->next = tail; tail->pre = head
这两个操作是必须要注意的。

问题一：凯撒密码
![](./imgs/1-kaisa-password.jpg)

[跳表](./Skip-List/README.md)
