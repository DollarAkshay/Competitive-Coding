/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.techgig.com/codegladiators/question/cFNrNGdiNUcxUzd6b3EraEJFWTlYczU5ZTNJVW1aZVpsemhLK3M1MFk0NDlHcEVrdVFuUC9iaFpwWUZNMEUvVw==/1&msg_type=1

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

vector<int> graph[100];

int leafCount_DFS(int node) {

	if (graph[node].size() == 0) {
		return 1;
	}
	else {
		int res = 0;
		REP(i, graph[node].size()) {
			int child = graph[node][i];
			res += leafCount_DFS(child);
		}
		return res;
	}
}

int main() {

	int n, root, x;
	scanf("%d", &n);
	REP(i, n) {
		int parent;
		scanf("%d", &parent);
		if (parent != -1) {
			graph[parent].pb(i);
		}
		else {
			root = i;
		}
	}

	scanf("%d", &x);
	printf("%d\n", leafCount_DFS(root) - leafCount_DFS(x));

	return 0;
}

//Solved