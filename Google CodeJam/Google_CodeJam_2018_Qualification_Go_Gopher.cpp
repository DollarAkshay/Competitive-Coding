/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard/0000000000007a30

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
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
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d", &n);
		int rows = ceil((double)n / 3);
		bool a[1000][1000];
		MSX(a, 0);

		while (true) {
			int x, y;
			REP(i, rows) {
				bool found = false;
				REP(j, 3) {
					if (a[i][j] == false) {
						found = true;
						x = 1;
						y = i + 1;
					}
				}
				if (found) {
					break;
				}
			}

			printf("%d %d\n", x + 1, y + 1);
			fflush(stdout);
			int digX, digY;
			scanf("%d %d", &digX, &digY);
			if (digX == -1 && digY == -1) {
				// Test Case Failed
				return 0;
			}
			else if (digX == 0 && digY == 0) {
				// Test Case Pass
				break;
			}

			a[digY - 1][digX - 1] = true;
		}
	}
	return 0;
}

//