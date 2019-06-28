/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/xor-paths-dd39904a/

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
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

struct Edge {
	int v;
	int w;

	Edge() {
		v = -1;
		w = -1;
	}

	Edge(int v, int w) {
		this->v = v;
		this->w = w;
	}
};

vector<struct Edge> g[10];

bool visited[10];
int xorFreq[10];

int dfs(int u, int val) {

	visited[u] = true;
	xorFreq[val]++;

	REP(i, g[u].size()) {
		Edge e = g[u][i];
		if (visited[e.v] == false) {
			dfs(e.v, val ^ e.w);
		}
	}

	visited[u] = false;
}

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n - 1) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		u--;
		v--;
		g[u].push_back(Edge(v, w));
		g[v].push_back(Edge(u, w));
	}

	// O(n * n)
	REP(i, n) {
		dfs(i, 0);
	}

	// O(n * log2 n)
	ll int res = 0;
	REP(i, 10) {
		res = (res + xorFreq[i] * xorFreq[i] % MOD) % MOD;
		REP(j, 3) {
			int offBy1 = i ^ (1 << j);
			res = (res + xorFreq[i] * xorFreq[offBy1] % MOD) % MOD;
		}
	}

	printf("%lld\n", res);

	return 0;
}

//