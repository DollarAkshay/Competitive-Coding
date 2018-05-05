/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.techgig.com/codegladiators/question/Nk1Wd1hKbnRicDNFNzlaWjBtNyt3R296TkJNOEIzMWxIeUhQUEEwcU1VK3VacEVjemxwcThnNXBvWmZ6ZTJQYQ==/1&msg_type=1

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
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

struct Node {
	int depth, deg;
	int pathLeaf, parent;
	Node() {
		depth = -1;
		parent = -1;
		pathLeaf = 0;
		deg = 0;
	}
};

int gifts[100000];
struct Node nodes[100000];

vector<int> graph[100000];
vector<pii> paths;

void DFS(int node, int depth) {

	nodes[node].depth = depth;
	REP(i, graph[node].size()) {
		int child = graph[node][i];
		if (nodes[child].depth == -1) {
			DFS(child, depth + 1);
			nodes[child].parent = node;
		}
	}
}

bool isNodeInPath(int node, int u, int v) {

	int found = false;
	while (u != v) {
		if (u == node || v == node) {
			found = true;
			break;
		}
		if (nodes[u].depth > nodes[v].depth) {
			u = nodes[u].parent;
		}
		else {
			v = nodes[v].parent;
		}
	}

	return found;
}

int calcGiftsAt(int node) {
	if (nodes[node].deg == 1) {
		return nodes[node].pathLeaf;
	}
	else {
		int res = 0;
		REP(i, paths.size()) {
			pii p = paths[i];
			if (isNodeInPath(node, p.first, p.second)) {
				res++;
			}
		}
		return res;
	}
}

int main() {

	int n, m;
	scanf("%d %d", &n, &m);
	REP(i, n - 1) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--;
		v--;
		graph[u].pb(v);
		graph[v].pb(u);
		nodes[u].deg++;
		nodes[v].deg++;
	}

	DFS(0, 0);

	REP(i, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--;
		v--;
		paths.pb(mp(u, v));
		nodes[u].pathLeaf++;
		nodes[v].pathLeaf++;
	}

	int maxGifts = 0;
	REP(i, n) {
		int res = calcGiftsAt(i);
		maxGifts = max(maxGifts, res);
	}

	printf("%d\n", maxGifts);

	return 0;
}

//TLE