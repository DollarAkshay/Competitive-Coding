/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://projecteuler.net/problem=14

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
#define MAX 1000000
#define MUL 1

// First - ParentNode, depth
map<ll int, pair<ll int, ll int>> parent;

void buildGraph(ll int n) {

	if (parent.find(n) == parent.end()) {
		ll int next = n % 2 == 0 ? n / 2 : 3 * n + 1;
		parent[n] = mp(next, -1);
		buildGraph(next);
		parent[n].second = parent[next].second + 1;
	}
	else if (n != 1) {
		ll int parentNode = n % 2 == 0 ? n / 2 : 3 * n + 1;
		parent[n].second = parent[parentNode].second + 1;
	}
}

ll int getCollatzSequenceLength(ll int n) {
	if (n == 1) {
		return 1;
	}
	ll int next = n % 2 == 0 ? n / 2 : 3 * n + 1;
	return 1 + getCollatzSequenceLength(next);
}

int main() {

	parent[1] = mp(-1, 1);

	FOR(i, 1, MAX) {
		buildGraph(i);
	}

	printf("Done Building Graph\n");

	ll int maxDepth = -1, maxChainNum = 0;
	for (auto it = parent.begin(); it != parent.end(); it++) {
		pair<ll int, ll int> node = it->second;
		if (node.second > maxDepth) {
			maxDepth = node.second;
			maxChainNum = it->first;
			printf("Number = %lld | Depth = %lld\n", maxChainNum, maxDepth);
		}
	}

	return 0;
}

//