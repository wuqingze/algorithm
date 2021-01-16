### Heap

- **Definition**
    - Heap is an array
    - if a[i] is root, then a[2*i + 1] and a[2*i+2] are the children of a[i]
    - if Heap is Big Root Heap, then a[i] >= a[2*i + 1] and a[i] >= a[2*i+2]. 
      Otherwise if Heap is Small Root Heap, then a[i] <= a[2*i+1] and a[i] <= a[2*i + 2]

- **����**
    - if the depth of Heap is h, then the minimum size of node of Heap is `2^(h-1)` and the 
      maximum size of node of Heap is `2^h - 1`
    - if the size of Heap is n, then the depth of Heap is `lg(n+1)`
![ ͼ6-1](./img/heap.jpg)
<div>
һ������(�����)�ɱ�����a)һ�ö�������b)һ�����顣ԲȦ�е����ֱ�ʾ����ÿ�����洢��ֵ������Ϸ������ֱ�ʾ��Ӧ�������±ꡣ�������µ����߱�ʾ���ӹ�ϵ���Ҹ���������ӽ�����ߡ�������ĸ߶�Ϊ3���洢ֵΪ8��4�Ž��ĸ߶�Ϊ1
<div>
