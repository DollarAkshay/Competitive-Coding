/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/MARCH18A/problems/CHEFKNN

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
#define MOD 163577857
#define MAX 5000

ll int CDP[MAX][MAX];
ll int DP[MAX][MAX];

int invert_mod(int a, int p) {
	ll int ne = 1, old = 0, q = p, r, h;
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

void preCompute() {
	REP(i, MAX) {
		DP[i][0] = 1;
		DP[0][i] = 1;
		CDP[0][i] = 1;
		CDP[i][0] = i == 0 ? 1 : (CDP[i - 1][0] + i + 1) % MOD;
	}

	FOR(j, 1, MAX - 1) {
		FOR(i, 1, MAX - 1) {
			DP[i][j] = ((CDP[i][j - 1] - i * DP[i][j - 1]) % MOD + MOD) % MOD;
			CDP[i][j] = (CDP[i - 1][j] + DP[i][j] * (i + 1)) % MOD;
		}
	}
}

int main() {

	preCompute();

	FOR(i, 1, 10) {
		FOR(j, 1, 10) {
			printf("%9lld ", nCrMod(i + j - 1, i, MOD));
		}
		printf("\n");
	}

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, k;
		scanf("%d %d", &n, &k);
		printf("%lld\n", CDP[n - 1][k - 1]);
	}

	return 0;
}

//