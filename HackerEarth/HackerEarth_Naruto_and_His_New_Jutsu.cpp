/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-easy-18/algorithm/naruto-and-divisors-1d0e45cc/

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
#include <unordered_set>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MS0(x) memset(x, 0, sizeof(x))
#define MS1(x) memset(x, 1, sizeof(x))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];

ll int oddDivSum(ll int n) {

	ll int sum = 0;
	int limit = sqrt(n);
	FOR(i, 1, limit) {
		if (n % i == 0) {
			if (i % 2 == 1) {
				sum += i;
			}
			if (n / i != limit && (n / i) % 2 == 1) {
				sum += n / i;
			}
		}
	}

	return sum;
}

int main() {

	ll int t, n;
	scanf("%lld", &t);
	REP(tc, t) {
		scanf("%lld", &n);
		printf("%lld\n", oddDivSum(n));
	}
	return 0;
}

//Solved