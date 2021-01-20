## Heap

- **Definition**
    - Heap is an array
    - if a[i] is root, then a[2*i + 1] and a[2*i+2] are the children of a[i]
    - if Heap is Big Root Heap, then a[i] >= a[2*i + 1] and a[i] >= a[2*i+2]. 
      Otherwise if Heap is Small Root Heap, then a[i] <= a[2*i+1] and a[i] <= a[2*i + 2]

- **性质**
    - if the depth of Heap is h, then the minimum size of node of Heap is `2^(h-1)` and the 
      maximum size of node of Heap is `2^h - 1`
    - if the size of Heap is n, then the depth of Heap is `lg(n+1)`

- cpp 11 时间函数chrono

```
#include <chrono>

using namespace std::chrono;

auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
auto stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).cout();
```
![ 图6-1](./img/heap.jpg)
<div>
一个最大堆(大根堆)可被看作a)一棵二叉树和b)一个数组。圆圈中的数字表示树中每个结点存储的值，结点上方的数字表示对应的数组下标。数组上下的连线表示父子关系，且父结点总在子结点的左边。这棵树的高度为3，存储值为8的4号结点的高度为1
<div>

### 堆排序

- **通过递归的方法保持大根堆的性质**
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

- **性质1** 如果一个堆的节点数为n，那么该堆的叶子节点为( └n/2┘+1, └n/2┘+2, ... , n )

    证明`性质1`，我们需要做到
    - 证明└n/2┘+1不存在叶子节点
    - 证明└n/2┘存在叶子节点

    ***证明***

    ```
    我们知道堆中，所有节点i,有两个子节点2*i, 2*i+1。设I=└n/2┘. 那么2*(I+1)=n+2>n,可以知道节点I+1
    不存在叶子节点。2*I=n,n为堆中的节点，可以知道I存在叶子节点。综上，性质1成立。

    ```

- **建堆**

    我们知道`性质1`，那么可以采用自底向上的方法构建堆
    ```
    buildHeap(A):
        n = len(A)
        for i in └n/2┘ down to 1:
            maxHeap(A, i)
    ```

- **堆排序**

    假设我们有一个大根堆，堆节点数为n,我们可以通过置换根节点和n节点，每次将最大数根节点放到n的位置，
    然后再通过维护堆的操作，确保堆的性质不被改变。

    ```
    HeapSort(A):
        n = len(A)
        buildHeap(A)
        for i in n down to 2:
            exchange(A, 0, i)
            set A size = i-1
            maxHeap(A)

    ```

- **[CPP代码实现](./code/Solution.cc)**

