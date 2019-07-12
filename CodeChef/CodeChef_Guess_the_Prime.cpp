/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JULY19A/problems/GUESSPRM

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

int a[1000000];

bool isPrime(ll int n) {

	if (n < 2) {
		return false;
	}

	int limit = sqrt(n);
	FOR(i, 2, limit) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

vector<int> primeFactors(ll int n) {

	vector<int> res;
	int limit = sqrt(n);
	FOR(i, 1, limit) {
		if (n % i == 0) {
			if (isPrime(i)) {
				res.push_back(i);
			}
			if (n / i > limit && isPrime(n / i)) {
				res.push_back(n / i);
			}
		}
	}

	SORT(res, res.size());

	// DB("Prime Factors of %lld : ", n);
	// REP(i, res.size()) {
	// 	DB("%d ", res[i]);
	// }
	// DB("\n\n");

	return res;
}

int numberWithUniqueModValues(vector<int> factors) {

	int start = (int)sqrt(factors.back()) + 1;

	set<int> s;

	FOR(n, start, start + 10000) {
		s.clear();
		REP(i, factors.size()) {
			int modVal = (ll int)n * n % factors[i];
			if (s.find(modVal) == s.end()) {
				s.insert(modVal);
			}
			else {
				break;
			}
		}
		if (s.size() == factors.size()) {
			return n;
		}
	}

	return -1;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		ll int res1, res2;
		printf("1 31623\n");
		fflush(stdout);
		scanf("%lld", &res1);

		ll int multiple = 31623LL * 31623 - res1;
		vector<int> factors = primeFactors(multiple);
		int n = numberWithUniqueModValues(factors);

		if (n == -1) {
			assert(1 == 0);
		}

		printf("1 %d\n", n);
		fflush(stdout);
		scanf("%lld", &res2);
		REP(i, factors.size()) {
			int modVal = (ll int)n * n % factors[i];
			if (modVal == res2) {
				printf("2 %d\n", factors[i]);
				break;
			}
		}

		string s;
		cin >> s;
		if (s == "No") {
			return 1;
		}
	}
	return 0;
}

//Solved :D Wow Didnt expect that.