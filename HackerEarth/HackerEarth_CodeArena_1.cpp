/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//

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
#define MAX 1000

int deg[MAX];
vector<int> graph[MAX];

struct compare {
	constexpr bool operator()(pair<int, int> const &a, pair<int, int> const &b) const noexcept {
		return a.second < b.second;
	}
};

int main() {

	int n, m;
	scanf("%d %d", &n, &m);
	assert(n <= MAX);
	REP(i, m) {
		int s, e;
		scanf("%d %d", &s, &e);
		graph[s - 1].push_back(e - 1);
		graph[e - 1].push_back(s - 1);
		deg[s - 1]++;
		deg[e - 1]++;
	}

	priority_queue<pii, vector<pii>, compare> pq;
	set<int> cover;

	REP(i, n) {
		pq.push(mp(i, deg[i]));
	}

	int res = 0;
	while (!pq.empty()) {
		pii top = pq.top();
		pq.pop();
		res++;
		cover.insert(top.first);
		REP(i, graph[top.first].size()) {
			cover.insert(graph[top.first][i]);
		}

		assert(cover.size() <= n);

		if (cover.size() == n) {
			break;
		}
	}

	printf("%d\n", res);

	return 0;
}

//