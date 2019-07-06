
# https://leetcode.com/problems/unique-paths-iii/


class Solution:

    n = -1
    m = -1
    z = 1

    v = []
    grid = []

    def dfs(self, x, y):

        if self.grid[y][x] == 2 and self.z == 0:
            return 1

        self.v[y][x] = 1
        self.z -= 1

        res = 0
        # Left
        if x > 0 and self.v[y][x - 1] == 0 and self.grid[y][x - 1] != -1:
            res += self.dfs(x - 1, y)

        # Right
        if x < self.m - 1 and self.v[y][x + 1] == 0 and self.grid[y][x + 1] != -1:
            res += self.dfs(x + 1, y)

        # Up
        if y > 0 and self.v[y - 1][x] == 0 and self.grid[y - 1][x] != -1:
            res += self.dfs(x, y - 1)

        # Down
        if y < self.n - 1 and self.v[y + 1][x] == 0 and self.grid[y + 1][x] != -1:
            res += self.dfs(x, y + 1)

        self.v[y][x] = 0
        self.z += 1

        return res

    def uniquePathsIII(self, grid: List[List[int]]) -> int:

        self.grid = grid.copy()
        self.n = len(grid)
        self.m = len(grid[0])

        start_x = -1
        start_y = -1

        for i, row in enumerate(grid):
            for j, cell in enumerate(row):
                if cell == 0:
                    self.z += 1
                if cell == 1:
                    start_x, start_y = j, i
                if cell == 2:
                    self.end = [j, i]

        self.v = [[0] * self.m for i in range(self.n)]
        res = self.dfs(start_x, start_y)
        return res
