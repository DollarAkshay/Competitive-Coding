/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/FEB18/problems/BROCLK

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
#define PI 3.141592653589793238463

ll int gcd(ll int a, ll int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

ll int invert_mod(ll int a, ll int p) {
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

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		ll int l, d, t;
		scanf("%lld %lld %lld", &l, &d, &t);
		double theta_deg = (double)PI / 2 - asin((double)d / l);
		// printf("T+ = %lf\n", theta_deg);
		theta_deg = fmodl((double)theta_deg * t, (double)PI * 2);
		// printf("T%% = %lf\n", theta_deg);

		double y = (double)sin((double)PI / 2 - theta_deg) * l;
		y = round(y * 10E2) / 10E2;
		// printf("Y = %lf\n", y);
		int pow_10 = 0;
		while (floor(y) != y && pow_10 < 8) {
			y *= 10;
			pow_10++;
		}

		ll int p = y, q = (int)round(pow((double)10, pow_10));
		ll int fact = gcd(abs(p), q);
		p /= fact;
		q /= fact;

		ll int res = (((p + MOD) % MOD) * (invert_mod(q, MOD) % MOD)) % MOD;
		printf("%lld\n", res);
	}

	return 0;
}

//