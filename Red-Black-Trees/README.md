### properties of red-black trees
---------------------
A **red-black** is a binary search tree with one extra bit of storage per node:
its color, which can be either RED or BLACK. By constrainning the node colors
on any simpple path from root to a leaf, red-black trees ensure that no such
path is more than as long as other, so that tree is approximately balancedd.

Each node of the tree contains the attributes color, key, left, right, and parent.
If a cild or the parent of a node does not exist, the corresponding pointer attribute
of the node contains the value NIL.

![](./imgs/red-black-tree.jpg)
<center><b>Figure 1</b> An example of a red-black tree</center>

* Every node is either red or black
* The root is black
* Every leaf(NIL) is black
* If a node is red, then both its children are black
* For each node, all simple paths from the node to descendant leaves contain
the same number of black nodes

### RIGHT-ROTATE
```
RIGHT-ROTATE(T, y)
    x = y.left
    y.left = x.right
    if y.left
        y.left.parent = y

    x.right = y
    x.parent = y.parent
    y.parent = x
    if x.parent
        if x.parent.left = y
            x.parent.left = x
        elseif x.parent.right = y
            x.parent.right = x
```

### LEFT-ROTATE
```
LEFT-ROTATE(T, x)
    y =  x.right
    x.right = y.left
    if x.right
        x.right.parent = x
    y.left = x
    y.parent = x.parent
    x.parent = y
    if y.parent 
        if y.parent.left == x
           y.parent.left = y
        elseif y.parent.right == x
            y.parent.right = y
```
        



