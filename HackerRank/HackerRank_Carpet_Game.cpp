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

ll int nPr(int n, int r) {

	ll int res = 1;
	FOR(i, n - r + 1, n) {
		res *= i;
	}

	return res;
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
				ll int res = 0;
				ll int rect2x2 = nCrMod(m, 2, MOD) * nCrMod(n, 2, MOD) % MOD;
				res = (res + rect2x2 * nPr(4, k) % MOD) % MOD;
				printf("%lld\n", res % MOD);
			}
			else {
				ll int res = 0;
				// https://math.stackexchange.com/questions/2674022/number-of-rectangles-in-a-grid-of-size-at-least-w-times-h
				// Rectangles of size atelast 2x2
				ll int totalRect = nCrMod(m, 2, MOD) * nCrMod(n, 2, MOD) % MOD;
				res += totalRect * nPr(4, k) % MOD;
				if (k >= 3) {
					FOR(i, 3, min(m, n)) {
						res = (res + (m - i + 1) * (n - i + 1) % MOD * nPr(4, k) % MOD) % MOD;
						i++;
					}
				}
				printf("%lld\n", res % MOD);
			}
		}
	}
	return 0;
}

//