import matplotlib.pyplot as plt
import math
import numpy as np


def updatePos():
    for i in range(len(pos)):
        pos[i] += dir[i] * res
        pos[i] = round(pos[i], 2)

    for i in range(len(pos)):
        if pos[i] <= 1 or pos[i] >= l:
            dir[i] = -dir[i]
        if (i > 0 and pos[i] == pos[i - 1]) or (i < n - 1 and pos[i] == pos[i + 1]):
            dir[i] = -dir[i]


# Main Code

l, n, q = [int(i) for i in input().split()]
pos = [int(i) for i in input().split()]
dir = [int(i) * 2 - 1 for i in input().split()]

t = 20
res = 0.5

x = [[i] for i in pos]
y = [[0] for i in pos]

for i in range(int(t / res)):
    updatePos()
    for j in range(len(pos)):
        x[j].append(pos[j])
        y[j].append((i + 1) * res)


fig, ax = plt.subplots()
# Major ticks every 20, minor ticks every 5
major_ticks = np.arange(0, 101, 1)
minor_ticks = np.arange(0, 101, 0.5)

ax.set_xticks(major_ticks)
ax.set_xticks(minor_ticks, minor=True)
ax.set_yticks(major_ticks)
ax.set_yticks(minor_ticks, minor=True)

# And a corresponding grid
ax.grid(which='both')
ax.grid(which='minor', alpha=0.2)

for i in range(len(pos)):
    ax.plot(x[i], y[i], 'o-')

plt.show()
