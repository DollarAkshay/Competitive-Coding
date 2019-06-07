/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JUNE19A/problems/LENTMO

#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

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
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

// a[0] will contain the normal values
// a[1] will contain the XOR values.
// a[2] = a[1] - a[0]
ll int a[3][1000000];

int main() {

	int t, n, k, x;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d", &n);
		REP(i, n) {
			scanf("%lld", &a[0][i]);
		}
		scanf("%d %d", &k, &x);

		REP(i, n) {
			a[1][i] = a[0][i] ^ x;
			a[2][i] = a[1][i] - a[0][i];
		}

		// Special Cases
		if (k == n) {
			ll int sum[2] = {0, 0};
			REP(i, n) {
				sum[0] += a[0][i];
				sum[1] += a[1][i];
			}
			printf("%lld\n", max(sum[0], sum[1]));
		}
		else if (k % 2 == 1) {
			ll int sum = 0;
			REP(i, n) {
				sum += max(a[0][i], a[1][i]);
			}
			printf("%lld\n", sum);
		}
		else {
			SORT(a[2], n);
			REV(a[2], n);

			ll int sum = 0;
			REP(i, n) {
				sum += a[0][i];
			}

			REP(i, n - 1) {
				if (a[2][i] + a[2][i + 1] >= 0) {
					sum += a[2][i] + a[2][i + 1];
				}
				i += 1;
			}
			printf("%lld\n", sum);
		}
	}
	return 0;
}

//Solved