/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://projecteuler.net/problem=43

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
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

ll int sum = 0;
int d[10];
set<int> used;

ll int fastPow(int b, int e) {
	if (e == 0) {
		return 1;
	}
	else {
		if (e % 2 == 0) {
			ll int res = fastPow(b, e / 2);
			return res * res;
		}
		else {
			return fastPow(b, e - 1) * b;
		}
	}
}

ll int generatePandigital(int digit) {

	if (digit == 4 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 2 != 0) {
		return 0;
	}
	else if (digit == 5 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 3 != 0) {
		return 0;
	}
	else if (digit == 6 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 5 != 0) {
		return 0;
	}
	else if (digit == 7 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 7 != 0) {
		return 0;
	}
	else if (digit == 8 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 11 != 0) {
		return 0;
	}
	else if (digit == 9 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 13 != 0) {
		return 0;
	}
	else if (digit == 10 && (d[digit - 3] * 100 + d[digit - 2] * 10 + d[digit - 1]) % 17 != 0) {
		return 0;
	}
	else if (digit == 10) {

		REP(i, 10) {
			sum += d[9 - i] * fastPow(10, i);
		}
		return 1;
	}
	else {
		ll int res = 0;
		REP(i, 10) {
			if (used.find(i) == used.end()) {
				d[digit] = i;
				used.insert(i);
				res += generatePandigital(digit + 1);
				used.erase(i);
			}
		}
		return res;
	}
}

int main() {

	printf("Numbers = %lld\n", generatePandigital(0));
	printf("Sum = %lld\n", sum);
	return 0;
}

//