/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard

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

int len;
char s[31];
int a[30];

int calcPower() {
	int res = 0;
	REP(i, len) {
		if (s[i] == 'S') {
			res += a[i];
		}
	}
	return res;
}

bool swap() {

	FORD(i, len - 1, 1) {
		if (s[i] == 'S' && s[i - 1] == 'C') {
			s[i] = 'C';
			s[i - 1] = 'S';
			a[i - 1] /= 2;
			return true;
		}
	}

	return false;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d %s", &n, s);
		len = strlen(s);
		int powVal = 1;
		REP(i, len) {
			if (s[i] == 'C') {
				powVal *= 2;
			}
			a[i] = powVal;
		}

		int hacks = 0;

		while (calcPower() > n) {
			int power_ = calcPower();
			bool swapSuccess = swap();
			if (!swapSuccess) {
				hacks = -1;
				break;
			}
			else {
				hacks++;
			}
		}

		if (hacks == -1) {
			printf("Case #%d: IMPOSSIBLE\n", tc + 1);
		}
		else {
			printf("Case #%d: %d\n", tc + 1, hacks);
		}
	}
	return 0;
}

//Solved Small Testcase