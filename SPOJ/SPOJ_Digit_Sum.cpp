/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//http://www.spoj.com/problems/PR003004/

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
ll int DP[16][9 * 16];

void getDigits(ll int n) {
	digits.clear();
	while (n > 0) {
		digits.pb(n % 10);
		n /= 10;
	}
}

ll int findSum(int idx, int sum, bool tight) {

	if (idx < 0) {
		return sum;
	}

	// If we already have the value return it
	// tight has to be false since if tight is true that means the next digits will be restricted
	// This DP is only to store all posibilities of 0-9 digit insertions
	if (DP[idx][sum] != -1 && tight == false) {
		return DP[idx][sum];
	}

	ll int res = 0;
	if (tight) {
		// If it is tight we can only insert upto what digit is there at the idx position
		// If we dont restrict it, the resulting number will be greater than what we are searching for
		FOR(i, 0, digits[idx]) {
			bool new_tight = i == digits[idx] ? true : false;
			int new_sum = sum + i;
			res += findSum(idx - 1, new_sum, new_tight);
		}
	}
	else {
		// Else we can insert any digit as it will not excede the number
		FOR(i, 0, 9) {
			int new_sum = sum + i;
			res += findSum(idx - 1, new_sum, false);
		}
	}

	// As mentioned earlier we only store this if tight is false
	// As it stores only for 0-9 digit insertions not 0-5 or 0-1 or 0-digit[idx] in general
	if (tight == false) {
		DP[idx][sum] = res;
	}

	return res;
}

int main() {

	MSX(DP, -1);

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		ll int l, r;
		scanf("%lld %lld", &l, &r);
		getDigits(max((ll int)0, l - 1));
		ll int res_l = findSum(digits.size() - 1, 0, 1);

		getDigits(r);
		ll int res_r = findSum(digits.size() - 1, 0, 1);

		printf("%lld\n", res_r - res_l);
	}

	return 0;
}

//Solved