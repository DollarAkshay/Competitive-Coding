/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//http://codeforces.com/contest/935/problem/B

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

char s[100001];

int main() {

	int n;
	scanf("%d", &n);
	scanf("%s", s);

	int sign = 0;
	int sum = 0;
	int coins = 0;
	// Treat U as +1 and R as -1
	REP(i, n) {
		sum += s[i] == 'U' ? +1 : -1;
		if (sign == 0) {
			sign = sum > 0 ? +1 : -1;
		}
		else if ((sign == -1 && sum > 0) || (sign == +1 && sum < 0)) {
			coins++;
			sign = sum > 0 ? +1 : -1;
		}
	}

	printf("%d\n", coins);

	return 0;
}

//Solved pre-tests