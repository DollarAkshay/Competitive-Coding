#~~~~~~~~~~~~~~~~~~#
#                  #
#  $DollarAkshay$  #
#                  #
#~~~~~~~~~~~~~~~~~~#

# https://www.hackerrank.com/challenges/battleship1p

import math
import random
import os
import sys


def getPreviousBoardState(n):
    prev_board = []
    ships_left = []
    if os.path.isfile('prev_state'):
        with open("prev_state", "r") as f:
            for i in range(n):
                line = f.readline()
                prev_board.append(line)
            ships_left = list(map(int, f.readline().split()))
    else:
        prev_board = ['-' * 10 for i in range(n)]
        ships_left = [2, 2, 3, 4, 5]
    return (prev_board, ships_left)


def writeBoardState(board, n, ships_left):
    with open("prev_state", "w") as f:
        for i in range(n):
            f.write(board[i] + '\n')
        f.write(' '.join(map(str, ships_left)) + '\n')


def returnShipDestroyed(prev_board, board):
    diff = 0
    for i in range(n):
        for j in range(10):
            if prev_board[i][j] != board[i][j] and board[i][j] == 'd':
                diff += 1
    return diff


def checkHorizontalPlacement(i, j, ship, n):
    hit_count = 0
    placeable = True
    for k in range(ship):
        if j + k < 10:
            if board[i][j + k] == 'm' or board[i][j + k] == 'd':
                placeable = False
                break
            elif board[i][j + k] == 'h':
                hit_count += 1
        else:
            placeable = False
            break
    return (placeable, hit_count)


def checVerticalPlacement(i, j, ship, n):
    hit_count = 0
    placeable = True
    for k in range(ship):
        if i + k < n:
            if board[i + k][j] == 'm' or board[i + k][j] == 'd':
                placeable = False
                break
            elif board[i + k][j] == 'h':
                hit_count += 1
        else:
            placeable = False
            break
    return (placeable, hit_count)


def getDensityMap(board, n, ships_left):
    HIT_SCORE = 50
    density_map = [[0] * 10 for i in range(n)]
    for ship in ships_left:
        for i in range(n):
            for j in range(10):
                placeable, hit_count = checkHorizontalPlacement(i, j, ship, n)
                if placeable:
                    for k in range(ship):
                        if board[i][j + k] == '-':
                            density_map[i][j + k] += 1 + hit_count * HIT_SCORE

                placeable, hit_count = checVerticalPlacement(i, j, ship, n)
                if placeable:
                    for k in range(ship):
                        if board[i + k][j] == '-':
                            density_map[i + k][j] += 1 + hit_count * HIT_SCORE

    for i in range(n):
        for j in range(10):
            print(" {:4d}".format(density_map[i][j]), end="", file=sys.stderr)
        print("\n", end="", file=sys.stderr)
    return density_map


def getMove(board, n, ships_left):
    density_map = getDensityMap(board, n, ships_left)
    maxVal = 0
    maxPos = []
    for i in range(n):
        for j in range(10):
            if density_map[i][j] > maxVal:
                maxPos = [(i, j)]
                maxVal = density_map[i][j]
            elif density_map[i][j] == maxVal:
                maxPos.append((i, j))

    print("Possible Moves :", maxPos, file=sys.stderr)
    return random.choice(maxPos)


# ~~~ Main Code ~~~
random.seed(1995)

n = int(input())
prev_board, ships_left = getPreviousBoardState(n)
board = []
for i in range(n):
    line = input()
    board.append(line)

destroyedShip = returnShipDestroyed(prev_board, board)
print("Ships Left :", ships_left, file=sys.stderr)
print("Destroyed Ship :", destroyedShip, file=sys.stderr)
if destroyedShip in ships_left:
    ships_left.remove(destroyedShip)

move_y, move_x = getMove(board, n, ships_left)
print(move_y, move_x)

writeBoardState(board, n, ships_left)

# Random Seed Scores :
# 1995 - 60.0
