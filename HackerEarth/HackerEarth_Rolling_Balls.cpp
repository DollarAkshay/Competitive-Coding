/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-circuits-18/algorithm/rolling-balls-b8923a50/#c137309

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

int l, n, q, k;
vector<pair<int, int>> ball;

vector<pair<int, int>> cycle[100000];

bool cycleComplete() {
	REP(i, n) {
		if (cycle[k][i] != ball[i]) {
			return false;
		}
	}
	return true;
}

void updatePos() {

	k++;
	REP(i, n) {
		pair<int, int> nextPos = mp(cycle[k - 1][i].first + cycle[k - 1][i].second * 2 - 1, cycle[k - 1][i].second);
		cycle[k].pb(nextPos);
	}

	REP(i, n) {
		if (cycle[k][i].first == 2 || cycle[k][i].first == l ||
			(i > 0 && cycle[k][i].first == cycle[k][i - 1].first) ||
			(i < n - 1 && cycle[k][i].first == cycle[k][i + 1].first)) {
			cycle[k][i].second = !cycle[k - 1][i].second;
		}
	}
}

int main() {

	scanf("%d %d %d", &l, &n, &q);
	l *= 2;

	REP(i, n) {
		int pos;
		scanf("%d", &pos);
		ball.pb(mp(pos * 2, 0));
	}

	REP(i, n) {
		int dir;
		scanf("%d", &dir);
		ball[i].second = dir;
	}

	cycle[0] = ball;
	updatePos();
	while (!cycleComplete()) {
		updatePos();
	}

	REP(i, q) {
		int t, p;
		scanf("%d %d", &t, &p);
		t = (t * 2) % k;
		printf("%d\n", cycle[t][p - 1].first / 2);
	}

	return 0;
}

//Partially Solved - TLE