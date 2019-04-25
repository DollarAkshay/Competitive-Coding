# ~~~~~~~~~~~~~~~~~ #
#                   #
#  Dollar Akshay$  #
#                   #
# ~~~~~~~~~~~~~~~~~ #

# https://www.hackerrank.com/challenges/matrix-rotation-algo/problem

import math
import os
import random
import sys


def printMatrix(a):
    for i in range(len(a)):
        for j in range(len(a[i])):
            print("{:d} ".format(a[i][j]), end="")
        print("")


m, n, rot = map(int, input().split())
matrix = []
for i in range(m):
    row = list(map(int, input().split()))
    matrix.append(row)

rings = min(m, n)//2

for ring in range(rings):
    perimeter = 2*(m + n - 4*ring - 2)
    rot_mod = rot % perimeter

    # Perform the rotations
    for r in range(rot_mod):
        new_matrix = [row[:] for row in matrix]

        # Top
        for i in range(1+ring, n-ring):
            new_matrix[ring][i-1] = matrix[ring][i]

        # Right
        for i in range(1+ring, m-ring):
            new_matrix[i-1][n-ring-1] = matrix[i][n-ring-1]

        # Bottom
        for i in range(1+ring, n-ring):
            new_matrix[m-ring-1][i] = matrix[m-ring-1][i-1]

        # Left
        for i in range(1+ring, m-ring):
            new_matrix[i][ring] = matrix[i-1][ring]

        matrix = [row[:] for row in new_matrix]

printMatrix(matrix)

# TLE
