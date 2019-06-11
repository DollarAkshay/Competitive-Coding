/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JUNE19A/problems/COUNTIT

#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
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
#include <unordered_set>
#include <vector>

using namespace std;
using namespace std::chrono;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[100][100];

void printVector(const vector<int> &v) {
	REP(i, v.size()) {
		DB("%d ", v[i]);
	}
	DB("\n");
}

int zeroCount(const vector<int> &v) {
	int res = 0;
	REP(i, v.size()) {
		if (v[i] == 0) {
			res++;
		}
	}
	return res;
}

ll int bruteforce(int n, int m, int k) {

	set<vector<int>> seq_set;

	vector<int> seq(n + m);

	ll int possibleStates = pow(k, n * m);
	REP(s, possibleStates) {
		int val = s;

		REP(i, seq.size()) {
			seq[i] = 0;
		}

		REP(i, n) {
			REP(j, m) {
				int x = val % k;
				a[i][j] = x;
				seq[i] = max(seq[i], x);
				seq[n + j] = max(seq[n + j], x);
				val /= k;
			}
		}

		seq_set.insert(seq);
	}

	REP(i, n + m + 1) {
		for (const auto &v : seq_set) {
			if (zeroCount(v) == n + m - i) {
				printVector(v);
			}
		}
		printf("\n");
	}

	return seq_set.size();
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);

		ll int bfRes = bruteforce(n, m, k);
		printf("BF : %lld\n\n\n", bfRes);
	}
	return 0;
}

//