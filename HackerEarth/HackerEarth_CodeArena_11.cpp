/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/d00671a/

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

int n;
int score[10000];
int DP[10000];

ll int solve(int judge) {

	if (DP[judge] > 0) {
		return DP[judge];
	}

	if (judge >= n) {
		DP[judge] = 0;
	}
	else {
		DP[judge] = max(solve(judge + 1), solve(judge + 2) + score[judge]);
	}

	return DP[judge];
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		MSX(DP, 0);
		scanf("%d", &n);
		int oddSum = 0, evenSum = 0;
		REP(i, n) {
			scanf("%d", &score[i]);
		}

		printf("Case %d: %d\n", tc + 1, solve(0));
	}
	return 0;
}

//Solved