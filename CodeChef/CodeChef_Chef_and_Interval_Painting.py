'''
Python Visulization for CodeChef
'''

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

matrix = np.array([
    [1, 0, 0, 0, 0],
    [3, 5, 0, 0, 0],
    [6, 17, 34, 0, 0],
    [10, 45, 130, 289, 0],
    [15, 100, 410, 1219, 2921],
    [21, 196, 1106, 4375, 13391],
    [28, 350, 2632, 13643, 53284],
    [36, 582, 5664, 37731, 186516],
    [45, 915, 11235, 94278, 94278, ],
    [55, 1375, 20845, 216238, 216238],
    [66, 1991, 36586, 461274, 461274],
    [78, 2795, 61282, 925002, 925002],
    [91, 3822, 98644, 1759030, 1759030],
    [105, 5110, 153440, 3194842, 3194842],
    [120, 6700, 231680, 5574682, 5574682],
    [136, 8636, 340816, 340816, 340816],
    [153, 10965, 489957, 489957, 489957],
    [171, 13737, 690099, 690099, 690099],
    [190, 17005, 954370, 954370, 954370],
    [210, 20825, 1298290, 1298290, 1298290]
])

fig = plt.figure()
ax = fig.gca(projection='3d')

# Make data.
X = np.arange(1, 6, 1)
Y = np.arange(1, 21, 1)
X, Y = np.meshgrid(X, Y)

Z = np.power(matrix, 0.4)

# Plot the surface.
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)

ax.zaxis.set_major_locator(LinearLocator(5))
ax.zaxis.set_major_formatter(FormatStrFormatter('%d'))

# Add a color bar which maps values to colors.
fig.colorbar(surf, shrink=0.5, aspect=5)

plt.show()
