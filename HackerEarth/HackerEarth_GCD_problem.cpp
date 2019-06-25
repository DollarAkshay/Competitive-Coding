/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/calculate-gcd-june-circuit-e5e41856/

// #pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

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
#define FORS(i, a, b, s) for (int i = a; i <= b; i += s)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007
#define MAX 1000000

int a[MAX];

int p[MAX + 1];
int m[MAX + 1];
ll int mi[MAX + 1];

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

int primeSeive() {
	FILL(p, 1);
	p[0] = p[1] = 0;

	int limit = sqrt(MAX);
	FOR(i, 2, limit) {
		if (p[i] == 1) {
			FORS(j, i * i, MAX, i) {
				p[j] = 0;
			}
		}
	}
}

int mobiusSeive() {

	FILL(m, 1);
	m[0] = 0;
	m[1] = 1;

	int limit = sqrt(MAX);

	// Calculate +1/-1 Mobius values
	FOR(i, 2, MAX) {
		if (p[i] == 1) {
			FORS(j, i, MAX, i) {
				m[j] *= -1;
			}
		}
	}

	// Set all prime squares to 0
	FOR(i, 2, limit) {
		if (p[i] == 1) {
			FORS(j, i * i, MAX, i * i) {
				m[j] = 0;
			}
		}
	}
}

int mobiusInvSeive() {
	FILL(mi, 0);
	FOR(i, 1, MAX) {
		FORS(j, i, MAX, i) {
			mi[j] = (mi[j] + fastPowMod(i, 4) * m[j / i] % MOD) % MOD;
		}
	}
}

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

ll int gcd(ll int a, ll int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
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
		REP(i, min(5, (int)havingGCD[g].size())) {
			printf("%2d %2d %2d %2d\n", havingGCD[g][i][0], havingGCD[g][i][1], havingGCD[g][i][2], havingGCD[g][i][3]);
		}
		if (havingGCD[g].size() > 5) {
			printf("...\n");
		}
	}
	printf("\n");

	return res;
}

ll int algo(int n) {
	ll int res = 0;

	FOR(i, 1, n / 4) {
		res = (res + mi[i] * ncrMod(n / i, 4) % MOD) % MOD;
	}

	return res;
}

int main() {

	primeSeive();
	mobiusSeive();
	mobiusInvSeive();

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d", &n);

		// ll int bfRes = bruteforce(n);
		// printf("\nBF   = %lld\n", bfRes);

		ll int res = algo(n);
		assert(res > 0);
		printf("%lld\n", res);
	}
	return 0;
}

//