/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/codearena/ring/ba216ab/

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

bool isPrime(ll int x) {
	int lim = sqrt(x);
	FOR(i, 2, lim) {
		if (x % i == 0)
			return false;
	}
	return true;
}

vector<int> findPrimeFactors(int n) {

	vector<int> res;
	int limit = sqrt(n);
	FOR(i, 2, limit) {
		if (n % i == 0) {
			int _i = n / i;
			while (n % i == 0) {
				n /= i;
				res.pb(i);
			}

			if (i != limit && isPrime(n / i)) {

				while (n % _i == 0) {
					n /= _i;
					res.pb(_i);
				}
			}
		}
	}

	return res;
}

int main() {

	int n;
	scanf("%d", &n);
	vector<int> res = findPrimeFactors(n);
	SORT(res, res.size());
	vector<int> number;

	int i = res.size() - 1;
	int curProd = 1;
	while (i >= 0) {
		while (i >= 0 && curProd * res[i] < 10) {
			curProd *= res[i];
			i--;
		}
		number.pb(curProd);
		curProd = 1;
	}

	REV(number, number.size());

	ll int y = 0;
	REP(i, number.size()) {
		y = (y * 10 + number[i]) % MOD;
	}
	printf("%lld\n", y);

	return 0;
}

//Question is so bad