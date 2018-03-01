/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/march-easy-18/algorithm/holi-and-colorful-houses-eb2049cb/

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

char s[1000000];

int solve(int x, int y, int n, bool clockwise) {

	int sweet = 0, start = x;
	while (start != y) {
		int next = (start + 2 * clockwise - 1 + n) % n;
		if (s[start] != s[next]) {
			sweet++;
		}
		start = next;
	}
	return sweet;
}

int main() {

	int t, n, q;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d %d", &n, &q);
		scanf("%s", s);
		REP(i, q) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--;
			y--;
			int res = min(solve(x, y, n, true), solve(x, y, n, false));
			printf("%d\n", res);
		}
	}
	return 0;
}

//Solved