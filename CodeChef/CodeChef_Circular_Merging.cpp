/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JULY19A/problems/CIRMERGE

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

void printVector(vector<ll int> a) {
	REP(i, a.size()) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

ll int bruteforce(vector<ll int> a) {

	if (a.size() == 1) {
		return 0;
	}

	ll int res = (ll int)1E18;
	ll int cost;
	REP(i, a.size() - 1) {
		vector<ll int> b = a;
		cost = b[i] + b[i + 1];
		b.erase(b.begin() + i);
		b.erase(b.begin() + i);
		b.insert(b.begin() + i, cost);
		res = min(res, cost + bruteforce(b));
	}

	cost = a.front() + a.back();
	a.erase(a.begin());
	a.erase(a.end());
	a.insert(a.begin(), cost);
	res = min(res, cost + bruteforce(a));

	return res;
}

ll int solve(vector<ll int> a) {
	ll int res = 0;

	while (a.size() > 1) {

		// Find smallest pair
		ll int minVal = (ll int)1E18;
		int pos = -1;
		REP(i, a.size()) {
			ll int pairVal = a[i] + a[(i + 1) % a.size()];
			if (pairVal < minVal) {
				minVal = pairVal;
				pos = i;
			}
		}

		//Do operation
		if (pos == a.size() - 1) {
			a.erase(a.begin() + pos);
			a.erase(a.begin() + 0);
			a.insert(a.begin() + 0, minVal);
		}
		else {
			a.erase(a.begin() + pos);
			a.erase(a.begin() + pos);
			a.insert(a.begin() + pos, minVal);
		}

		res += minVal;
	}

	return res;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {

		int n;
		vector<ll int> a;

		scanf("%d", &n);
		REP(i, n) {
			ll int x;
			scanf("%lld", &x);
			a.push_back(x);
		}

		ll int bfRes = bruteforce(a);
		ll int algoRes = solve(a);
		printf("BF   : %lld\n", bfRes);
		printf("ALGO : %lld\n", algoRes);
	}
	return 0;
}

//