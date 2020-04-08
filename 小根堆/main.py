class Main:
    def __init__(self):
        pass

    def __init__(self, arr, n):
        self.heap = [0x7fffffff]*n
        self.size = 0
        for i in range(n):
            self.insert(arr[i])
        for i in range(n,len(arr)):
            self.remove()
            self.insert(arr[i])

    def insert(self,num):
        self.heap[self.size] = num
        self.sihftUp(self.size)
        self.size += 1

    def remove(self):
        self.heap[0] = self.heap[self.size-1]
        self.heap[self.size-1] = 0x7fffffff
        self.shiftDown(0)
        self.size -= 1
        
    def top(self):
        return self.heap

    def shiftUp(self, leaf):
        cur = leaf
        temp = heap[leaf]
        while cur > 0:
            p = (cur -1)//2
            if self.heap[p] > self.heap[cur]:
                self.heap[cur] = self.heap[p]
                cur = p
            else:
                break
        heap[cur] = temp

    def sihftDown(self, root):
        cur = root
        n = len(self.heap)
        temp = self.heap[cur]
        while cur < n -1:
            child = cur * 2 + 1
            if child > n -1:
                break
            if child + 1 < n && self.heap[child] > self.heap[child+1]:
                child = child + 1
            
            if self.heap[cur] < self.heap[child]:
                break
            else:
                self.heap[cur] = self.heap[child]
                cur = child
        self.heap[cur] = temp


def topn(arr,n):
    if None == arr or [] == arr or n<0 or n>len(arr):
        return None

    o = Main(arr,n)
    return o.top()

if __name__ == '__main__':
    print('hello world')
    print(topn([1,2,2],2))
