/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/84939e4/

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

ll int x[3000];
ll int y[3000];
ll int f[3000];
ll int n;
double DP[3001];
bool calc[3001];

double dist(int a, int b) {
	return sqrt((double)(x[a] - x[b]) * (x[a] - x[b]) + (double)(y[a] - y[b]) * (y[a] - y[b]));
}

double solve(int city, bool last) {

	if (last) {
		return f[n - 1] - dist(city, n - 1);
	}

	if (calc[city + 1] == true) {
		return DP[city + 1];
	}

	else {
		double res = 0;
		FOR(i, city + 1, n - 2) {
			if (i != n - 2) {
				res = max(res, solve(i, 0) + f[i] - dist(city, i));
			}
			res = max(res, solve(i, 1) + f[i] - dist(city, i));
		}

		DP[city + 1] = res;
		calc[city + 1] = true;
	}

	return DP[city + 1];
}

int main() {

	scanf("%lld", &n);
	REP(i, n) {
		scanf("%lld %lld %lld", &x[i], &y[i], &f[i]);
	}

	printf("%lf\n", max(solve(0, 0), solve(0, 1)) + f[0]);

	return 0;
}

//