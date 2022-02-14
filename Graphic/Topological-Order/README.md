**Directed Acycline Graph(有向无环图)**

**拓扑系列**： 设$G=(V,E)$是一个有n个顶点的有向图，V中的顶点系列$V_1,V_2,.....,V_n$满足从
顶点$V_i$到$V_j$有一条路径，则在顶点序列中顶点$V_i$必在顶点$V_j$之前。则我
们称这样的顶点序列为一个拓扑序列。或者换一种更直观的说法，加入存在$V_0,V_1,
.....,V_n$是拓扑系列，那么任意i,j，(i<j)，有从顶点$V_i$到顶点$V_j$的路径。
若没有这样的路径，那么$V_{i+1}$->$V_j$中一定有这样的路径.

**拓扑排序:** 所谓的拓扑排序，其实就是对一个有向无环图构造拓扑序列的过程

拓扑排序的算法步骤很简单，就是两步：
- 在有向图中选一个没有前驱的顶点且输出之。
- 从图中删除该顶点和所有以它为尾的弧。重复上述两步，直至全部顶点均已输出，或者当前图不存在无前驱的顶点为止，后一种情况说明有向图中存在环。

上面的算法也被称之为kahn算法。

同时拓扑排序也可以用来判断一个有向图是不是无环图，即排序的最后，生成的拓扑系列
是不是包含图中的所有顶点，如果全包含，则是无环图，如果不全包含，则存在。原理就是
存在环的有向图，肯定存在一个子图，这个子图中没有一个顶点的入度是为0的，算法就
没法继续进行，所以最后必定存在剩余的节点没有排序。

##### 拓扑排序的运用

[leetcode 207. Course Schedule](https://leetcode.com/problems/course-schedule/)

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where $prerequisites[i] = [a_i, b_i]$ indicates that you **must** take course $b_i$ first if you want to take course $a_i$.

- For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

**解法**

这道题可以转化成一个有向图中存不存在环，可以用拓扑排序来判断存不存在有向图，即khan算法.

**同时拓扑排序也是求关键路径的基础**,关键路径在现实中有很重要的应用，比如节约工程成本。
