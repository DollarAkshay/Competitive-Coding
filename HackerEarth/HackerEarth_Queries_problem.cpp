/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/an-interesting-partition-problem-june-circuits-18f83691/

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
#define ull unsigned long long
#define pii pair<int, int>
#define MOD 1000000000000000000LL

ll int a[100000];

int main() {

	int n, m;
	scanf("%d %d", &n, &m);
	REP(i, n) {
		scanf("%lld", &a[i]);
	}

	int lProd = 1, rProd = 1;
	ll int li = 0, ri = n - 1;

	while (li < ri) {
		if (abs(a[li] * lProd - rProd) < abs(lProd - a[ri] * rProd)) {
			lProd = (ull int)lProd * a[li] % MOD;
			li++;
		}
		else {
			rProd = (ull int)rProd * a[ri] % MOD;
			ri--;
		}
	}

	int x = li;
	printf("X = %d\n", x);

	REP(q, m) {
		ll int t, pos, val;
		scanf("%lld", &t);
		if (t == 1) {
			scanf("%lld %lld", &pos, &val);

			if (pos <= x) {
				lProd = (ull int)lProd * val % MOD;
			}
		}
		else {
			printf("%d\n", x);
		}
	}

	return 0;
}

//