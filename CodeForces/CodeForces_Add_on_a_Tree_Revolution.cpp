/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//http://codeforces.com/contest/1189/problem/D2

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
#define MAX 1000

struct Edge {
	int v, w;

	Edge() {
		v = w = -1;
	}

	Edge(int v, int w) {
		this->v = v;
		this->w = w;
	}
};

struct Operation {
	int u, v, w;

	Operation() {
		u = v = w = -1;
	}

	Operation(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
};

int d[MAX];
int p[MAX];
vector<struct Edge> ge[MAX];
int gc[MAX][MAX];
int l[MAX][MAX];

vector<struct Operation> op;

void computeLeaves(int n) {

	REP(i, n) {
		if (d[i] == 1) {
			int v = i;
			while (v != -1) {
				l[v][i] = 1;
				v = p[v];
			}
		}
	}
}

void dfs(int u, int parent, int n) {
	p[u] = parent;
	REP(i, ge[u].size()) {
		int v = ge[u][i].v;
		if (p[v] == -1 && v != 0) {
			dfs(v, u, n);
		}
	}
}

void addOperation(int u, int v, int w, int n) {

	if (d[u] == 1 && d[v] == 1) {
		op.push_back(Operation(u, v, w));
	}
	else if (d[u] == 1) {
		int a = -2, b = -3;
		REP(i, n) {
			if (l[v][i] == 1 && i != u) {
				a = i;
				break;
			}
		}

		REP(i, n) {
			if (d[i] == 1 && i != u && i != a) {
				b = i;
				break;
			}
		}

		op.push_back(Operation(u, b, w / 2));
		op.push_back(Operation(a, b, -w / 2));
		op.push_back(Operation(u, a, w / 2));
	}
	else if (d[v] == 1) {
		int a = -4, b = -5;
		REP(i, n) {
			if (l[u][i] == 1 && i != v) {
				a = i;
				break;
			}
		}

		REP(i, n) {
			if (d[i] == 1 && i != v && i != a) {
				b = i;
				break;
			}
		}

		op.push_back(Operation(v, b, w / 2));
		op.push_back(Operation(a, b, -w / 2));
		op.push_back(Operation(v, a, w / 2));
	}
	else {
		int a = -1, b = -1, c = -1, d = -1;
		REP(i, n) {
			if (a == -1) {
				if (l[u][i] == 1) {
					a = i;
				}
			}
			else {
				if (l[u][i] == 1) {
					b = i;
					break;
				}
			}
		}

		REP(i, n) {
			if (c == -1) {
				if (l[v][i] == 1 && i != a && i != b) {
					c = i;
				}
			}
			else {
				if (l[v][i] == 1 && i != a && i != b) {
					d = i;
					break;
				}
			}
		}

		op.push_back(Operation(a, d, w / 2));
		op.push_back(Operation(a, b, -w / 2));
		op.push_back(Operation(c, d, -w / 2));
		op.push_back(Operation(b, c, w / 2));
	}
}

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n - 1) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		u--;
		v--;
		d[u]++;
		d[v]++;
		ge[u].push_back(Edge(v, w));
		ge[v].push_back(Edge(u, w));
		gc[u][v] = 1;
		gc[v][u] = 1;
	}

	bool flag = true;
	REP(i, n) {
		if (d[i] == 2) {
			flag = false;
			break;
		}
	}

	printf(flag == true ? "YES\n" : "NO\n");

	if (flag) {
		FILL(p, -1);
		dfs(0, -1, n);
		computeLeaves(n);

		REP(i, n) {
			int u = i;
			REP(j, ge[i].size()) {
				int v = ge[i][j].v;
				int w = ge[i][j].w;
				if (u < v) {
					addOperation(u, v, w, n);
				}
			}
		}

		printf("%d\n", op.size());
		REP(i, op.size()) {
			printf("%d %d %d\n", op[i].u + 1, op[i].v + 1, op[i].w);
		}
	}
	return 0;
}

//Fail