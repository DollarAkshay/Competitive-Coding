/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

// https://codeforces.com/problemset/problem/1223/C

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

int arr[1000000];
int cs[1000000];

int algo(int n, int x, int a, int y, int b, int k) {

	SORT(arr, n);
	REV(arr, n);

	int xVal = x * (n / a);
	int yVal = y * (n / b);

	int price = 0;
	REP(i, n) {
		if ((i + 1) % a == 0) {
			price += x * arr[i];
		}
		if ((i + 1) % b == 0) {
			price += y * arr[i];
		}

		if (price >= k) {
			return i + 1;
		}
	}
	return -1;
}

int main() {

	int t;
	Si(t);
	REP(tc, t) {
		int n;
		Si(n);

		int sum = 0;
		REP(i, n) {
			Si(arr[i]);
			arr[i] /= 100;
			sum += arr[i];
			cs[i] = sum;
		}
		int x, a, y, b, k;
		Si(x);
		Si(a);
		Si(y);
		Si(b);
		Si(k);
		int res = algo(n, x, a, y, b, k);
		Pi(res);
	}
	return 0;
}

//