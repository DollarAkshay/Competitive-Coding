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
	bool operator<(const point &rhs) const {
		if (x < rhs.x) {
			return true;
		}
		if (x > rhs.x) {
			return false;
		}

		return y < rhs.y;
	}
	point operator+(const point &rhs) const {
		return point(x + rhs.x, y + rhs.y);
	}
};

struct point dir[4] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};
vector<point> poly;

ll int gcd(ll int a, ll int b) {
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

// On the polygon is treated as outside
bool isPointInPolygon(point p) {

	ll int prevSide = 0;
	int n = poly.size();
	REP(i, n) {
		// d = (x−x1)(y2−y1)−(y−y1)(x2−x1)
		ll int side = (p.x - poly[i].x) * (poly[(i + 1) % n].y - poly[i].y) - (p.y - poly[i].y) * (poly[(i + 1) % n].x - poly[i].x);
		if (side == 0) {
			return false;
		}

		if (prevSide == 0 ||
			(prevSide < 0 && side < 0) ||
			(prevSide > 0 && side > 0)) {
			prevSide = side;
		}
		else {
			return false;
		}
	}

	return true;
}

ll int doubleAreaOfPolygon() {
	// List of Points must be given in counter clockwise order
	int n = poly.size();
	ll int sum1 = 0;
	REP(i, n) {
		sum1 += poly[i].x * poly[(i + 1) % n].y;
	}

	ll int sum2 = 0;
	REP(i, n) {
		sum2 += poly[i].y * poly[(i + 1) % n].x;
	}

	return sum1 - sum2;
}

ll int countOfBoundaryPoints() {

	int n = poly.size();
	int extra = 0;
	REP(i, n) {
		int x1 = poly[i].x;
		int y1 = poly[i].y;
		int x2 = poly[(i + 1) % n].x;
		int y2 = poly[(i + 1) % n].y;
		extra += gcd(x1 - x2, y2 - y1) - 1;
	}

	return n + extra;
}

vector<point> findAllBoundaryPoints() {

	int n = poly.size();
	vector<point> extra;

	REP(i, n) {
		int x1 = poly[i].x;
		int y1 = poly[i].y;
		int x2 = poly[(i + 1) % n].x;
		int y2 = poly[(i + 1) % n].y;
		ll int f = gcd(abs(x1 - x2), abs(y2 - y1));
		FOR(i, 1, f - 1) {
			extra.pb(point(x1 + i * (x2 - x1) / f, y1 + i * (y2 - y1) / f));
		}
	}

	REP(i, extra.size()) {
		printf("EXTRA = %lld %lld\n", extra[i].x, extra[i].y);
	}

	vector<point> res;
	res.insert(res.end(), poly.begin(), poly.end());
	res.insert(res.end(), extra.begin(), extra.end());

	return res;
}

vector<point> findLatticePoints(int limit) {

	vector<point> res;
	set<point> v;
	queue<point> q;

	// Add all the integer points closest to the boundary that are inside
	REP(i, poly.size()) {
		q.push(poly[i]);
	}

	// Find the rest of the points that are inside the polygon.
	while (q.empty() == false) {
		point u = q.front();
		q.pop();

		REP(i, 4) {
			point next = u + dir[i];
			if (v.find(next) == v.end() && isPointInPolygon(next)) {
				res.pb(next);
				q.push(next);
				v.insert(next);
				if (res.size() >= limit) {
					break;
				}
			}
		}
		if (res.size() >= limit) {
			break;
		}
	}

	return res;
}

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d", &n);
		poly.clear();
		REP(i, n) {
			ll int x, y;
			scanf("%lld %lld", &x, &y);
			poly.pb(point(x, y));
		}
		ll int area = doubleAreaOfPolygon();
		ll int boundary_points = countOfBoundaryPoints();
		ll int lattice_points = area + 2 - boundary_points;
		assert(lattice_points % 2 == 0);
		lattice_points /= 2;
		ll int limit = (ll int)floor((long double)n / 10);
		if (lattice_points < limit) {
			printf("-1\n");
		}
		else {
			vector<point> res = findLatticePoints(limit);
			REP(i, res.size()) {
				printf("%lld %lld\n", res[i].x, res[i].y);
			}
		}
	}
	return 0;
}

//TLE