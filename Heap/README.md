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

### 优先队列

虽然堆排序算法是一个很漂亮的算法，但是在实际中，快速排序一个好的实现往往好于
堆排序。尽管如此，堆数据结构还是有着很大的用处，一个很常见的应用是优先队列(priority queue).

优先队列的一个应用是在一台分时计算机上进行作业调度。如果一个作业做完或者被中断，
用top()操作从所有等待的作业中，选择出具有最高优先级的作业。任何时候，一个新的作业
或者中断的作业都可以通过insert操作加入到队列中。比如，一个被中断的作业，操作系统可以
先通过insert操作插入队列中，然后用top操作取出最大优先级的作业继续执行。

- **定义堆结构**
```
template<typename T>
struct PriorityQueue{
    int len = 0;            //节点数
    int capability = 1024;  //树的空间大小，默认是1024，可以按照2倍的速率增长
    T* arr;                 //存储节点的空间
}
```
- **insert方法**
    - 如果空间不够，需要扩展空间 
        ```
            if(len == capability){
                capability = capability * 2;
                T *t = (T*) malloc(sizeof(T) * capability);
                memcpy(t, arr, capability/2);
                delete arr;
                arr = t;
            }
        ```

     - 将节点添加到数组尾部后，并自底向上调整堆的结构
        ```
        void maintainHeap(){
            int index = len-1;
            while(index>0){
                int parent = (index -1)/2;
                if(arr[parent] < arr[index]){
                    exchagne(index, parent);
                    index = parent;
                }else break;
            }
        }
        ```

- **top方法**

    top方法将堆中的根节点弹出并返回。如果堆中没有节点，抛出异常，取到根节点，然后将
    根节点换成最后一位元素。然后通过maxHeap操作自顶向下维持堆的结构。

    ```
    T top(){
        if(len == 0) throw "priority queue is empty!";
        auto result = arr[0];
        arr[0] = arr[--len];
        maxHeap();
        return result;
    }
    ```

- **动态扩张和内存拷贝**
    - 按原来堆空间的2倍大小申请新空间
    - 通过`memcpy(void *dest, void *src, int offset)`方法拷贝原堆的内存到目标堆，`memcpy`方法
    在头文件`string.h`中
    - 通过`delete src`释放原堆空间
    - 将堆指针指向新分配的内存空间

    ***示例***
    ```
    if(len == capability){
        capability = capability * 2;
        T *t = (T*) malloc(sizeof(T) * capability);
        memcpy(t, arr, capability/2);
        delete arr;
        arr = t;
    }
    ``` 

- **[CPP代码实现](./code/PriorityQueue.cc)**
