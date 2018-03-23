/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/the-cgi-dream-builder-challenge/problems/ee293e7d96e2414199ebcfeecf60a51b/

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

ll int a[1000000];

ll int fastPowMod(ll int b, ll int e) {
	if (e == 0) {
		return 1;
	}
	else if (e % 2 == 1) {
		return fastPowMod(b, e - 1) * b;
	}
	else {
		ll int res = fastPowMod(b, e / 2);
		return (res * res) % MOD;
	}
}

ll int solve(int n, int k) {
	ll int res = MOD;
	REP(i, n - 1) {
		ll int val = fastPowMod(abs(a[i] - a[i + 1]), k) * fastPowMod(abs(a[i] + a[i + 1]), k) % MOD;
		res = min(res, val);
	}
	return res;
}

ll int bf(int n, int k) {
	ll int res = MOD;
	REP(i, n) {
		FOR(j, i + 1, n - 1) {
			ll int val = fastPowMod(abs(a[i] * a[i] - a[j] * a[j]), k);
			res = min(res, val);
		}
	}
	return res;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, k;
		scanf("%d %d", &n, &k);
		REP(i, n) {
			scanf("%lld", &a[i]);
		}
		SORT(a, n);

		printf("%lld\n", bf(n, k));
	}
	return 0;
}

//Not solved