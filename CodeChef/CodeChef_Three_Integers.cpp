/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/LTIME58A/problems/AFK

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

int a[1000000];

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		ll int a, b, c;
		scanf("%lld %lld %lld", &a, &b, &c);

		ll int res = 0;
		if ((a + c) % 2 == 0) {
			res = abs(b - (a + c) / 2);
		}
		else {
			if (b > (a + c) / 2) {
				res = abs(b - (a + c + 1) / 2) + 1;
			}
			else {
				res = abs(b - (a + c) / 2) + 1;
			}
		}

		printf("%lld\n", res);
	}
	return 0;
}

//