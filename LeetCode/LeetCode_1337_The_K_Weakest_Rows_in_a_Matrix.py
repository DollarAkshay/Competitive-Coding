from bisect import bisect_left
import numpy as np
import heapq


class Node:
    def __init__(self, d: dict):
        self.val = d['val']
        self.idx = d['idx']

    def __lt__(self, other):
        return self.val < other.val or (self.val == other.val and self.idx < other.idx)


class Solution(object):
    def kWeakestRows(self, mat, k):

        heap = []
        for i in range(len(mat)):
            heap.append(Node({'val': np.sum(mat[i]), 'idx': i}))
        heapq.heapify(heap)

        res = []
        for _ in range(k):
            node = heapq.heappop(heap)
            res.append(node.idx)

        return res


if __name__ == '__main__':
    s = Solution()
    mat = [[1, 1, 0, 0, 0],
           [1, 1, 1, 1, 0],
           [1, 0, 0, 0, 0],
           [1, 1, 0, 0, 0],
           [1, 1, 1, 1, 1]]
    print(s.kWeakestRows(mat, 3))
