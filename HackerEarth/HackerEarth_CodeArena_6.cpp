/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/257f938/

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

int a[1000][1000];
ll int rowSum[1000][1001];

int main() {

	int r, c;
	scanf("%d %d", &r, &c);
	REP(i, r) {
		REP(j, c) {
			scanf("%d", &a[i][j]);
			rowSum[i][j + 1] = a[i][j] + rowSum[i][j];
		}
	}

	int q;
	scanf("%d", &q);
	REP(qr, q) {
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
		x1--;
		y1--;
		x2--;
		y2--;
		ll int res = 0;
		FOR(i, y1, y2) {
			res += rowSum[i][x2 + 1] - rowSum[i][x1];
		}
		printf("%lld\n", res);
	}
	return 0;
}

//Solved