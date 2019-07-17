/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codeforces.com/contest/1195/problem/C

#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
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
#include <unordered_set>
#include <vector>

using namespace std;
using namespace std::chrono;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int n;
int h[2][1000000];
ll int dp[3][1000000];

ll int recursion(int i, int prevRow) {

	if (dp[prevRow + 1][i] > 0) {
		return dp[prevRow + 1][i];
	}

	if (i == n) {
		return 0;
	}

	ll int res = 0;
	if (prevRow != 0) {
		res = max(res, h[0][i] + recursion(i + 1, 0));
	}
	if (prevRow != 1) {
		res = max(res, h[1][i] + recursion(i + 1, 1));
	}
	res = max(res, recursion(i + 1, -1));

	dp[prevRow + 1][i] = res;
	return dp[prevRow + 1][i];
}

int main() {

	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &h[0][i]);
	}
	REP(i, n) {
		scanf("%d", &h[1][i]);
	}

	ll int res = recursion(0, -1);
	printf("%lld\n", res);

	return 0;
}

//Pretests passed