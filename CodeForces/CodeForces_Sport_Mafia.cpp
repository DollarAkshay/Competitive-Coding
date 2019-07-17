/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codeforces.com/contest/1195/problem/B

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

ll int n, k;
ll int binarysearch(ll int low, ll int high) {

	if (low > high) {
		assert(1 == 0);
	}

	ll int mid = (low + high) / 2;
	ll int k_ = (n - mid + 1) * (n - mid) / 2 - mid;

	if (k_ < k) {
		return binarysearch(low, mid - 1);
	}
	else if (k_ > k) {
		return binarysearch(mid + 1, high);
	}
	else {
		return mid;
	}
}

int main() {

	scanf("%lld %lld", &n, &k);
	printf("%lld\n", binarysearch(0, n));

	return 0;
}

//Solved