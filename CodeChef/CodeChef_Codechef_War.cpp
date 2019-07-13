/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JULY19A/problems/CHFWAR

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

int a[1000000];

ll int getDamageAt(int p, int n) {

	n -= 1;
	ll int damage = 0;
	int rem = n - p / 2;
	int cycleLen = rem;

	if (p % 2 == 1 && p > 0) {
		damage += a[p - 1];
	}

	// vector<int> b;
	// FOR(i, p, n - 1) {
	// 	b.push_back(a[i]);
	// }
	// FOR(i, 0, p - 1) {
	// 	b.push_back(a[i]);
	// 	i++;
	// }

	ll int pass = 1;
	while (rem > 1) {
		if (rem % 2 == 0) {
			rem /= 2;
		}
		else {
			int pow2 = (1LL << pass);
			int k = (cycleLen - 1) / pow2;
			int bi = pow2 * k;
			int ai = bi < n - p ? bi + p : (bi - (n - p)) * 2;
			damage += a[ai];
			// assert(b[bi] = a[ai]);
			rem = (rem + 1) / 2;
		}
		pass += 1;
	}
	return damage;
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {
		int n, f;
		scanf("%d", &n);
		int minAttack = (int)1E9;
		REP(i, n - 1) {
			scanf("%d", &a[i]);
			minAttack = min(minAttack, a[i]);
		}
		scanf("%d", &f);

		if (minAttack > f) {
			printf("impossible\n");
		}
		else {
			printf("possible\n");
			int bestPos = -1;
			ll int minDamage = (ll int)1E18;
			REP(i, n - 1) {
				if (a[i] <= f) {
					ll int curDamage = getDamageAt(i, n);
					// DB("Damage at %2d : %d\n", i, curDamage);
					if (curDamage < minDamage) {
						minDamage = curDamage;
						bestPos = i;
					}
				}
			}
			printf("%d %lld\n", bestPos + 1, minDamage + f);
		}
	}
	return 0;
}

// Solved
