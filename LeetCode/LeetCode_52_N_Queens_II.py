import copy


class Solution:

    board = []
    res = 0

    def print_board(self):
        print("------")
        for row in self.board:
            print("".join(row))
        print("\n")

    def place_queen(self, n, row, col):

        for i in range(n):

            # Block the column
            self.board[i][col] = '.'

            # Block the Row
            self.board[row][i] = '.'

            # Block the left up diagonal
            if row - i >= 0 and col - i >= 0:
                self.board[row - i][col - i] = '.'

            # Block the left down diagonal
            if row + i < n and col - i >= 0:
                self.board[row + i][col - i] = '.'

            # Block the right down diagonal
            if row + i < n and col + i < n:
                self.board[row + i][col + i] = '.'

            # Block the right up diagonal
            if row - i >= 0 and col + i < n:
                self.board[row - i][col + i] = '.'

        self.board[row][col] = 'Q'

    def backtrack(self, n, k):
        if k >= n:
            self.res += 1
            return

        for i in range(n):
            if self.board[k][i] == ' ':
                board_copy = copy.deepcopy(self.board)
                self.place_queen(n, k, i)
                self.backtrack(n, k + 1)
                self.board = board_copy

    def totalNQueens(self, n):
        self.board = [[' ' for i in range(n)] for j in range(n)]
        self.res = 0
        self.backtrack(n, 0)
        return self.res


# if __name__ == '__main__':
#     s = Solution()
#     n = 1
#     print(s.totalNQueens(n))
