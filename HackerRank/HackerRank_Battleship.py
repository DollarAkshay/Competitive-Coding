#~~~~~~~~~~~~~~~~~~#
#                  #
#  $DollarAkshay$  #
#                  #
#~~~~~~~~~~~~~~~~~~#

# https://www.hackerrank.com/challenges/battleship

import math
import random
import os
import sys


def printShipCoordiantes():

    temp_board = [['-'] * 10 for i in range(10)]
    for ship in [1, 1, 2, 2, 3, 4, 5]:
        placed = False
        while placed is False:
            rand_x = random.randint(0, 9)
            rand_y = random.randint(0, 9)
            rand_orient = random.randint(0, 1)
            if rand_orient == 0:
                placeable, hit_count = checkHorizontalPlacement(temp_board, rand_y, rand_x, ship)
                if placeable:
                    placed = True
                    for k in range(ship):
                        temp_board[rand_y][rand_x + k] = 'd'
                    if ship == 1:
                        print("{:d} {:d}".format(rand_x, rand_y))
                    else:
                        print("{:d} {:d}:{:d} {:d}".format(rand_x, rand_y, rand_x + ship - 1,  rand_y))
            else:
                placeable, hit_count = checVerticalPlacement(temp_board, rand_y, rand_x, ship)
                if placeable:
                    placed = True
                    for k in range(ship):
                        temp_board[rand_y + k][rand_x] = 'd'
                    if ship == 1:
                        print("{:d} {:d}".format(rand_x, rand_y))
                    else:
                        print("{:d} {:d}:{:d} {:d}".format(rand_x, rand_y, rand_x,  rand_y + ship - 1))


def getPreviousBoardState():
    prev_board = []
    ships_left = []
    if os.path.isfile('prev_state'):
        with open("prev_state", "r") as f:
            for i in range(10):
                line = f.readline()
                prev_board.append(line)
            ships_left = list(map(int, f.readline().split()))
    else:
        prev_board = [['-'] * 10 for i in range(10)]
        ships_left = [1, 1, 2, 2, 3, 4, 5]
    return (prev_board, ships_left)


def writeBoardState(board, ships_left):
    with open("prev_state", "w") as f:
        for i in range(10):
            f.write(board[i] + '\n')
        f.write(' '.join(map(str, ships_left)) + '\n')


def returnShipDestroyed(prev_board, board):
    diff = 0
    for i in range(10):
        for j in range(10):
            if prev_board[i][j] != board[i][j] and board[i][j] == 'd':
                diff += 1
    return diff


def checkHorizontalPlacement(board, i, j, ship):
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


def checVerticalPlacement(board, i, j, ship):
    hit_count = 0
    placeable = True
    for k in range(ship):
        if i + k < 10:
            if board[i + k][j] == 'm' or board[i + k][j] == 'd':
                placeable = False
                break
            elif board[i + k][j] == 'h':
                hit_count += 1
        else:
            placeable = False
            break
    return (placeable, hit_count)


def getDensityMap(board, ships_left):
    HIT_SCORE = 50
    density_map = [[0] * 10 for i in range(10)]
    for ship in ships_left:
        for i in range(10):
            for j in range(10):
                placeable, hit_count = checkHorizontalPlacement(board, i, j, ship)
                if placeable:
                    for k in range(ship):
                        if board[i][j + k] == '-':
                            density_map[i][j + k] += 1 + hit_count * HIT_SCORE

                placeable, hit_count = checVerticalPlacement(board, i, j, ship)
                if placeable:
                    for k in range(ship):
                        if board[i + k][j] == '-':
                            density_map[i + k][j] += 1 + hit_count * HIT_SCORE

    for i in range(10):
        for j in range(10):
            print(" {:4d}".format(density_map[i][j]), end="", file=sys.stderr)
        print("\n", end="", file=sys.stderr)
    return density_map


def getMove(board, ships_left):
    density_map = getDensityMap(board, ships_left)
    maxVal = 0
    maxPos = []
    for i in range(10):
        for j in range(10):
            if density_map[i][j] > maxVal:
                maxPos = [(i, j)]
                maxVal = density_map[i][j]
            elif density_map[i][j] == maxVal:
                maxPos.append((i, j))

    print("Possible Moves :", maxPos, file=sys.stderr)
    return random.choice(maxPos[0])


# ~~~ Main Code ~~~
first_line = input()
if first_line == "INIT":
    printShipCoordiantes()
else:
    prev_board, ships_left = getPreviousBoardState()
    board = []
    for i in range(10):
        line = input()
        board.append(line)

    destroyedShip = returnShipDestroyed(prev_board, board)
    print("Ships Left :", ships_left, file=sys.stderr)
    print("Destroyed Ship :", destroyedShip, file=sys.stderr)
    if destroyedShip in ships_left:
        ships_left.remove(destroyedShip)

    move_y, move_x = getMove(board, ships_left)
    print(move_y, move_x)

    writeBoardState(board, ships_left)
