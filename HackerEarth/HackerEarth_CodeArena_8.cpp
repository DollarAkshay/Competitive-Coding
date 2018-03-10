/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/e99c6ab/

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

int t1[10000];
int t2[10000];

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d", &n);
		REP(i, n) {
			int a, b;
			scanf("%d %d", &a, &b);
			t1[i] = a;
			t2[i] = b;
		}

		SORT(t1, n);
		SORT(t2, n);

		int res = 0;
		int curPop = 0;
		int i = 0, j = 0;
		while (i < n) {
			if (t1[i] < t2[j]) {
				curPop++;
				i++;
			}
			else if (t2[j] < t1[i]) {
				curPop--;
				j++;
			}
			else {
				i++;
				j++;
			}
			res = max(res, curPop);
		}
		printf("%d\n", res);
	}
	return 0;
}

//