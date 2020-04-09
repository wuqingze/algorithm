class Main:
    def __init__(self):
        pass

    def __init__(self, arr):
        n = len(arr)
        self.heap = [0x7fffffff]*n
        self.size = 0
        for i in range(n):
            self.insert(arr[i])

    def insert(self,num):
        self.heap[self.size] = num
        self.shiftUp(self.size)
        self.size += 1

    def remove(self):
        self.heap[0] = self.heap[self.size-1]
        self.heap[self.size-1] = 0x7fffffff
        self.shiftDown(0)
        self.size -= 1
        
    def top(self):
        if self.size<=0:
            return None
        r = self.heap[0]
        self.heap[0] = self.heap[self.size-1]
        self.heap[self.size-1] = 0x7fffffff
        self.size -= 1
        self.shiftDown(0)
        return r

    def shiftUp(self, leaf):
        cur = leaf
        temp = self.heap[leaf]
        while cur > 0:
            p = (cur -1)//2
            if self.heap[p] > self.heap[cur]:
                t = self.heap[cur]
                self.heap[cur] = self.heap[p]
                self.heap[p] = t
                cur = p
            else:
                break
        self.heap[cur] = temp

    def shiftDown(self, root):
        cur = root
        n = len(self.heap)
        temp = self.heap[cur]
        while cur < n -1:
            child = cur * 2 + 1
            if child > n -1:
                break
            if child + 1 < n and self.heap[child] > self.heap[child+1]:
                child = child + 1
            
            if self.heap[cur] < self.heap[child]:
                break
            else:
                t = self.heap[cur] 
                self.heap[cur] = self.heap[child]
                self.heap[child] = t
                cur = child
        self.heap[cur] = temp


def topn(arr,n):
    if None == arr or [] == arr or n<0 or n>len(arr):
        return None
    o = Main(arr)
    t = None
    print(o.heap)
    for i in range(n):
        t = o.top()
        print("top===", o.heap)
    return t 

if __name__ == '__main__':
#    print('hello world')
#    print(topn([1,2,2],2))
#    print(topn([4,3,2,1],2))
#    print(topn([3,2,1],1))
#    print(topn([1],1))
#    print(topn([],1))
#    print(topn([1,2,3,4],1))
#n    print(topn([9,8,7,6,5,4,3,2,1],1))
    print(topn([9,8,7,6,5,4,3,2,1],1))
    print(topn([9,8,7,6,5,4,3,2,1],2))
    print(topn([9,8,7,6,5,4,3,2,1],3))
    print(topn([9,8,7,6,5,4,3,2,1],4))
    print(topn([9,8,7,6,5,4,3,2,1],5))
    print(topn([9,8,7,6,5,4,3,2,1],6))
    print(topn([9,8,7,6,5,4,3,2,1],7))
    print(topn([9,8,7,6,5,4,3,2,1],8))
    print(topn([9,8,7,6,5,4,3,2,1],9))
