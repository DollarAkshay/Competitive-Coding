/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/FEB18/problems/CHEFCHR

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

char s[500001];
int f[26];

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		MSX(f, 0);
		scanf("%s", s);
		int res = 0, len = strlen(s);
		REP(i, len) {
			f[s[i] - 'a']++;
			if (i >= 4) {
				f[s[i - 4] - 'a']--;
			}

			if (f['c' - 'a'] == 1 && f['h' - 'a'] == 1 && f['e' - 'a'] == 1 && f['f' - 'a'] == 1) {
				res++;
			}
		}

		if (res > 0) {
			printf("lovely %d\n", res);
		}
		else {
			printf("normal\n");
		}
	}
	return 0;
}

//Solved