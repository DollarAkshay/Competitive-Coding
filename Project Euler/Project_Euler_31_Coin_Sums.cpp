/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://projecteuler.net/problem=31

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

int coin[] = {1, 2, 5, 10, 20, 50, 100, 200};
ll int DP[1000][8];

ll int waysOfSum(int sum, int prevCoinIdx) {

	if (sum < 0) {
		return 0;
	}
	else if (DP[sum][prevCoinIdx] != 0) {
		return DP[sum][prevCoinIdx];
	}
	else {
		ll int ways = 0;
		REP(i, 8) {
			if (i <= prevCoinIdx) {
				ways += waysOfSum(sum - coin[i], i);
			}
		}
		DP[sum][prevCoinIdx] = ways;
		return DP[sum][prevCoinIdx];
	}
}

int main() {

	REP(i, 8) {
		DP[0][i] = 1;
	}

	printf("%lld\n", waysOfSum(200, 7));

	return 0;
}
//