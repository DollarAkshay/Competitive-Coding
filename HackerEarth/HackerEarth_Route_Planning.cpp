/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-circuits-18/algorithm/route-planning-c6409134/

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <functional>
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
#define MAX 100000

struct BusStop {
	int busID;
	int time, cycle;
	BusStop() {}
	BusStop(int id, int t, int c) {
		busID = id;
		time = t;
		cycle = c;
	}
};

vector<int> route[MAX];
vector<struct BusStop> busTime[MAX];
int res[MAX];

void modifiedDijkstra(int s) {

	int v[MAX];
	priority_queue<pii, vector<pii>, greater<pii>> q;

	MSX(res, -1);
	MSX(v, 0);

	res[0] = 0;
	q.push(mp(0, s));

	while (!q.empty()) {
		pii top = q.top();
		q.pop();
		int u = top.second;
		if (v[u] == 0) {
			v[u] = 1;
			REP(i, busTime[u].size()) {
				struct BusStop stop = busTime[u][i];
				int nextStop = route[stop.busID][(stop.time + 1) % stop.cycle];
				int waitTime = ((stop.time - res[u]) % stop.cycle + stop.cycle) % stop.cycle;
				int timeToNextStop = res[u] + waitTime + 1;
				if (res[nextStop] == -1 || res[nextStop] > timeToNextStop) {
					res[nextStop] = timeToNextStop;
					q.push(mp(timeToNextStop, nextStop));
				}
			}
		}
	}
}

int main() {

	int n, m;
	scanf("%d %d", &n, &m);
	REP(i, m) {
		int count;
		scanf("%d", &count);
		REP(j, count) {
			int x;
			scanf("%d", &x);
			x--;
			route[i].pb(x);
			busTime[x].pb(BusStop(i, j, count));
		}
	}

	modifiedDijkstra(0);
	FOR(i, 1, n - 1) {
		printf("%d ", res[i]);
	}
	printf("\n");

	return 0;
}

//Solved