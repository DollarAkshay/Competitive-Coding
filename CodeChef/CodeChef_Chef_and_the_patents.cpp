/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/FEB18/problems/CHEFPTNT

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

char s[1000001];

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, m, x, k;
		scanf("%d %d %d %d", &n, &m, &x, &k);
		scanf("%s", s);
		int len = strlen(s), e = 0, o = 0;
		REP(i, len) {
			if (s[i] == 'E') {
				e++;
			}
			else {
				o++;
			}
		}

		bool isPossible = false;
		if (n <= k && (double)n / x <= (double)m) {
			FOR(i, 1, m) {
				if (i % 2 == 1) {
					int available = min(o, x);
					n -= available;
					o -= available;
				}
				else {
					int available = min(e, x);
					n -= available;
					e -= available;
				}
			}
			if (n <= 0) {
				isPossible = true;
			}
		}
		puts(isPossible ? "yes" : "no");
	}
	return 0;
}

//Solved