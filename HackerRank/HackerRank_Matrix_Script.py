# ~~~~~~~~~~~~~~~~~ #
#                   #
#  $Dollar Akshay$  #
#                   #
# ~~~~~~~~~~~~~~~~~ #

# https://www.hackerrank.com/challenges/matrix-script/problem

import re


def flatten(a, n, m):
    res = ""
    for j in range(m):
        for i in range(n):
            res += a[i][j]
    return res


n, m = map(int, input().split())

matrix = []
for _ in range(n):
    matrix_item = input()
    matrix.append(matrix_item)

decoded = flatten(matrix, n, m)
res = re.sub(
    r"([a-zA-Z0-9])(\W+)([a-zA-Z0-9])",
    r"\1 \3",
    decoded
)
print(res)
