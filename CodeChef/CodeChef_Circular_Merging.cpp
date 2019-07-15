/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JULY19A/problems/CIRMERGE

//#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

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

ll int bestCost;

void printVector(vector<ll int> a) {
	REP(i, a.size()) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int compressPair(vector<ll int> &a, int i) {
	ll int val = a[i] + a[(i + 1) % a.size()];
	if (i == a.size() - 1) {
		a.erase(a.begin() + i);
		a.erase(a.begin() + 0);
		a.insert(a.begin() + 0, val);
	}
	else {
		a.erase(a.begin() + i);
		a.erase(a.begin() + i);
		a.insert(a.begin() + i, val);
	}
	return val;
}

ll int bruteforce(vector<ll int> a) {

	if (a.size() == 1) {
		return 0;
	}

	ll int res = (ll int)1E18;
	ll int cost;
	REP(i, a.size()) {
		vector<ll int> b = a;
		cost = compressPair(b, i);
		res = min(res, cost + bruteforce(b));
	}

	return res;
}

ll int solve(vector<ll int> a) {

	if (a.size() == 1) {
		return 0;
	}
	else if (a.size() == 2) {
		return a[0] + a[1];
	}
	else if (a.size() == 3) {
		ll int minCost = (ll int)1E18;
		vector<int> pos;
		REP(i, a.size()) {
			REP(j, a.size() - 1) {
				vector<ll int> b = a;
				ll int curCost = 0;
				curCost += compressPair(b, i);
				curCost += compressPair(b, j);
				// printf("Cost for %d,%d : %d\n", i, j, curCost);
				if (curCost < minCost) {
					minCost = curCost;
					pos.clear();
					pos.push_back(i);
					pos.push_back(j);
				}
			}
		}

		ll int cost1 = compressPair(a, pos[0]);
		// ll int cost2 = compressPair(a, pos[1]);
		// printVector(a);
		return cost1 + solve(a);
	}
	else {
		ll int minCost = (ll int)1E18;
		vector<int> pos;
		REP(i, a.size()) {
			REP(j, a.size() - 1) {
				REP(k, a.size() - 2) {
					vector<ll int> b = a;
					ll int curCost = 0;
					curCost += compressPair(b, i);
					curCost += compressPair(b, j);
					curCost += compressPair(b, k);
					// printf("Cost for %d,%d : %d\n", i, j, curCost);
					if (curCost < minCost) {
						minCost = curCost;
						pos.clear();
						pos.push_back(i);
						pos.push_back(j);
						pos.push_back(k);
					}
				}
			}
		}

		ll int cost1 = compressPair(a, pos[0]);
		// ll int cost2 = compressPair(a, pos[1]);
		// ll int cost3 = compressPair(a, pos[2]);
		// printVector(a);
		return cost1 + solve(a);
	}
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

		if (bfRes != algoRes) {
			printVector(a);
			printf("BF   : %lld\n", bfRes);
			printf("ALGO : %lld\n\n", algoRes);
		}

		// printf("%lld\n", bfRes);
	}

	return 0;
}

// Bruteforce TLE
