/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://codejam.withgoogle.com/2018/challenges/0000000000007764/dashboard

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
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int c[100000];
bool r[100000];

int n, l;

int value() {
	int res = 0;
	REP(i, n) {
		res += round(100.0 * c[i] / n);
	}

	// if (res > 100) {
	// 	printf("Count :");
	// 	REP(i, n) {
	// 		printf(" %d", c[i]);
	// 	}
	// 	printf("\nRound :");
	// 	REP(i, n) {
	// 		printf(" %d", (int)round(100.0 * c[i] / n));
	// 	}
	// 	printf("\n");
	// }

	return res;
}

int recursiveDP(int rem) {

	if (rem == 0) {
		return value();
	}
	else {
		int maxVal = 0;
		REP(i, n) {
			c[i]++;
			maxVal = max(maxVal, recursiveDP(rem - 1));
			c[i]--;
		}
		return maxVal;
	}
}

int requireToRoundUp(int val, int maxVal) {
	int delta = 0;
	bool flag = false;
	while (delta <= maxVal) {
		double percent = 100.0 * (val + delta) / n;
		double fraction = percent - (int)percent;
		if (fraction >= 0.5000) {
			flag = true;
			break;
		}
		delta++;
	}

	return flag ? delta : -1;
}

int algo(int rem) {
	int newLang = requireToRoundUp(0, rem);

	vector<pii> delta;

	REP(i, l) {
		int val = requireToRoundUp(c[i], rem);
		if (val != -1 && (val < newLang || newLang == -1)) {
			delta.pb(mp(val, i));
		}
	}

	SORT(delta, delta.size());

	int roundUp = 0;
	REP(i, delta.size()) {
		if (rem >= delta[i].first) {
			rem -= delta[i].first;
			c[delta[i].second] += delta[i].first;
			roundUp++;
		}
	}
	printf("RU : %d\n", roundUp);

	if (newLang != -1) {
		roundUp += newLang / rem;
	}
	else {
		roundUp += round(100.0 * rem / n);
	}

	printf("NewLang = %d\n", newLang);

	REP(i, l) {
		roundUp += round(100.0 * c[i] / n);
	}

	return roundUp;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		MSX(c, 0);
		MSX(r, 0);
		scanf("%d %d", &n, &l);
		int surveyed = 0;
		REP(i, l) {
			scanf("%d", &c[i]);
			surveyed += c[i];
		}
		int res2 = algo(n - surveyed);
		int res1 = recursiveDP(n - surveyed);
		printf("Case #%d: %d\n", tc + 1, res1);
		printf("ALGO #%d: %d\n\n", tc + 1, res2);
	}
	return 0;
}

//