# https://projecteuler.net/problem=15


def recursiveDP(x, y):
    global n, m, DP
    if x > m or y > n:
        return 0
    elif x == m and y == n:
        return 1
    elif DP[y][x] != 0:
        return DP[y][x]
    else:
        DP[y][x] = recursiveDP(x + 1, y) + recursiveDP(x, y + 1)
        return DP[y][x]


m = 20
n = 20

DP = [[0 for j in range(m + 1)] for i in range(n + 1)]
print("Solving for {:d} x {:d} matrix : ", recursiveDP(0, 0))
