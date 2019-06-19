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
#define SIZE 3000000

high_resolution_clock::time_point timer;
int nodeDepth[SIZE];
int parent[SIZE];
int children[SIZE];
vector<vector<int>> paths[SIZE];
vector<int> g[SIZE];

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

	vector<int> vertSetA;
	vector<int> vertSetB;
	while (a != b) {
		if (nodeDepth[a] > nodeDepth[b]) {
			vertSetA.push_back(a);
			a = parent[a];
		}
		else {
			vertSetB.push_back(b);
			b = parent[b];
		}
	}

	vertSetA.push_back(a);
	FORD(i, vertSetB.size() - 1, 0) {
		vertSetA.push_back(vertSetB[i]);
	}
	return vertSetA;
}

ll int solve(int a, int b) {

	ll int res = 0;
	vector<int> path = getPath(a, b);

	vector<int> childPaths;

	REP(i, path.size()) {

		int prevNode = i > 0 ? path[i - 1] : -1;
		int curNode = path[i];
		int nextNode = i < path.size() - 1 ? path[i + 1] : -1;

		int prevNodeIndex = -1;
		int nextNodeIndex = -1;
		int curEdges = g[curNode].size();
		REP(j, curEdges) {
			if (g[curNode][j] == prevNode) {
				prevNodeIndex = j;
			}
			if (g[curNode][j] == nextNode) {
				nextNodeIndex = j;
			}
		}

		res += paths[curNode][curEdges].back();
		if (prevNodeIndex != -1) {
			res += -2 * paths[curNode][prevNodeIndex].back() + paths[curNode][prevNodeIndex][prevNodeIndex];
		}
		if (nextNodeIndex != -1) {
			res += -2 * paths[curNode][nextNodeIndex].back() + paths[curNode][nextNodeIndex][nextNodeIndex];
		}
		if (prevNodeIndex != -1 && nextNodeIndex != -1) {
			res += 2 * paths[curNode][prevNodeIndex][nextNodeIndex];
		}

		res++;
	}

	return res;
}

void calculatePaths(int n) {

	REP(k, n) {
		int edges = g[k].size();
		SORT(g[k], edges);

		REP(i, edges) {
			vector<int> row;
			int rowSum = 0;
			REP(j, edges) {
				int childCountI = parent[k] == g[k][i] ? children[0] - children[k] : children[g[k][i]] + 1;
				int childCountJ = parent[k] == g[k][j] ? children[0] - children[k] : children[g[k][j]] + 1;
				if (i == j) {
					row.push_back(childCountI);
					rowSum += childCountI;
				}
				else {
					row.push_back(childCountI * childCountJ);
					rowSum += childCountI * childCountJ;
				}
			}
			row.push_back(rowSum);
			paths[k].push_back(row);
		}

		// Compute Column Sum
		vector<int> row;
		REP(j, edges + 1) {
			int colSum = 0;
			REP(i, edges) {
				colSum += paths[k][i][j];
			}
			row.push_back(colSum);
		}
		paths[k].push_back(row);
	}
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
		calculatePaths(n);
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
			printf("%lld\n", algoRes);
		}
		ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
		DB("Time Taken : %.3lf ms\n", ns / 1E6);
	}
	return 0;
}

//