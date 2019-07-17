/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codeforces.com/contest/1195/problem/D2

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
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 998244353

int a[1000000];
int f[100];

string fun(int a, int b) {

	string res = "";
	while (a > 0 && b > 0) {
		res += to_string(b % 10);
		res += to_string(a % 10);
		b /= 10;
		a /= 10;
	}

	while (a > 0) {
		res += to_string(a % 10);
		a /= 10;
	}

	while (b > 0) {
		res += to_string(b % 10);
		b /= 10;
	}
	REV(res, res.size());
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

int intLen(int a) {

	int res = 0;
	while (a > 0) {
		a /= 10;
		res++;
	}
	return res;
}

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &a[i]);
		f[intLen(a[i])]++;
	}

	ll int res = 0;
	REP(i, n) {
		int k = 1;
		int x = a[i];
		while (x > 0) {
			ll int d = x % 10;
			FOR(j, 1, 10) {
				if (k <= j) {
					res = (res + (d * fastPowMod(10, 2 * k - 1) * f[j] % MOD) + (d * fastPowMod(10, 2 * k - 2) * f[j] % MOD)) % MOD;
				}
				else {
					res = (res + (d * fastPowMod(10, j * 2 + (k - j - 1)) * 2 * f[j] % MOD)) % MOD;
				}
			}
			k += 1;
			x /= 10;
		}
	}

	printf("%lld\n", res);

	return 0;
}

// Solved