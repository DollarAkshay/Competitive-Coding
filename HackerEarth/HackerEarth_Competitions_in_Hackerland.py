import matplotlib.pyplot as plt
import math


def calculateForce(pos):
    res = 0
    for i in range(n):
        if pos >= dist[i]:
            res -= power[i] / math.log2(2 + pos - dist[i])
        else:
            res += power[i] / math.log2(2 + dist[i] - pos)
    return res


# Main Code
n = int(input())
dist = [float(i) for i in input().split()]
power = [float(i) for i in input().split()]

low = min(dist) - 1
high = max(dist) + 1
division = 10000

x = [low + (high - low) * i / division for i in range(division)]
y = [calculateForce(i) for i in x]
plt.grid(True)
plt.plot(x, y, 'k,')
plt.show()
