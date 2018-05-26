/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/APRIL18A/problems/CUTPLANT

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
#define MAX 10

int a[100000];
int b[100000];

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {

		scanf("%lld %lld %lld", &n, &s, &y);

		// Make problem simpler by eliminating the direction.
		// If d[i] == 0 Mirror Position. Multiply postion by -1

		REP(i, n) {
			scanf("%lf", &v[i]);
		}

		REP(i, n) {
			scanf("%lf", &d[i]);
		}

		REP(i, n) {
			scanf("%lf", &p[i]);
			if (d[i] == 0) {
				p[i] *= -1;
			}
		}

		REP(i, n) {
			scanf("%lf", &c[i]);
		}

		double t = 0;
		REP(i, n) {
			double crossTime = calcCrossTime(t, i);
			t += crossTime;
		}
		printf("%lf\n", t);
	}
	return 0;
}

//Solved