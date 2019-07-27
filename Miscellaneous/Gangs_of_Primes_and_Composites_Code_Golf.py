import sys
import collections  

def dfs(x, y, isPrime):

    q = []
    q.append((y, x))

    while len(q) > 0:
        uy, ux = q.pop(0)
        v[uy][ux] = 1

        if uy>0 and v[uy-1][ux]==0 and p[a[uy - 1][ux]] == isPrime:
            q.append((uy-1, ux))

        if ux<m-1 and v[uy][ux+1]==0 and p[a[uy][ux+1]] == isPrime:
            q.append((uy, ux+1))

        if uy<n-1 and v[uy+1][ux]==0 and p[a[uy + 1][ux]] == isPrime:
            q.append((uy+1, ux))

        if ux>0 and v[uy][ux-1]==0 and p[a[uy][ux-1]] == isPrime:
            q.append((uy, ux-1))

    


a = m = n = v = None
p = [1] * 10001
p[0] = p[1] = 0
for i in range(100):
    if p[i] == 1:
        for j in range(i * i, 10001, i):
            p[j] = 0

t = int(input())
for tc in range(t):
    n, m = map(int, input().split())
    if m>100 or n>100:
        sys.exit(3)
    a = []
    for i in range(n):
        row = list(map(int, input().split()))
        if len(row) != m:
            sys.exit(4)
        a.append(row)
    
    

    for i in range(n):
        for j in range(m):
            if a[i][j] < 2 and a[i][j] > 10000:
                sys.exit(4)
    
    v = [[0] * m for i in range(n)]
    y = 0
    z = 0
    
    for i in range(n):
        for j in range(m):
            if v[i][j] == 0:
                isPrime = p[a[i][j]]
                dfs(j, i, isPrime)
                if tc == 1 and i==0 and j==0:
                    # sys.exit(5)
                    pass
                if isPrime == 1:
                    y += 1
                else:
                    z += 1
    print(y, z)
    
    
