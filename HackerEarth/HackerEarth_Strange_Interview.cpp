/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/college/game_of_codes_5/algorithm/question-4-36/

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

vector<pii> a;
int DP[1000][2];

int solve(int i, int prevScore) {

	if (i == a.size()) {
		return 0;
	}

	if (a[i].second > prevScore && DP[i][1] != -1) {
		return DP[i][1];
	}

	if (DP[i][0] != -1) {
		return DP[i][0];
	}

	if (a[i].second > prevScore) {
		DP[i][1] = max(1 + solve(i + 1, a[i].second), solve(i + 1, prevScore));
		return DP[i][1];
	}
	else {
		DP[i][0] = solve(i + 1, prevScore);
		return DP[i][0];
	}
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		a.clear();
		MSX(DP, -1);
		int n;
		scanf("%d", &n);
		REP(i, n) {
			int x;
			scanf("%d", &x);
			a.pb(mp(-1, x));
		}

		REP(i, n) {
			int x;
			scanf("%d", &x);
			a[i].first = x;
		}

		SORT(a, a.size());
		printf("%d\n", solve(0, -1));
	}
	return 0;
}

//