/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/COOK91/problems/CCOOK

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
		int count = 0;
		REP(i, 5) {
			int x;
			scanf("%d", &x);
			if (x == 1) {
				count++;
			}
		}
		if (count == 0) {
			puts("Beginner");
		}
		else if (count == 1) {
			puts("Junior Developer");
		}
		else if (count == 2) {
			puts("Middle Developer");
		}
		else if (count == 3) {
			puts("Senior Developer");
		}
		else if (count == 4) {
			puts("Hacker");
		}
		else {
			puts("Jeff Dean");
		}
	}
	return 0;
}

//Solved