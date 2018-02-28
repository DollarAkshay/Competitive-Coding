/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-circuits-18/approximate/competition-in-hackerland-ec730844/

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

const long double delta = 1e-10;
int n;
pair<long double, long double> p[5000];

long double findTotalPower(long double trophyPos) {

	long double res = 0;
	REP(i, n) {
		if (trophyPos >= p[i].first) {
			res -= p[i].second / log2l(2 + trophyPos - p[i].first);
		}
		else {
			res += p[i].second / log2l(2 + p[i].first - trophyPos);
		}
	}

	// Negative value means left team has more power
	// Positive value means right team has more power
	return res;
}

long double binarySearch(long double low, long double high) {

	long double res = -1;
	while (low <= high) {
		res = (low + high) / 2;
		long double powMid = findTotalPower(res);
		if (powMid > 0) {
			high = res - delta;
		}
		else {
			low = res + delta;
		}
	}

	return res;
}

int main() {

	long double x;
	scanf("%d", &n);
	REP(i, n) {
		long double x;
		scanf("%llf", &x);
		p[i] = mp(x, 0);
	}

	REP(i, n) {
		scanf("%llf", &x);
		p[i].second = x;
	}

	SORT(p, n);
	vector<pair<long double, long double>> trophyRange;
	REP(i, n - 1) {
		long double lPower = findTotalPower(p[i].first + delta);
		long double rPower = findTotalPower(p[i + 1].first - delta);
		if (lPower < 0 && rPower > 0) {
			trophyRange.pb(mp(p[i].first + delta, p[i + 1].first - delta));
		}
	}

	vector<long double> res;

	REP(i, trophyRange.size()) {
		long double trophyPoint = binarySearch(trophyRange[i].first, trophyRange[i].second);
		res.push_back(trophyPoint);
	}

	printf("%d\n", res.size());
	REP(i, res.size()) {
		printf("%.10llf ", res[i]);
	}

	return 0;
}

//