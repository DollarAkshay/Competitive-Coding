/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codejam.withgoogle.com/2018/challenges/00000000000000cb/dashboard/00000000000079cb

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

void print(vector<int> a) {
	REP(i, a.size()) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int errors(vector<int> a) {
	REP(i, a.size() - 1) {
		if (a[i] > a[i + 1]) {
			return i;
		}
	}
	return -1;
}

bool troubleSort(vector<int> &a) {
	bool done = false;
	while (!done) {
		done = true;
		REP(i, a.size() - 2) {
			if (a[i] > a[i + 2]) {
				done = false;
				int temp = a[i];
				a[i] = a[i + 2];
				a[i + 2] = temp;
			}
		}
	}
}

int solve(vector<int> a) {

	vector<int> even, odd;
	REP(i, a.size()) {
		if (i % 2) {
			odd.pb(a[i]);
		}
		else {
			even.pb(a[i]);
		}
	}

	SORT(even, even.size());
	SORT(odd, odd.size());

	vector<int> res;
	REP(i, odd.size()) {
		res.pb(even[i]);
		res.pb(odd[i]);
	}

	if (a.size() % 2 == 1) {
		res.pb(even.back());
	}

	REP(i, res.size() - 1) {
		if (res[i] > res[i + 1]) {
			return i;
		}
	}

	return -1;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		vector<int> a;
		scanf("%d", &n);
		REP(i, n) {
			int x;
			scanf("%d", &x);
			a.pb(x);
		}

		int res = solve(a);
		if (res == -1) {
			printf("Case #%d: OK\n", tc + 1);
		}
		else {
			printf("Case #%d: %d\n", tc + 1, res);
		}
	}
	return 0;
}

//Solved Small Testcase