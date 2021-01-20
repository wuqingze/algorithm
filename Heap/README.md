## Heap

- **Definition**
    - Heap is an array
    - if a[i] is root, then a[2*i + 1] and a[2*i+2] are the children of a[i]
    - if Heap is Big Root Heap, then a[i] >= a[2*i + 1] and a[i] >= a[2*i+2]. 
      Otherwise if Heap is Small Root Heap, then a[i] <= a[2*i+1] and a[i] <= a[2*i + 2]

- **����**
    - if the depth of Heap is h, then the minimum size of node of Heap is `2^(h-1)` and the 
      maximum size of node of Heap is `2^h - 1`
    - if the size of Heap is n, then the depth of Heap is `lg(n+1)`

- cpp 11 ʱ�亯��chrono

```
#include <chrono>

using namespace std::chrono;

auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
auto stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).cout();
```
![ ͼ6-1](./img/heap.jpg)
<div>
һ������(�����)�ɱ�����a)һ�ö�������b)һ�����顣ԲȦ�е����ֱ�ʾ����ÿ�����洢��ֵ������Ϸ������ֱ�ʾ��Ӧ�������±ꡣ�������µ����߱�ʾ���ӹ�ϵ���Ҹ���������ӽ�����ߡ�������ĸ߶�Ϊ3���洢ֵΪ8��4�Ž��ĸ߶�Ϊ1
<div>

### ������

- **ͨ���ݹ�ķ������ִ���ѵ�����**
```
maxHeap(arr, i)
    left = 2*i; right = 2*i+1
    if arr[i] >= left and arr[i] >= right
        return
    if arr[left] > arr[right]
        exchange(arr, i, left)
        maxHeap(arr, left)
    else
        exchange(arr, i, right)
        maxHeap(arr, right)
```

- **����1** ���һ���ѵĽڵ���Ϊn����ô�öѵ�Ҷ�ӽڵ�Ϊ( ��n/2��+1, ��n/2��+2, ... , n )

    ֤��`����1`��������Ҫ����
    - ֤����n/2��+1������Ҷ�ӽڵ�
    - ֤����n/2������Ҷ�ӽڵ�

    ***֤��***

    ```
    ����֪�����У����нڵ�i,�������ӽڵ�2*i, 2*i+1����I=��n/2��. ��ô2*(I+1)=n+2>n,����֪���ڵ�I+1
    ������Ҷ�ӽڵ㡣2*I=n,nΪ���еĽڵ㣬����֪��I����Ҷ�ӽڵ㡣���ϣ�����1������

    ```

- **����**

    ����֪��`����1`����ô���Բ����Ե����ϵķ���������
    ```
    buildHeap(A):
        n = len(A)
        for i in ��n/2�� down to 1:
            maxHeap(A, i)
    ```

- **������**

    ����������һ������ѣ��ѽڵ���Ϊn,���ǿ���ͨ���û����ڵ��n�ڵ㣬ÿ�ν���������ڵ�ŵ�n��λ�ã�
    Ȼ����ͨ��ά���ѵĲ�����ȷ���ѵ����ʲ����ı䡣

    ```
    HeapSort(A):
        n = len(A)
        buildHeap(A)
        for i in n down to 2:
            exchange(A, 0, i)
            set A size = i-1
            maxHeap(A)

    ```

- **[CPP����ʵ��](./code/Solution.cc)**

