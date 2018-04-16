# https://www.hackerearth.com/challenge/college/game_of_codes_5/algorithm/question-3-65/

from bisect import bisect

n, q = map(int, input().split())

S = []
for i in range(n):
    S.append(input())

S = sorted(S)

for i in range(q):
    print(bisect(S, input()))
