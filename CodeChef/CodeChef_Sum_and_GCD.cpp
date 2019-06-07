/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JUNE19A/problems/SUMAGCD

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
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];

bool isPrime(ll int n) {

	int limit = sqrt(n);
	FOR(i, 2, limit) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

ll int gcd(ll int a, ll int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

ll int bruteforce(int n) {

	ll int bestGCD = -1;
	int bestSet = -1;

	vector<int> b, c;

	int limit = 1 << n;
	REP(i, limit) {
		int x = i;
		b.clear();
		c.clear();
		REP(j, n) {
			if (x % 2 == 0) {
				b.push_back(a[j]);
			}
			else {
				c.push_back(a[j]);
			}
			x /= 2;
		}

		if (b.size() == 0 || c.size() == 0) {
			continue;
		}

		ll int gcdB = b[0];
		ll int gcdC = c[0];
		REP(i, b.size()) {
			gcdB = gcd(gcdB, b[i]);
		}

		REP(i, c.size()) {
			gcdC = gcd(gcdC, c[i]);
		}

		if (gcdB + gcdC > bestGCD) {
			bestGCD = gcdB + gcdC;
			bestSet = i;
		}
	}

	// b.clear();
	// c.clear();
	// REP(j, n) {
	// 	if (bestSet % 2 == 0) {
	// 		b.push_back(a[j]);
	// 	}
	// 	else {
	// 		c.push_back(a[j]);
	// 	}
	// 	bestSet /= 2;
	// }
	// REP(i, b.size()) {
	// 	printf("%d ", b[i]);
	// }
	// printf("\n");
	// REP(i, c.size()) {
	// 	printf("%d ", c[i]);
	// }
	// printf("\n\n");

	return bestGCD;
}

ll int solve(int n) {
	SORT(a, n);
	vector<int> unique_a;
	FORD(i, n - 1, 0) {
		if (i == 0 || a[i] != a[i - 1]) {
			unique_a.push_back(a[i]);
		}
	}
	if (unique_a.size() <= 2) {
		return (ll int)unique_a[0] + unique_a.back();
	}
	else {
		ll int bestVal = -1;
		REP(i, unique_a.size()) {
			ll int gcdVal = -1;
			REP(j, unique_a.size()) {
				if (i != j) {
					gcdVal = gcdVal == -1 ? unique_a[j] : gcd(gcdVal, unique_a[j]);
				}
			}

			if (bestVal < gcdVal + unique_a[i]) {
				bestVal = gcdVal + unique_a[i];
			}
		}
		return bestVal;
	}
}

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {

		scanf("%d", &n);
		REP(i, n) {
			scanf("%d", &a[i]);
		}

		printf("%lld\n", solve(n));
	}
	return 0;
}

// Solved