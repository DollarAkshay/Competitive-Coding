/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-circuits-18/algorithm/zulu-and-games-0fee9adb/

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

int n;
bool v[5000];
pair<ll int, ll int> level[5000];
map<int, int> maxFreq;
vector<int> selected;

bool intersects(int a, int b) {
	if (level[a].first <= level[b].second && level[b].first <= level[a].second) {
		return true;
	}
	else {
		return false;
	}
}

bool canSelect(int lvl) {
	FORD(i, selected.size() - 1, 0) {
		if (intersects(lvl, selected[i])) {
			return false;
		}
	}
	return true;
}

bool valid() {

	REP(i, n) {
		if (canSelect(i)) {
			return false;
		}
	}
	return true;
}

int getMaxLevel() {
	ll int maxVal = 0;
	REP(i, selected.size()) {
		maxVal = max(maxVal, level[selected[i]].second);
		//printf("%d->", selected[i] + 1);
	}
	//printf("\n");
	return maxVal;
}

void addLevel(int lvl) {
	selected.pb(lvl);
	if (maxFreq.find(level[lvl].second) == maxFreq.end()) {
	}
}

ll int selectLevel(int lvl) {

	if (lvl == n) {
		if (valid()) {
			return getMaxLevel();
		}
		else {
			return 0;
		}
	}

	ll int res = 0;
	if (canSelect(lvl)) {
		selected.pb(lvl);
		v[lvl] = 1;
		res += selectLevel(lvl + 1);
		selected.pop_back();
		res += selectLevel(lvl + 1);
	}
	else {
		res += selectLevel(lvl + 1);
	}

	return res;
}

int main() {

	scanf("%d", &n);
	REP(i, n) {
		ll int x;
		scanf("%lld", &x);
		level[i] = mp(x, -1);
	}
	REP(i, n) {
		ll int x;
		scanf("%lld", &x);
		level[i].second = x;
	}

	SORT(level, n);

	ll int res = 0;
	REP(i, n) {
		if (v[i] == 0) {
			selected.pb(i);
			res += selectLevel(i);
			selected.pop_back();
		}
	}

	printf("%lld\n", res % MOD);
	return 0;
}

//Partially Solved - TLE