/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

// https://www.codechef.com/FEB18/problems/POINPOLY

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

struct point {
	ll int x, y;

  public:
	point() {
		x = 0;
		y = 0;
	}
	point(ll int px, ll int py) {
		x = px;
		y = py;
	}
	point operator+(const point &rhs) const {
		return point(x + rhs.x, y + rhs.y);
	}
	point operator/(const int k) const {
		return point(x / k, y / k);
	}
};

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d", &n);
		vector<point> poly;
		REP(i, n) {
			ll int x, y;
			scanf("%lld %lld", &x, &y);
			poly.pb(point(x, y));
		}
		int limit = n / 10;
		vector<point> res;
		REP(k, limit) {
			FOR(i, 0, 9) {
				FOR(j, i + 2, 9) {
					if (i == 0 && j == 9) {
						continue;
					}
					point p1 = poly[k * 10 + i];
					point p2 = poly[k * 10 + j];
					point mid = (p1 + p2);
					if (mid.x % 2 == 0 && mid.y % 2 == 0) {
						res.push_back(mid / 2);
						i = 10;
						j = 10;
					}
				}
			}
		}

		REP(i, limit) {
			printf("%lld %lld\n", res[i].x, res[i].y);
		}
	}
	return 0;
}

//Solved after contest