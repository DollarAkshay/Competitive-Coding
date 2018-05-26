/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/APRIL18A/problems/GOODPREF

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

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		char s[1001];
		scanf("%s %d", s, &n);

		int len = strlen(s);
		ll int count[1000];
		MSX(count, 0);

		int aCount = 0, bCount = 0;
		ll int res = 0;
		int pattern = -1;

		REP(i, len * len) {
			int bin = i / len;

			if (bin >= n) {
				break;
			}

			if (i % len == 0 && bin >= 2 && count[bin - 1] == count[bin - 2]) {
				pattern = bin;
				break;
			}

			if (s[i % len] == 'a') {
				aCount++;
			}
			else {
				bCount++;
			}

			if (aCount > bCount) {
				count[bin]++;
				res++;
			}
		}

		if (pattern != -1) {
			res += (n - pattern) * count[pattern - 1];
		}

		printf("%lld\n", res);
	}
	return 0;
}

//Solved