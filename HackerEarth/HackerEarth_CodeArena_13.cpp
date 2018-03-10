/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/c0a05c2/

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

vector<int> graph[100000];
vector<pii> edges;
vector<pii> dis;

int n, m, k;

void removeEdge(int i) {
	pii e = edges[i];
	graph[e.first].erase(remove(graph[e.first].begin(), graph[e.first].end(), e.second), graph[e.first].end());
	graph[e.second].erase(remove(graph[e.second].begin(), graph[e.second].end(), e.first), graph[e.second].end());
}

int bfs(int s) {

	int curTime = 0;
	int dis_i = 0;
	int vis[100000];
	queue<int> q;

	MSX(vis, -1);

	q.push(s);
	vis[s] = 0;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		REP(i, graph[u].size()) {
			int v = graph[u][i];
			if (vis[v] == -1) {
				vis[v] = vis[u] + 1;
				curTime = max(curTime, vis[v]);
				q.push(v);
			}
		}

		while (dis_i < k && dis[dis_i].first == curTime) {
			removeEdge(dis[dis_i].second);
			dis_i++;
		}
	}

	return vis[n - 1];
}

int main() {

	scanf("%d %d %d", &n, &m, &k);
	REP(i, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--;
		v--;
		graph[u].pb(v);
		graph[v].pb(u);
		edges.pb(mp(u, v));
	}

	REP(i, k) {
		int t, x;
		scanf("%d %d", &t, &x);
		x--;
		dis.pb(mp(t, x));
	}

	SORT(dis, dis.size());

	printf("%d\n", bfs(0));

	return 0;
}

//Solved - Time consuming