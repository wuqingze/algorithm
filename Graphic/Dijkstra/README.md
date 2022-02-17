#### 无向图单源最短路径算法/Dijkstra/狄克斯特拉算法
Dijkstra算法是求无向有权图中两点间最短路径的算法，具体的算法
描述在下面。
假设我们开始的源点为s,结束节点为e,设3个变量S,U,D,S表示访问过的且已知
已知距源点s最短距离的节点，U为还不知距源点最短距离的节点，D[0,...,n-1]
中，D[i]表示节点i到节点s的最短距离，其中D[s]=0,一开始，若i,j,k为源点s的
邻接节点，那么D[i]=W(s->i),D[j]=W(s->j),D[k]=W(s->k),其中W表示边的权值，
如果l节点不与s节点邻接，那么D[l]的初始值为正无穷。

算法思路
- 取D中的最小值所对应的节点，该节点加入S中，从U中删除
- 假设i为D中最小值对应节点，j,k为i的邻接节点且目前还不确定到源点s最小距离的
节点，那么如果D[j]>D[i]+W(i->j),那么D[j]更新为D[j]=D[i]+W(i->j)，同理，如果
节点k满足上述条件，做类似的更新
- 重复步骤一，直至从D中取出的节点为目标节点e

Dijkstra算法本质是一种贪心算法，当然这里最关键的是更新D中的值后，再从D中取
出最小值，这一过程是计算可行的。所以这里需要引入小根堆的方法，每次取最小值，
只要取堆顶值即可，然后删除堆顶，更新的过程也很直观，如果D中节点值变小了，
那么我们需要将节点向堆顶方向更新。

具体的代码实现在[这里](./Solution.cc)