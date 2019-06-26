/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/june-circuits-function-value-bdd25438/

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
#define FILL(a, x) fill_n(a, sizeof(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

ll int f[1000001];

ll int fastPowMod(ll int b, ll int e, ll int m) {

	if (e == 0) {
		return 1;
	}
	else if (e % 2 == 1) {
		return fastPowMod(b, e - 1, m) * b % m;
	}
	else {
		ll int res = fastPowMod(b, e / 2, m);
		return (res * res) % m;
	}
}

// C function for extended Euclidean Algorithm
ll int gcdExtended(ll int a, ll int b, ll int *x, ll int *y) {
	// Base Case
	if (a == 0) {
		*x = 0, *y = 1;
		return b;
	}

	ll int x1, y1; // To store results of recursive call
	ll int gcd = gcdExtended(b % a, a, &x1, &y1);

	// Update x and y using results of recursive
	// call
	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

// Function to find modulo inverse of a
ll int modInverse(ll int a, ll int m) {
	ll int x, y;
	ll int g = gcdExtended(a, m, &x, &y);
	if (g != 1) {
		assert(1 == 0);
	}
	else {
		// m is added to handle negative x
		int res = (x % m + m) % m;
		return res;
	}
}

ll int bruteforce(int l, int r, int m) {
	ll int res = 0;
	FOR(i, l, r) {
		res = (res + f[i]) % m;
	}
	return res;
}

ll int evenSum(ll int l, ll int r, int m) {
	ll int seqL = (l + 1) / 2;
	ll int seqR = r / 2;

	// printf("Even L/R  : %lld/%lld\n", seqL, seqR);
	ll int res = (4 + 3 * fastPowMod(-1, seqL, m) + 3 * fastPowMod(-1, seqR, m) - fastPowMod(3, seqL, m) + fastPowMod(3, seqR + 1, m) - 4 * seqL % m + 4 * seqR % m) * modInverse(4, m) % m;
	return (res + m) % m;
}

ll int oddSum(ll int l, ll int r, int m) {

	ll int seqL = l / 2;
	ll int seqR = (r - 1) / 2;

	// printf("Odd L/R  : %lld/%lld\n", seqL, seqR);
	ll int res = (fastPowMod(3, seqR + 1, m) - fastPowMod(3, seqL, m)) * modInverse(2, m) % m;
	return (res + m) % m;
}

ll int preCalc() {

	f[1] = f[2] = 1;
	FOR(i, 3, 1000000) {
		if (i % 2 == 0) {
			f[i] == (2 * f[i - 1] - f[i - 2] + 2) % MOD;
		}
		else {
			f[i] = (3 * f[i - 2]) % MOD;
		}
	}
}

int main() {

	preCalc();

	int t, m;
	scanf("%d %d", &t, &m);
	REP(tc, t) {
		ll int l, r;
		scanf("%lld %lld", &l, &r);

		// ll int bfRes = bruteforce(l, r, m);
		// printf("BF   : %lld\n", bfRes);

		ll int algoRes = (oddSum(l, r, m) + evenSum(l, r, m)) % m;
		printf("%lld\n", algoRes);
	}
	return 0;
}

//Partially Solved