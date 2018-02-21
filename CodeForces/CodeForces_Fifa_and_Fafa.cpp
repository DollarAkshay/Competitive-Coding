/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//http://codeforces.com/contest/935/problem/C

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

int a[1000000];

int main() {

	int R;
	int x1, y1;
	int x2, y2;
	scanf("%d %d %d %d %d", &R, &x1, &y1, &x2, &y2);

	double dist = sqrtl(((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2)));

	if (x1 == x2 && y1 == y2) {
		double r = (double)R / 2;
		double xap = x1 + r;
		double yap = y1;
		printf("%.12lf %.12lf %.12lf\n", xap, yap, r);
	}
	else if (dist > R) {
		printf("%d %d %d\n", x1, y1, R);
	}
	else {
		double xap = x2 - (dist + R) * (x2 - x1) / (2 * dist);
		double yap = y2 - (dist + R) * (y2 - y1) / (2 * dist);
		double r = (R + dist) / 2;
		printf("%.12lf %.12lf %.12lf\n", xap, yap, r);
	}

	return 0;
}

//Solved after Contest