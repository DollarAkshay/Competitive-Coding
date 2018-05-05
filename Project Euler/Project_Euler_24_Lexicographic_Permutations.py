# https://projecteuler.net/problem=24

import time


def permutation(index):
    global all_perm, array

    if index == len(array):
        string = ''.join([str(i) for i in array])
        all_perm.append(string)
    else:
        for i in range(index, len(array)):
            array[index], array[i] = array[i], array[index]
            permutation(index + 1)
            array[index], array[i] = array[i], array[index]


# Main
all_perm = []
array = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
permutation(0)
print("Number of Permutations : ", len(all_perm))
all_perm.sort()
print("Millionth permutation : ", all_perm[1000000 - 1])
