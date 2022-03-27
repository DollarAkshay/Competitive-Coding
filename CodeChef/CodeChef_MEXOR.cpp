/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

// https://www.codechef.com/OCT21A/problems/MEXOR

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
#define S(format, ...) scanf(format, ##__VA_ARGS__)
#define Si(x) S("%d", &x)
#define Sll(x) S("%lld", &x)
#define P(format, ...) printf(format, ##__VA_ARGS__)
#define Pi(x) P("%d\n", x)
#define Pll(x) P("%lld\n", x)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];

int firstPowerMissingInBinary(int n) {

	int res = 1;
	while (res <= n) {
		if ((res & n) == 0) {
			break;
		}
		res = res << 1;
	}
	return res;
}

int highestPowerOf2LteN(int n) {
	if (n < 1) {
		return 0;
	}

	int x = floor(log2(n));
	return 1 << x;
}

int algo(int n) {

	if (n == 0) {
		return 1;
	}

	int mp2 = firstPowerMissingInBinary(n);
	if (mp2 > n) {
		return mp2;
	}
	else {
		return highestPowerOf2LteN(n);
	}
}

int main() {

	int t;
	Si(t);
	REP(tc, t) {
		int n;
		Si(n);
		Pi(algo(n));
	}

	return 0;
}

// Solved