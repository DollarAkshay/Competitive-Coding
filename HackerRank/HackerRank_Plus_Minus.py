# ~~~~~~~~~~~~~~~~~ #
#                   #
#  $Dollar Akshay$  #
#                   #
# ~~~~~~~~~~~~~~~~~ #

# https://www.hackerrank.com/challenges/plus-minus/problem

n = int(input())
a = list(map(int, input().split()))
pos, neg, zer = 0, 0, 0

for x in a:
    if x > 0:
        pos += 1
    elif x < 0:
        neg += 1
    else:
        zer += 1

print(pos/n)
print(neg/n)
print(zer/n)
