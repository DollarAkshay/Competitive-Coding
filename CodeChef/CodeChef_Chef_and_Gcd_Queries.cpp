/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/MARCH18A/problems/GCDCNT

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <iterator>
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

vector<int> a;
vector<int> prime;
vector<int> primeProd[MAX + 1];

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

vector<int> findPrimeFactors(int n) {

	vector<int> res;
	REP(i, prime.size()) {
		if (n % prime[i] == 0) {
			res.pb(prime[i]);
			while (n % prime[i] == 0) {
				n /= prime[i];
			}
			if (n == 1) {
				break;
			}
		}
	}

	return res;
}

void addElement(int x, int index) {
	vector<int> pf = findPrimeFactors(x);
	int subset_count = 1 << pf.size();

	REP(subsetMask, subset_count) {
		ll int prod = 1;
		REP(i, pf.size()) {
			if (subsetMask & (1 << i)) {
				prod *= pf[i];
			}
		}
		auto insertPos = upper_bound(primeProd[prod].begin(), primeProd[prod].end(), index);
		primeProd[prod].insert(insertPos, index);
	}
}

void removeElement(int index) {

	int x = a[index];
	vector<int> pf = findPrimeFactors(x);
	int subset_count = 1 << pf.size();

	REP(subsetMask, subset_count) {
		ll int prod = 1;
		REP(i, pf.size()) {
			if (subsetMask & (1 << i)) {
				prod *= pf[i];
			}
		}
		auto posOfIndex = lower_bound(primeProd[prod].begin(), primeProd[prod].end(), index);
		primeProd[prod].erase(posOfIndex);
	}
}

int main() {

	sieveOfEratosthenes();

	int n;
	scanf("%d", &n);
	REP(i, n) {
		int x;
		scanf("%d", &x);
		a.pb(x);
		addElement(x, i);
	}

	int q;
	scanf("%d", &q);
	REP(qr, q) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int pos, value;
			scanf("%d %d", &pos, &value);
			pos--;
			removeElement(pos);
			a[pos] = value;
			addElement(value, pos);
		}
		else {
			int l, r, g;
			scanf("%d %d %d", &l, &r, &g);
			l--;
			r--;
			ll int res = 0;
			vector<int> pf = findPrimeFactors(g);
			int subset_count = 1 << pf.size();
			REP(subsetMask, subset_count) {
				ll int prod = 1, bitCount = 0;
				REP(i, pf.size()) {
					if (subsetMask & (1 << i)) {
						bitCount += 1;
						prod *= pf[i];
					}
				}
				int li = lower_bound(primeProd[prod].begin(), primeProd[prod].end(), l) - primeProd[prod].begin();
				int ri = upper_bound(primeProd[prod].begin(), primeProd[prod].end(), r) - primeProd[prod].begin() - 1;

				if (bitCount % 2 == 0) {
					res += ri - li + 1;
				}
				else {
					res -= ri - li + 1;
				}
			}

			printf("%lld\n", res);
		}
	}

	return 0;
}

//