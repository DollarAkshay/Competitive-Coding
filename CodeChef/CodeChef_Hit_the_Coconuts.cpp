/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JULY19A/problems/CCC

// #pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
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
#include <unordered_set>
#include <vector>

using namespace std;
using namespace std::chrono;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007
#define MAX 1000

int a[MAX];
int sum[MAX + 1];
ll int dp[MAX][MAX];

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, z;
		scanf("%d %d", &n, &z);
		REP(i, n) {
			scanf("%d", &a[i]);
		}

		SORT(a, n);
		sum[0] = 0;
		REP(i, n) {
			sum[i + 1] = sum[i] + a[i];
		}

		REP(i, n + 1) {
			REP(j, z + 1) {
				if (j == i) {
					dp[i][j] = sum[i];
				}
				else if (i == 0 || j == 0 || j > i) {
					dp[i][j] = 0;
				}
				else {
					dp[i][j] = min(a[i - 1] + dp[i - 1][j - 1], a[0] + dp[i - 1][j]);
				}
				// DB("%3d ", dp[i][j]);
			}
			// DB("\n");
		}

		ll int res = dp[n][z];
		printf("%lld\n", res);
	}
	return 0;
}

// Wrong Answer
