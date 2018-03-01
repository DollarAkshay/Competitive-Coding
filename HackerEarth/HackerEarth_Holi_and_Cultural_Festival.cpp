/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/march-easy-18/algorithm/company-cc24027a/

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

int n, p, d, m;

int pr[2000];
int dr[2000];
int mr[2000];

int DP[80][80][80][80];

int recur(int i, int pl, int dl, int ml) {

	if (i < 80 && pl < 80 && dl < 80 && ml < 80 && DP[i][pl][dl][ml] > 0) {
		return DP[i][pl][dl][ml];
	}

	if (i >= n) {
		return 0;
	}

	int pVal = 0, dVal = 0, mVal = 0;
	if (pl > 0) {
		pVal = pr[i] + recur(i + 1, pl - 1, dl, ml);
	}
	if (dl > 0) {
		dVal = dr[i] + recur(i + 1, pl, dl - 1, ml);
	}
	if (ml > 0) {
		mVal = mr[i] + recur(i + 1, pl, dl, ml - 1);
	}

	int res = max(pVal, max(dVal, mVal));
	if (i < 80 && pl < 80 && dl < 80 && ml < 80) {
		DP[i][pl][dl][ml] = res;
	}
	return res;
}

int main() {

	scanf("%d %d %d %d", &n, &p, &d, &m);
	REP(i, n) {
		scanf("%d %d %d", &pr[i], &dr[i], &mr[i]);
	}

	printf("%lld\n", recur(0, p, d, m));
	return 0;
}

//