/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-easy-18/algorithm/sallu-bhai-and-ias-8838ac8d/

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
#include <unordered_set>
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
#define MOD 2520

ll int DP[13][2520][512];
vector<int> digits;
int powers[10];

void getDigits(ll int n) {
	digits.clear();
	while (n > 0) {
		digits.push_back(n % 10);
		n /= 10;
	}
}

bool checkSpecial(int sum, int digitmask) {

	// A number with only zeroes
	if (sum == 0 && digitmask == 0) {
		return false;
	}

	FOR(i, 1, 9) {
		if (digitmask & (1 << (i - 1))) {
			if (sum % i != 0) {
				return false;
			}
		}
	}

	return true;
}

ll int calcSpecial(int index, int sum, bool tight, int digitmask) {

	if (index < 0) {
		return checkSpecial(sum, digitmask);
	}

	// If we already have the value return it
	// tight has to be false since if tight is true that means the next digits will be restricted
	// This DP is only to store all posibilities of 0-9 digit insertions
	if (tight == false && DP[index][sum][digitmask] != -1) {
		return DP[index][sum][digitmask];
	}

	ll int res = 0;
	if (tight) {
		FOR(i, 0, digits[index]) {
			int new_tight = i == digits[index] ? 1 : 0;
			int new_sum = (sum + powers[i]) % MOD;
			int new_digitmask = i == 0 ? digitmask : digitmask | (1 << (i - 1));
			res += calcSpecial(index - 1, new_sum, new_tight, new_digitmask);
		}
	}
	else {
		FOR(i, 0, 9) {
			int new_sum = (sum + powers[i]) % MOD;
			int new_digitmask = i == 0 ? digitmask : digitmask | (1 << (i - 1));
			res += calcSpecial(index - 1, new_sum, 0, new_digitmask);
		}
	}

	if (tight == false) {
		DP[index][sum][digitmask] = res;
	}

	return res;
}

void preCalc() {

	powers[0] = 0;
	FOR(i, 1, 9) {
		powers[i] = (int)round(pow(i, i));
	}
}

int main() {

	MSX(DP, -1);
	preCalc();

	int n;
	scanf("%d", &n);
	REP(i, n) {
		ll int l, r;
		scanf("%lld %lld", &l, &r);

		getDigits(l - 1);
		ll int res_l = calcSpecial(digits.size() - 1, 0, 1, 0);
		// printf("RES_L = %lld\n", res_l);

		getDigits(r);
		ll int res_r = calcSpecial(digits.size() - 1, 0, 1, 0);
		// printf("RES_R = %lld\n", res_r);

		printf("%lld\n", res_r - res_l);
	}

	return 0;
}

//Solved