/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/FEB18/problems/CHANOQ

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

int crosses[100000];

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		vector<pii> segments;
		int n, q;
		scanf("%d", &n);
		REP(i, n) {
			int l, r;
			scanf("%d %d", &l, &r);
			segments.pb(mp(l, r));
		}
		scanf("%d", &q);
		REP(qr, q) {

			REP(i, n) {
				crosses[i] = 0;
			}
			int m;
			scanf("%d", &m);
			REP(i, m) {
				int x;
				scanf("%d", &x);
				REP(j, n) {
					if (segments[j].first <= x && x <= segments[j].second) {
						crosses[j]++;
					}
				}
			}

			int good_segments = 0;
			REP(j, n) {
				if (crosses[j] % 2 == 1) {
					good_segments++;
				}
			}
			printf("%d\n", good_segments);
		}
	}
	return 0;
}

//TLE