# https://www.hackerearth.com/challenge/college/game_of_codes_5/algorithm/question-1-138/

t = int(input())
for tc in range(t):
    x, y, a, b = map(int, input().split())
    if x**y > a**b:
        print("x^y")
    else:
        print("a^b")
