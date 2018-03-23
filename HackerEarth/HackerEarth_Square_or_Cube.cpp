/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/airtel-crack-the-code/algorithm/square-and-cube-2-dd08d321/

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
#define MAX 100000
#define MAXN 300000

int a[MAXN];
vector<int> prime;
vector<pii> cumFact[MAXN + 1];

void sieveOfEratosthenes() {

	bool p[MAX + 1];
	MSX(p, 1);
	p[0] = p[1] = 0;

	int limit = sqrt(MAX);
	FOR(i, 2, limit) {
		if (p[i] == true) {
			FOR(j, i * i, MAX) {
				p[j] = 0;
				j += i - 1;
			}
		}
	}

	// Put all the primes in a vector
	REP(i, MAX + 1) {
		if (p[i]) {
			prime.pb(i);
		}
	}
}

vector<pii> findPrimeFactors(int n) {

	vector<pii> res;
	REP(i, prime.size()) {
		if (n % prime[i] == 0) {
			int times = 0;
			while (n % prime[i] == 0) {
				n /= prime[i];
				times++;
			}
			res.pb(mp(prime[i], times));
			if (n == 1) {
				break;
			}
		}
	}

	return res;
}

vector<pii> findFactDiff(int l, int r) {

	vector<pii> res;
	int i = 0, j = 0;
	while (i < cumFact[l].size() && j < cumFact[r + 1].size()) {
		if (cumFact[l][i].first == cumFact[r + 1][j].first) {
			int diff = cumFact[r + 1][j].second - cumFact[l][i].second;
			if (diff > 0) {
				res.pb(mp(cumFact[r + 1][j].first, diff));
			}
			i++;
			j++;
		}
		else {
			res.pb(cumFact[r + 1][j]);
			j++;
		}
	}

	while (j < cumFact[r + 1].size()) {
		res.pb(cumFact[r + 1][j]);
		j++;
	}

	return res;
}

int main() {

	sieveOfEratosthenes();

	int n, q;
	scanf("%d %d", &n, &q);

	REP(k, n) {
		scanf("%d", &a[k]);
		vector<pii> fact = findPrimeFactors(abs(a[k]));
		if (a[k] < 0) {
			fact.pb(mp(-1, 1));
		}
		SORT(fact, fact.size());

		// Add fact to cumFact
		int i = 0, j = 0;
		while (i < cumFact[k].size() && j < fact.size()) {
			if (cumFact[k][i].first < fact[j].first) {
				cumFact[k + 1].pb(cumFact[k][i]);
				i++;
			}
			else if (fact[j].first < cumFact[k][i].first) {
				cumFact[k + 1].pb(fact[j]);
				j++;
			}
			else {
				cumFact[k + 1].pb(mp(fact[j].first, fact[j].second + cumFact[k][i].second));
				i++;
				j++;
			}
		}

		while (i < cumFact[k].size()) {
			cumFact[k + 1].pb(cumFact[k][i]);
			i++;
		}

		while (j < fact.size()) {
			cumFact[k + 1].pb(fact[j]);
			j++;
		}
	}

	REP(qr, q) {
		int l, r;
		scanf("%d %d", &l, &r);
		l--;
		r--;
		vector<pii> factPowers = findFactDiff(l, r);

		bool isCube = true;
		bool isSquare = true;

		REP(i, factPowers.size()) {
			if (factPowers[i].first == -1) {
				if (factPowers[i].second % 2 != 0) {
					isSquare = false;
				}
				continue;
			}
			if (factPowers[i].second % 2 != 0) {
				isSquare = false;
			}
			if (factPowers[i].second % 3 != 0) {
				isCube = false;
			}
		}

		if (isCube && isSquare) {
			printf("Both\n");
		}
		else if (isCube && !isSquare) {
			printf("Cube\n");
		}
		else if (!isCube && isSquare) {
			printf("Square\n");
		}
		else {
			printf("None\n");
		}
	}
	return 0;
}

//Solved