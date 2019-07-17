/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codeforces.com/contest/1195/problem/E

#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

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

int h[3000][3000];
int minR[3000][3000];
int minC[3000][3000];

ll int bruteforce(int n, int m, int a, int b) {

	ll int res = 0;
	REP(i, n - a + 1) {
		REP(j, m - b + 1) {
			ll int minVal = (ll int)1E18;
			FOR(ai, i, i + a - 1) {
				FOR(bj, j, j + b - 1) {
					minVal = min(minVal, (ll int)h[ai][bj]);
				}
			}
			res += minVal;
			printf("%10d ", minVal);
		}
		printf("\n");
	}
	printf("\n\n");
	return res;
}

void print2DArray(int a[3000][3000], int n, int m) {

	REP(i, n) {
		REP(j, m) {
			printf("%10d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main() {

	int m, n, a, b;
	scanf("%d %d %d %d", &n, &m, &a, &b);

	int g0, x, y, z;
	scanf("%d %d %d %d", &g0, &x, &y, &z);

	// Calculate Original Matrix
	REP(i, n) {
		REP(j, m) {
			if (i == 0 && j == 0) {
				h[i][j] = g0;
			}
			else {
				int prevJ = j == 0 ? m - 1 : j - 1;
				int prevI = j == 0 ? i - 1 : i;
				h[i][j] = ((ll int)h[prevI][prevJ] * x + y) % z;
			}
		}
	}
	// print2DArray(h, n, m);

	// Do it for Rows
	REP(i, n) {
		deque<pii> dq;

		REP(j, b - 1) {
			while (!dq.empty() && h[i][j] < dq.back().second) {
				dq.pop_back();
			}
			dq.push_back(make_pair(j, h[i][j]));
		}

		FOR(j, b - 1, m - 1) {

			// Remove elements not part of this window
			while (!dq.empty() && dq.front().first <= j - b) {
				dq.pop_front();
			}
			// Remove useless elements
			while (!dq.empty() && h[i][j] < dq.back().second) {
				dq.pop_back();
			}

			dq.push_back(make_pair(j, h[i][j]));
			minR[i][j - b + 1] = dq.front().second;
		}
	}
	// print2DArray(minR, n, m - b + 1);

	// Do it for columns
	REP(j, m - b + 1) {

		deque<pii> dq;
		REP(i, a - 1) {
			while (!dq.empty() && minR[i][j] < dq.back().second) {
				dq.pop_back();
			}
			dq.push_back(make_pair(i, minR[i][j]));
		}

		FOR(i, a - 1, n - 1) {

			// Remove elements not part of this window
			while (!dq.empty() && dq.front().first <= i - a) {
				dq.pop_front();
			}
			// Remove useless elements
			while (!dq.empty() && minR[i][j] < dq.back().second) {
				dq.pop_back();
			}

			dq.push_back(make_pair(i, minR[i][j]));
			minC[i - a + 1][j] = dq.front().second;
		}
	}
	// print2DArray(minC, n - a + 1, m - b + 1);

	ll int res = 0;
	REP(i, n - a + 1) {
		REP(j, m - b + 1) {
			res += minC[i][j];
		}
	}

	// printf("BF   : %lld\n", bruteforce(n, m, a, b));
	printf("%lld\n", res);

	return 0;
}

//