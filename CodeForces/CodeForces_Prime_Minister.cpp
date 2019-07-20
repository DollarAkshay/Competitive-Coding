/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codeforces.com/contest/1178/problem/A

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

int a[1000000];

int main() {

	int n;
	int total = 0;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &a[i]);
		total += a[i];
	}

	int x = a[0];
	int sum = x;
	vector<int> indices;
	FOR(i, 1, n - 1) {
		if (2 * a[i] <= x) {
			indices.push_back(i + 1);
			sum += a[i];
		}
	}

	if (sum * 2 > total) {
		printf("%d\n1 ", indices.size() + 1);
		REP(i, indices.size()) {
			printf("%d ", indices[i]);
		}
	}
	else {
		printf("0\n");
	}

	return 0;
}

//Pretests passed