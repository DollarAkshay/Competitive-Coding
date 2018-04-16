# https://www.hackerearth.com/challenge/college/game_of_codes_5/algorithm/strange-sequence/

t = int(input())
for tc in range(t):
    _ = input()
    a = list(map(int, input().split()))
    prev = -1
    freq = []
    prevChar = []
    for bit in a:
        if prev == bit:
            freq[-1] += 1
        else:
            prev = bit
            freq.append(1)
            prevChar.append(prev)

    if len(freq) <= 3:
        print(sum(freq))
    else:
        res = 0
        for i in range(len(freq) - 2):
            if prevChar[i] == 0 and i <= len(freq) - 4:
                res = max(res, sum(freq[i:i + 4]))
            res = max(res, sum(freq[i:i + 3]))
        print(res)
