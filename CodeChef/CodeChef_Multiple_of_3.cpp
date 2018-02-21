/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/problems/MULTHREE

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
#define MOD 10

int a[1000000];

ll int fastPowMod(ll int b, ll int e) {

	if (e == 0) {
		return 1;
	}
	else if (e % 2 == 1) {
		return fastPowMod(b, e - 1) * b;
	}
	else {
		ll int res = fastPowMod(b, e / 2);
		return (res * res) % MOD;
	}
}

bool algo1(ll int k, ll int d0, ll int d1) {
	ll int intitial_sum = d0 + d1;
	int di, seq_start = -1;
	REP(i, k - 2) {
		di = fastPowMod(2, i) * (d0 + d1) % MOD;
		if (di == 2 || di == 0) {
			seq_start = i + 2;
			break;
		}
		intitial_sum += di;
	}

	if (seq_start == -1 || di == 0) {
		return intitial_sum % 3 == 0;
	}
	else {
		ll int rem_digits = k - seq_start;
		ll int seq_sum = 0;
		seq_sum += (2 + 4 + 8 + 6) * (rem_digits / 4);
		if (rem_digits % 4 == 1) {
			seq_sum += 2;
		}
		else if (rem_digits % 4 == 2) {
			seq_sum += 2 + 4;
		}
		else if (rem_digits % 4 == 3) {
			seq_sum += 2 + 4 + 8;
		}
		return (intitial_sum + seq_sum) % 3 == 0;
	}
}

bool algo2(ll int k, ll int d0, ll int d1) {

	int s = d0 + d1;

	if (k == 2) {
		return s % 3 == 0;
	}
	else if (k == 3) {
		return (s + s % 10) % 3 == 0;
	}
	else {
		ll int rem_k = (k - 3) / 4;
		ll int seq_sum = (2 * s % 10) + (4 * s % 10) + (8 * s % 10) + (6 * s % 10);
		ll int rem_sum = 0;

		if ((k - 3) % 4 == 1) {
			rem_sum = (2 * s % 10);
		}
		else if ((k - 3) % 4 == 2) {
			rem_sum = (2 * s % 10) + (4 * s % 10);
		}
		else if ((k - 3) % 4 == 3) {
			rem_sum = (2 * s % 10) + (4 * s % 10) + (8 * s % 10);
		}

		return (s + s % 10 + rem_k * seq_sum + rem_sum) % 3 == 0;
	}
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		ll int k, d0, d1;
		scanf("%lld %lld %lld", &k, &d0, &d1);

		//puts(algo1(k, d0, d1) ? "YES" : "NO");
		puts(algo2(k, d0, d1) ? "YES" : "NO");
	}
	return 0;
}

//Solved