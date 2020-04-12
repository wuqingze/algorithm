class Main:
    def __init__(self):
        self.dp = None
        self.flag = None

#    def f(self,A,B,i,j):
#        if i<0 or j<0:
#            return
#        if A[i] == B[j]:
#            self.f(A,B,i-1,j-1)
#            self.dp[i+1][j+1] = self.dp[i][j]+1
#            self.flag[i][j] = 'ok'
#        else:
#            self.f(A,B,i,j-1)
#            self.f(A,B,i-1,j)
#            if self.dp[i+1][j] > self.dp[i,j+1]:
#                self.dp[i+1][j+1] = self.dp[i+1][j]
#                self.flag[i+1][j+1] = 'up'
#            else:
#                self.dp[i][j+1]=self.dp[i][j+1]
#                self.flag[i+1][j+1]='left'
        

    def lcs(self, A, B):
        if A==None or A== '' or B==None or B=='':
            return ''
        n = len(A)
        m = len(B)
        dp = [[0 for i in range(m+1)] for j in range(n+1)]
        flag = [['' for i in range(m+1)] for j in range(n+1)]
        for i in range(n+1):
            for j in range(m+1):
                if i==0 or j==0:
                    dp[i][j] = 0
                elif A[i-1] == B[j-1]:
                    dp[i][j] = dp[i-1][j-1]+1
                    flag[i][j] = 'ok'
                else:
                    if dp[i-1][j] < dp[i][j-1]:
                        dp[i][j] = dp[i][j-1]
                        flag[i][j] = 'left'
                    else:
                        dp[i][j] = dp[i-1][j]
                        flag[i][j] = 'up'
        print(dp[n][m])
        for d in flag:
            print(d)
        self.printLcs(flag,A,n,m)
    def printLcs(self,flag,a,i,j):
        print(a)
        if i==0 or j==0:
            return
        if flag[i][j] == 'ok':
            self.printLcs(flag,a,i-1,j-1)
            print(a[i-1])
        elif flag[i][j] == 'left':
            self.printLcs(flag,a,i,j-1)
        else:
            self.printLcs(flag,a,i-1,j)

if __name__=='__main__':
    print('hello world')
    o = Main()
    a='ABCBDAB'
    b='BDCABA'
    o.lcs(a,b)
