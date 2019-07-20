/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://codeforces.com/contest/1178/problem/B

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
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int f[1000001];

int main() {

	string s_;
	cin >> s_;

	string s = "";
	int totalW = 0;
	REP(i, s_.size()) {
		if (s_[i] == 'o') {
			s += "o";
		}
		else if (s_[i] == 'v' && i > 0 && s_[i - 1] == 'v') {
			s += "w";
			totalW++;
		}
	}

	ll int res = 0;
	int leftW = 0;
	REP(i, s.size()) {
		if (s[i] == 'o') {
			res += (ll int)leftW * (totalW - leftW);
		}
		else {
			leftW++;
		}
	}

	printf("%lld\n", res);

	return 0;
}

//Pretests passed
