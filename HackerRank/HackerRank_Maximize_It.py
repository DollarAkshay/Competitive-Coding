# ~~~~~~~~~~~~~~~~~ #
#                   #
#  $Dollar Akshay$  #
#                   #
# ~~~~~~~~~~~~~~~~~ #

# https://www.hackerrank.com/challenges/maximize-it/problem


def dfs(sum, pos):
    global best_val, a, k
    if pos == k:
        best_val = max(best_val, sum % m)
    else:
        for x in a[pos]:
            sum += x**2
            dfs(sum, pos+1)
            sum -= x**2


best_val = 0
k, m = map(int, input().split())
a = []
for i in range(k):
    x = list(map(int, input().split()))[1:]
    a.append(x)

dfs(0, 0)
print(best_val)
