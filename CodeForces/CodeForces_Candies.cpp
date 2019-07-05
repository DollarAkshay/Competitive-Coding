/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//http://codeforces.com/contest/1189/problem/C

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

int a[100000];
int s[100001];

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &a[i]);
		s[i + 1] = s[i] + a[i];
	}

	int q;
	scanf("%d", &q);
	REP(i, q) {
		int l, r;
		scanf("%d %d", &l, &r);
		int sum = s[r] - s[l - 1];
		printf("%d\n", sum / 10);
	}

	return 0;
}

//Pre-tests Passed