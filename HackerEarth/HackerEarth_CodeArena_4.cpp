/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/edfa418/

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

int a[10001];
ll int DP[10001];

ll int solve(int liters) {

	if (DP[liters] >= 0) {
		return DP[liters];
	}

	if (liters == 0) {
		DP[liters] = 0;
	}
	else {
		ll int res = 0;
		FOR(i, 1, liters) {
			res = max(res, a[i] + solve(liters - i));
		}
		DP[liters] = res;
	}
	return DP[liters];
}

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		MSX(DP, -1);
		scanf("%d", &n);
		REP(i, n) {
			scanf("%d", &a[i + 1]);
		}
		printf("%lld\n", solve(n));
	}
	return 0;
}

//