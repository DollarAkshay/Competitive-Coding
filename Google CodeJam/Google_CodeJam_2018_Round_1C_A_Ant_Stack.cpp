/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://codejam.withgoogle.com/2018/challenges/0000000000007765/dashboard/000000000003e0a8

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define REP(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define MOD 1000000007

const int FACTOR = 6;

int n;
ll int w[100000];
ll int cw[100000];

int recursiveDP(int i, int ants, ll int totalWeight) {

	if (i == n) {
		return ants;
	}

	if (DP[i][totalWeight] != 0) {
		return DP[i][totalWeight];
	}

	if (FACTOR * w[i] >= totalWeight) {
		DP[i][totalWeight] = max(recursiveDP(i + 1, ants, totalWeight),
								 recursiveDP(i + 1, ants + 1, totalWeight + w[i]));
	}
	else {
		DP[i][totalWeight] = recursiveDP(i + 1, ants, totalWeight);
	}

	return DP[i][totalWeight];
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d", &n);
		REP(i, n) {
			scanf("%lld", &w[i]);
			cw[i + 1] = cw[i] + w[i];
		}

		int res = 0;
		REP(i, n){
			if(cw[i] > FACTOR[])
		}
		printf("Case #%d: %d\n", tc + 1, res);
	}
	return 0;
}

//