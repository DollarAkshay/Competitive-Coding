/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//http://www.spoj.com/problems/RAONE/

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

vector<int> digits;
int DP[9][2 * 9 * 4 + 1];

void getDigits(int n) {
	digits.clear();
	while (n > 0) {
		digits.pb(n % 10);
		n /= 10;
	}
}

int findRaNumbers(int idx, int diff, bool tight) {

	if (idx < 0) {
		return diff == 1;
	}

	if (DP[idx][diff + 9 * 4] != -1 && tight == false) {
		return DP[idx][diff + 9 * 4];
	}

	int res = 0;
	if (tight) {
		FOR(i, 0, digits[idx]) {
			bool new_tight = i == digits[idx] ? true : false;
			int new_diff = (idx + 1) % 2 == 0 ? diff + i : diff - i;
			res += findRaNumbers(idx - 1, new_diff, new_tight);
		}
	}
	else {
		FOR(i, 0, 9) {
			int new_diff = (idx + 1) % 2 == 0 ? diff + i : diff - i;
			res += findRaNumbers(idx - 1, new_diff, false);
		}
	}

	if (tight == false) {
		DP[idx][diff + 9 * 4] = res;
	}

	return res;
}

int main() {

	MSX(DP, -1);

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		int l, r;
		scanf("%d %d", &l, &r);

		getDigits(max(0, l - 1));
		int res_l = findRaNumbers(digits.size() - 1, 0, true);

		getDigits(r);
		int res_r = findRaNumbers(digits.size() - 1, 0, true);

		printf("%d\n", res_r - res_l);
	}
	return 0;
}

//Solved