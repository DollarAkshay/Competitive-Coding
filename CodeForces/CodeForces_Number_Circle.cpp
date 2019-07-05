/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//http://codeforces.com/contest/1189/problem/B

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
int v[100000];

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &a[i]);
	}

	SORT(a, n);
	REV(a, n);

	if (a[0] >= a[1] + a[2]) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
		FILL(v, 0);
		REP(i, n) {
			printf("%d ", a[i]);
			v[i] = 1;
			i++;
		}

		FORD(i, n - 1, 0) {
			if (v[i] == 0) {
				printf("%d ", a[i]);
				v[i] = 1;
			}
		}

		printf("\n");
	}
	return 0;
}

//Pretests Passed