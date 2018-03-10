/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/e3caab6/

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

ll int avg[100];
ll int a[100];
ll int csum[101];

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &avg[i]);
	}

	FOR(i, 1, n) {
		a[i - 1] = i * avg[i - 1] - csum[i - 1];
		csum[i] = csum[i - 1] + a[i - 1];
	}

	REP(i, n) {
		printf("%d ", a[i]);
	}
	return 0;
}

//