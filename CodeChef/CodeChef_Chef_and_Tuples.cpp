/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/COOK91/problems/CTHREE

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

int max_lvl = 2;
int f_limit[3];

ll int factorizeABC(int n, int lvl) {

	if (lvl == max_lvl) {
		if (n <= f_limit[lvl]) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int limit = sqrt(n);
	ll int count = 0;
	FOR(i, 1, limit) {
		if (n % i == 0 && i <= f_limit[lvl]) {
			count += factorizeABC(n / i, lvl + 1);
			int reci = n / i;
			if (reci > limit && reci <= f_limit[lvl]) {
				count += factorizeABC(n / reci, lvl + 1);
			}
		}
	}
	return count;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d %d %d %d", &n, &f_limit[0], &f_limit[1], &f_limit[2]);

		ll int res = factorizeABC(n, 0);
		printf("%lld\n", res);
	}
	return 0;
}

//Solved