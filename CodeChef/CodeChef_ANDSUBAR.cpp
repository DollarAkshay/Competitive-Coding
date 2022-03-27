/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

// https://www.codechef.com/OCT21A/problems/ANDSUBAR

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

int bruteforce(int n) {
	int bestLen = -1;
	FOR(i, 1, n) {
		int curAnd = 0b1111111111111111;
		FOR(j, i, n) {
			curAnd = curAnd & j;
			if (curAnd > 0 && j - i + 1 > bestLen) {
				bestLen = j - i + 1;
				// printf("%2d to %d = %2d\n", i, j, curAnd);
			}
			if (curAnd == 0) {
				break;
			}
		}
	}
	return bestLen;
}

int highestPowerOf2LteN(int n) {
	if (n < 1) {
		return 0;
	}

	int x = floor(log2(n));
	return 1 << x;
}

int algo(int n) {
	int p2 = highestPowerOf2LteN(n);
	return max(n - p2 + 1, p2 / 2);
}

int main() {

	// FOR(i, 1, 10000) {

	// 	if (i % 1000 == 0) {
	// 		printf("Processed upto %6d\n", i);
	// 	}

	// 	int algoRes = algo(i);
	// 	int bfRes = bruteforce(i);
	// 	if (algoRes != bfRes) {
	// 		printf("@n = %6d | Algo %d , BF = %d\n", i, algoRes, bfRes);
	// 	}
	// }

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n;
		scanf("%d", &n);
		cout << algo(n) << endl;
	}

	//  bruteforce(1000);
	return 0;
}

// Solved