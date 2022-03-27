/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

// https://www.codechef.com/OCT21A/problems/DIGITREM

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
#define S(format, ...) scanf(format, ##__VA_ARGS__)
#define Si(x) S("%d", &x)
#define Sll(x) S("%lld", &x)
#define P(format, ...) printf(format, ##__VA_ARGS__)
#define Pi(x) P("%d\n", x)
#define Pll(x) P("%lld\n", x)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];

bool hasDigit(ll n, int d) {
	while (n) {
		if (n % 10 == d)
			return true;
		n /= 10;
	}
	return false;
}

ll bruteforce(ll n, int d) {
	FOR(i, 0, 1E9) {
		if (hasDigit(n + i, d) == false) {
			return i;
		}
	}
	return -1;
}

int getDigit(int n, int k) {
	int div = pow(10, k);
	return n / div % 10;
}

ll algo(ll n, int d) {

	ll res = 0;
	int len = floor(log10(n)) + 1;
	FOR(i, 0, len - 1) {
		int digit = getDigit(n, i);
		if (digit == d) {
			int pow10 = pow(10, i);
			res += pow(10, i) - n % pow10;
			n += pow(10, i) - n % pow10;
			// P("i = %d | res = %d | n = %d\n", i, res, n);
		}
	}

	FORD(i, len - 1, 0) {
		int digit = getDigit(n, i);
		if (digit == d) {
			int pow10 = pow(10, i);
			res += pow(10, i) - n % pow10;
			n += pow(10, i) - n % pow10;
		}
	}

	return res;
}

int main() {

	// FOR(n, 1, 1000) {
	// 	FOR(d, 0, 9) {
	// 		int bfRes = bruteforce(n, d);
	// 		int res = algo(n, d);
	// 		if (res != bfRes) {
	// 			P("N/d = %5d/%5d | Algo = %6d | BF = %6d\n", n, d, res, bfRes);
	// 		}
	// 	}
	// }

	int t;
	Si(t);
	REP(tc, t) {
		int n, d;
		Si(n);
		Si(d);
		ll res = algo(n, d);
		Pll(res);
	}
	return 0;
}

// Solved