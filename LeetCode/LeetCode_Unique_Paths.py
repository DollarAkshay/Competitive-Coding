
# https://leetcode.com/problems/unique-paths-iii/


class Solution:

    def uniquePathsIII(self, grid_: List[List[int]]) -> int:

        global n, m, v, grid

        grid = grid_.copy()
        n = len(grid)
        m = len(grid[0])

        start_x = -1
        start_y = -1
        z = 1
        for i, row in enumerate(grid):
            for j, cell in enumerate(row):
                if cell == 0:
                    z += 1
                if cell == 1:
                    start_x, start_y = j, i

        v = [[0] * m for i in range(n)]
        res = dfs(start_x, start_y)
        return res


# Main Code
n = -1
m = -1

v = []
grid = []


def dfs(x, y, z):

    global n, m, v, grid

    if grid[y][x] == 2:
        if z == 0:
            return 1
        else:
            return 0

    v[y][x] = 1

    res = 0
    # Left
    if x > 0 and v[y][x - 1] == 0 and grid[y][x - 1] != -1:
        res += dfs(x - 1, y, z - 1)

    # Right
    if x < m - 1 and v[y][x + 1] == 0 and grid[y][x + 1] != -1:
        res += dfs(x + 1, y, z - 1)

    # Up
    if y > 0 and v[y - 1][x] == 0 and grid[y - 1][x] != -1:
        res += dfs(x, y - 1, z - 1)

    # Down
    if y < n - 1 and v[y + 1][x] == 0 and grid[y + 1][x] != -1:
        res += dfs(x, y + 1, z - 1)

    v[y][x] = 0

    return res
