/*~~~~~~~~~~~~~~~~~~*
    * *
    *  $DollarAkshay$ *
    * *
    *~~~~~~~~~~~~~~~~~~*/

//https: // www.hackerearth.com / challenges / competitive / june - circuits - 19 / algorithm / climbing - b0536d6a/

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
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int n;
ll int a, b, c;
ll int h1, h2;
ll int fact[100001];
vector<int> seq;

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

ll int solve1() {
	ll int res = 0;
	FOR(i, 0, n) {
		FOR(j, 0, n - i) {
			int k = n - i - j;
			if (i * a + j * b + k * c == h2 - h1) {
				res = (res + fact[n] * inverse_mod(fact[i], MOD) % MOD * inverse_mod(fact[j], MOD) % MOD * inverse_mod(fact[k], MOD) % MOD) % MOD;
			}
		}
	}
	return res;
}

ll int solve2(ll int a, ll int b) {

	ll int res = 0;
	FOR(i, 0, n) {
		if (i * a + (n - i) * b == h2 - h1) {
			res = (res + fact[n] * inverse_mod(fact[i], MOD) % MOD * inverse_mod(fact[n - i], MOD)) % MOD;
		}
	}
	return res;
}

ll int solve() {

	if (a == b && b == c) {
		if (h2 - h1 == a * n) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (a == b) {
		solve2(a, c);
	}
	else if (b == c || c == a) {
		solve2(a, b);
	}
	else {
		return solve1();
	}
}

ll int bruteforce(ll int h, ll int n) {

	if (n == 0) {
		if (h == 0) {
			// REP(i, seq.size()) {
			// 	printf("%d ", seq[i]);
			// }
			// printf("\n");
		}
		return h == 0 ? 1 : 0;
	}

	ll int res = 0;
	seq.push_back(a);
	res = (res + bruteforce(h - a, n - 1)) % MOD;
	seq.pop_back();
	if (b != a) {
		seq.push_back(b);
		res = (res + bruteforce(h - b, n - 1)) % MOD;
		seq.pop_back();
	}
	if (c != a && c != b) {
		seq.push_back(c);
		res = (res + bruteforce(h - c, n - 1)) % MOD;
		seq.pop_back();
	}

	return res % MOD;
}

void preCalc() {
	fact[0] = 1;
	FOR(i, 1, 100000) {
		fact[i] = fact[i - 1] * i % MOD;
	}
}

int main() {

	preCalc();

	scanf("%d %lld %lld %lld %lld %lld", &n, &h1, &h2, &a, &b, &c);

	// ll int bfRes = bruteforce(h2 - h1, n);
	ll int algoRes = solve();

	// printf("BF   : %lld\n", bfRes);
	// printf("ALGO : %lld\n\n", algoRes);
	printf("%lld\n", algoRes);

	return 0;
}

//Solved
