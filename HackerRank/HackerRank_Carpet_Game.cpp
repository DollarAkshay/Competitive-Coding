/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerrank.com/contests/101hack53/challenges/carpet-game

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

unsigned long long invert_mod(unsigned long long a, unsigned long long p) {
	unsigned long long ne = 1, old = 0, q = p, r, h;
	int pos = 0;
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

ll int nCrMod(int n, int r, int mod) {
	if (n == r)
		return 1;
	ll int x = 1, i = 1;
	r = n - r > r ? n - r : r;
	while (n - r) {
		x = ((x * n--) % mod * invert_mod(i++, mod)) % mod;
		if (x == 0)
			return 0;
	}
	return x;
}

ll int fact(int n) {
	ll int res = 1;
	FOR(i, 1, n) {
		res *= i;
	}
	return res;
}

ll int rectCount(ll int m, ll int n, ll int w, ll int h) {
	return (m - w + 1) * (n - h + 1) % MOD;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		ll int n, m, k;
		scanf("%lld %lld %lld", &n, &m, &k);
		k++;
		if (k > 4 || m * n < k) {
			printf("0\n");
		}
		else {
			if (k == 2) {
				ll int hori = nCrMod(m, 2, MOD) * n % MOD;
				ll int vert = nCrMod(n, 2, MOD) * m % MOD;
				ll int diag = 0;
				FOR(i, 2, min(m, n)) {
					diag = (diag + 2 * rectCount(m, n, i, i) % MOD) % MOD;
				}
				printf("%lld\n", fact(2) * (hori + vert + diag) % MOD);
			}
			else if (k == 3) {
				ll int res = 0;
				FOR(i, 2, min(m, n)) {
					res = (res + 4 * rectCount(m, n, i, i) % MOD) % MOD;
				}

				// # - #    - # -
				// - # -    # - #
				FOR(i, 1, min((m - 1) / 2, n - 1)) {
					res = (res + 2 * rectCount(m, n, 2 * i + 1, i + 1) % MOD) % MOD;
				}

				//Transpose of Previous
				FOR(i, 1, min(m - 1, (n - 1) / 2)) {
					res = (res + 2 * rectCount(m, n, i + 1, 2 * i + 1) % MOD) % MOD;
				}

				printf("%lld\n", fact(3) * res % MOD);
			}
			else {
				ll int res = 0;
				FOR(i, 2, min(m, n)) {
					res = (res + rectCount(m, n, i, i) % MOD) % MOD;
				}

				// - # -
				// # - #
				// - # -
				FOR(i, 1, min((m - 1) / 2, (n - 1) / 2)) {
					res = (res + rectCount(m, n, 2 * i + 1, 2 * i + 1) % MOD) % MOD;
				}

				printf("%lld\n", fact(4) * res % MOD);
			}
		}
	}
	return 0;
}

//Solved after contest