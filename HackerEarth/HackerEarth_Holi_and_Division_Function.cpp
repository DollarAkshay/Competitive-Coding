/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/march-easy-18/algorithm/holi-and-division-function-1dfc3294/

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
#define MAX 100000

int f[MAX + 1];
int cf[MAX + 1];
int a[MAX];

bool calc[MAX + 1];
ll int DP[MAX + 1];

ll int solve(int n) {

	if (calc[n] == true) {
		return DP[n];
	}

	ll int res = 0;
	double divisor = 0.499999;
	while (true) {
		int r = min(MAX, (int)floor(n * (divisor + 1)));
		int l = floor(n * divisor);
		res += round((divisor + 0.5)) * (cf[r] - cf[l]);
		divisor += 1;
		if (r >= MAX) {
			break;
		}
	}

	calc[n] = true;
	DP[n] = res;

	return DP[n];
}

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		MSX(f, 0);
		MSX(DP, 0);
		MSX(calc, 0);
		MSX(cf, 0);
		scanf("%d", &n);
		REP(i, n) {
			scanf("%d", &a[i]);
			f[a[i]]++;
		}

		FOR(i, 1, MAX) {
			cf[i] = cf[i - 1] + f[i];
		}

		ll int res = 0;
		REP(i, n) {
			res += solve(a[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}

//Solved after Contest