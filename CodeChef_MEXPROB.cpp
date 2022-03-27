/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

// https://www.codechef.com/OCT21A/problems/MEXPROB

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
#define S(format, ...) scanf(format, ##__VA_ARGS__)
#define Si(x) S("%d", &x)
#define Sll(x) S("%lld", &x)
#define P(format, ...) printf(format, ##__VA_ARGS__)
#define Pi(x) P("%d\n", x)
#define Pll(x) P("%lld\n", x)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];
unordered_set<int> s;

int mex(vector<int> a) {
	set<int> s(a.begin(), a.end());
	FOR(i, 0, 1E6) {
		if (s.find(i) == s.end()) {
			return i;
		}
	}
	return -1;
}

int bruteforce(vector<int> a, int k) {
	vector<int> res;
	REP(i, a.size()) {
		FOR(j, i, a.size() - 1) {
			vector<int> sub(a.begin() + i, a.begin() + j + 1);
			res.push_back(mex(sub));
		}
	}

	// Convert res vector into a frequency map
	map<int, int> freq;
	for (int i : res) {
		freq[i]++;
	}

	//Print all values in the frequency map
	for (auto it : freq) {
		P("%2d - %2d\n", it.first, it.second);
	}
}

int algo(int n) {
	return 0;
}

int main() {

	vector<int> v = {2};
	bruteforce(v, 0);
	P("--------------------------\n");
	v = {1, 2};
	bruteforce(v, 0);
	P("--------------------------\n");
	v = {0, 1, 2};
	bruteforce(v, 0);
	P("--------------------------\n");
	v = {0, 1, 2, 3};
	bruteforce(v, 0);
	P("--------------------------\n");
	P("--------------------------\n");
	v = {1};
	bruteforce(v, 0);
	P("--------------------------\n");
	v = {0, 1};
	bruteforce(v, 0);
	P("--------------------------\n");
	v = {2, 0, 1};
	bruteforce(v, 0);
	P("--------------------------\n");
	v = {1, 0, 1};
	bruteforce(v, 0);
	P("--------------------------\n");
	// Pi(res);

	// int t;
	// Si(t);
	// REP(tc, t) {
	// 	int n, k;
	// 	Si(n);
	// 	Si(k);
	// 	s.clear();
	// 	REP(i, n) {
	// 		Si(a[i]);
	// 	}
	// 	vector<int> v(a, a + n);
	// 	int res = bruteforce(v, k);
	// 	Pi(res);
	// }
	return 0;
}

//