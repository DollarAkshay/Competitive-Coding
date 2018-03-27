/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/broadridge-code-bee-20/problems/419a978405e542bbb2801704d3c454b6/

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
		int m;
		char s[100001];
		scanf("%s %d\n", s, &m);
		int len = strlen(s);

		int f[26];
		MSX(f, 0);
		REP(i, len) {
			f[s[i] - 'a'] = 1;
		}

		REP(i, m) {
			char c1, space, c2;
			scanf("%c %c\n", &c1, &c2);
			f[c1 - 'a'] = 0;
			f[c2 - 'a'] = 0;
		}

		bool possible = true;
		REP(i, 26) {
			if (f[i] == 1) {
				possible = false;
				printf("%d ", i);
			}
		}
		puts(possible ? "YES" : "NO");
	}
	return 0;
}

//