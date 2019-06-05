/*~~~~~~~~~~~~~~~~~~*
*                  *
* $Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.hackerrank.com/challenges/mancala6

#include <algorithm>
#include <assert.h>
#include <bitset>
#include <ctype.h>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MS0(x) memset(x, 0, sizeof(x))
#define MS1(x) memset(x, 1, sizeof(x))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int matrix[300][300];
int new_matrix[300][300];

int main() {

	int m, n, rot;

	scanf("%d %d %d", &m, &n, &rot);
	REP(i, m) {
		REP(j, n) {
			scanf("%d", &matrix[i][j]);
		}
	}

	int rings = min(m, n) / 2;

	REP(ring, rings) {
		int perimeter = 2 * (m + n - 4 * ring - 2);
		int rot_mod = rot % perimeter;

		// Perform the rotations
		REP(r, rot_mod) {

			memcpy(new_matrix, matrix, sizeof(int) * 300 * 300);

			// Top
			FOR(i, 1 + ring, n - ring - 1) {
				new_matrix[ring][i - 1] = matrix[ring][i];
			}

			// Right
			FOR(i, 1 + ring, m - ring - 1) {
				new_matrix[i - 1][n - ring - 1] = matrix[i][n - ring - 1];
			}

			// Bottom
			FOR(i, 1 + ring, n - ring - 1) {
				new_matrix[m - ring - 1][i] = matrix[m - ring - 1][i - 1];
			}

			// Left
			FOR(i, 1 + ring, m - ring - 1) {
				new_matrix[i][ring] = matrix[i - 1][ring];
			}

			memcpy(matrix, new_matrix, sizeof(int) * 300 * 300);
		}
	}

	REP(i, m) {
		REP(j, n) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}

//Solved