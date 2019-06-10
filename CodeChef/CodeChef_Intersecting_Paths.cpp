/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JUNE19A/problems/INTRPATH

// #pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
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
#include <unordered_set>
#include <vector>

using namespace std;
using namespace std::chrono;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

high_resolution_clock::time_point timer;
bool inPath[300000];
int nodeDepth[300000];
int parent[300000];
int children[300000];
vector<int> g[300000];

void scanint(int &x) {
	register int c = getchar_unlocked();
	x = 0;
	int neg = 0;
	for (; ((c < 48 || c > 57) && c != '-'); c = getchar_unlocked())
		;
	if (c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	for (; c > 47 && c < 58; c = getchar_unlocked()) {
		x = (x << 1) + (x << 3) + c - 48;
	}
	if (neg)
		x = -x;
}

int dfs(int node, int depth) {
	nodeDepth[node] = depth;

	REP(i, g[node].size()) {
		int v = g[node][i];
		if (nodeDepth[v] == -1) {
			parent[v] = node;
			children[node] += dfs(v, depth + 1);
		}
	}

	return children[node] + 1;
}

vector<int> getPath(int a, int b) {

	vector<int> vertSet;
	while (a != b) {
		if (nodeDepth[a] > nodeDepth[b]) {
			vertSet.push_back(a);
			a = parent[a];
		}
		else {
			vertSet.push_back(b);
			b = parent[b];
		}
	}
	vertSet.push_back(a);
	return vertSet;
}

ll int solve(int a, int b) {

	ll int res = 0;
	vector<int> path = getPath(a, b);

	for (const auto &u : path) {
		inPath[u] = true;
	}

	vector<int> childPaths;

	if (rand() % 100 <= 0) {
		//DB("Path Size : %d\n", path.size());
	}

	for (const auto &u : path) {
		childPaths.clear();
		REP(i, g[u].size()) {
			int v = g[u][i];
			if (inPath[v] == false) {
				if (parent[u] == v) {
					childPaths.push_back(children[0] - children[u]);
				}
				else {
					childPaths.push_back(children[v] + 1);
				}
			}
		}

		REP(i, childPaths.size()) {
			res += childPaths[i];
			FOR(j, i + 1, childPaths.size() - 1) {
				res += childPaths[i] * childPaths[j];
			}
		}

		res++;
	}

	for (const auto &u : path) {
		inPath[u] = false;
	}

	return res;
}

int main() {

	DB("BEGIN\n");
	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, q;
		scanint(n);
		scanint(q);
		//scanf("%d %d", &n, &q);

		// Clear globals
		MSX(nodeDepth, -1);
		MSX(parent, -1);
		MSX(children, 0);
		REP(i, n) {
			g[i].clear();
		}

		timer = high_resolution_clock::now();
		REP(i, n - 1) {
			int u, v;
			scanint(u);
			scanint(v);
			//scanf("%d %d", &u, &v);
			u--;
			v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(0, 0);
		ll int ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
		DB("Time Taken : %.3lf ms\n", ns / 1E6);

		timer = high_resolution_clock::now();
		REP(i, q) {
			int a, b;
			scanint(a);
			scanint(b);
			//scanf("%d %d", &a, &b);
			a--;
			b--;

			// int bfRes = bruteForce(a, b, n);
			int algoRes = solve(a, b);

			// printf("BF   : %lld\n", bfRes);
			// printf("%lld\n", algoRes);
		}
		ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
		DB("Time Taken : %.3lf ms\n", ns / 1E6);
	}
	return 0;
}

//