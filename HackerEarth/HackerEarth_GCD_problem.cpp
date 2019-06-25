/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/calculate-gcd-june-circuit-e5e41856/

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
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];

ll int inverse_mod(ll int a, ll int p) {
	ll int ne = 1, old = 0, q = p, r, h;
	ll int pos = 0;
	while (a > 0) {
		r = q % a;
		q = q / a;
		h = q * ne + old;
		old = ne;
		ne = h;
		q = a;
		a = r;
		pos = !pos;
	}
	return pos ? old : (p - old);
}

ll int ncrMod(int n, int r) {

	ll int res = 1;
	r = r < n - r ? r : n - r;
	FOR(i, 1, r) {
		res = ((res * (n - i + 1) % MOD) * inverse_mod(i, MOD)) % MOD;
	}
	return res;
}

ll int fastPowMod(ll int b, ll int e) {

	if (e == 0) {
		return 1;
	}
	else if (e % 2 == 1) {
		return fastPowMod(b, e - 1) * b % MOD;
	}
	else {
		ll int res = fastPowMod(b, e / 2);
		return (res * res) % MOD;
	}
}

ll int gcd(ll int a, ll int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

ll int lcm(ll int a, ll int b) {
	return a * b / gcd(a, b);
}

ll int bruteforce(int n) {

	ll int res = 0;
	vector<vector<int>> havingGCD[1000];

	FOR(i, 1, n) {
		FOR(j, i + 1, n) {
			FOR(k, j + 1, n) {
				FOR(l, k + 1, n) {
					ll int f = gcd(i, gcd(j, gcd(k, l)));
					havingGCD[f].push_back({i, j, k, l});
					res += f * f * f * f;
				}
			}
		}
	}

	// Grpuped by GCD Value
	FOR(g, 1, n / 4) {
		printf("GCD = %d\n", g);
		REP(i, min(35, (int)havingGCD[g].size())) {
			printf("%2d %2d %2d %2d\n", havingGCD[g][i][0], havingGCD[g][i][1], havingGCD[g][i][2], havingGCD[g][i][3]);
		}
		if (havingGCD[g].size() > 35) {
			printf("...\n");
		}
	}
	printf("\n");

	return res;
}

ll int algo(int n) {
	ll int res = 0;

	FOR(i, 1, n / 4) {
		ll int x = 2 * i;
		ll int k1 = (n - x) / i;
		ll int k2 = k1 - 1;
		ll int k3 = k1 - 2;

		ll int k1Count = ((k1 * k1 * k1 - k1) / 6) % MOD;
		ll int k2Count = ((k2 * k2 * k2 - k2) / 6) % MOD;
		ll int k3Count = ((k3 * k3 * k3 - k3) / 6) % MOD;

		ll int k1Res = fastPowMod(i, 4) * k1Count % MOD;
		ll int k2Res = fastPowMod(i, 4) * k2Count % MOD;
		ll int k3Res = fastPowMod(i, 4) * k3Count % MOD;

		res = (res + k1Res + k2Res + k3Res) % MOD;

		printf(" GCD = %2d | %7lld | %7lld + %7lld + %7lld = %7lld\n", i, ncrMod(n / i, 4), k1Count, k2Count, k3Count, k1Count + k2Count + k3Count);
	}

	return res;
}

int main() {

	int t = 1;
	// scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d", &n);

		ll int bfRes = bruteforce(n);
		ll int algoRes = algo(n);
		printf("\nBF   = %lld\n", bfRes);
		printf("ALGO = %lld\n", algoRes);
		printf("Diff = %lld\n", bfRes - algoRes);
	}
	return 0;
}

//