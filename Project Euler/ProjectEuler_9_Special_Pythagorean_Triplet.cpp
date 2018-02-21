/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://projecteuler.net/problem=9

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

bool inline isTriplet(int a, int b, int c) {
	return a * a + b * b == c * c;
}

int main() {

	int SUM = 1000;

	REP(a, SUM) {
		FOR(b, a + 1, SUM) {
			int c = SUM - a - b;
			if (a < b && b < c) {
				if (isTriplet(a, b, c)) {
					printf("%d %d %d\nPROD = %d", a, b, c, a * b * c);
				}
			}
		}
	}
	return 0;
}

//