/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/june-circuits-function-value-bdd25438/

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

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill_n(a, sizeof(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

struct Matrix2D {

	vector<vector<ll int>> m;
	int r, c;

	Matrix2D() {
		r = c = -1;
	}

	Matrix2D(int r, int c) {
		this->r = r;
		this->c = c;
		vector<vector<ll int>> zeroVector(r, vector<ll int>(c, 0));
		m = zeroVector;
	}

	Matrix2D(vector<vector<ll int>> a) {
		r = a.size();
		c = a[0].size();
		m = a;
	}

	Matrix2D identity() {
		assert(r == c);
		Matrix2D res(r, c);
		REP(k, r) {
			res.m[k][k] = 1;
		}
		return res;
	}

	void print() {
		printf("Matrix Size : %d x %d\n", r, c);
		REP(i, r) {
			REP(j, c) {
				printf("%lld ", m[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	Matrix2D operator*(Matrix2D const &rhs) {

		assert(c == rhs.r);

		Matrix2D res(r, rhs.c);

		REP(i, r) {
			REP(j, rhs.c) {
				REP(k, c) {
					res.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}

		return res;
	}

	Matrix2D operator%(int modVal) {

		REP(i, r) {
			REP(j, c) {
				m[i][j] %= modVal;
			}
		}

		return *this;
	}
};

Matrix2D tOdd = Matrix2D({{1, 1, 0, 0},
						  {0, 0, 1, 0},
						  {0, 3, 0, 0},
						  {0, 0, 0, 1}});

Matrix2D tEven = Matrix2D({{1, 1, 0, 0},
						   {0, 0, 1, 0},
						   {0, -1, 2, 1},
						   {0, 0, 0, 1}});

Matrix2D t = tEven * tOdd;
Matrix2D f_1 = Matrix2D({{0},
						 {1},
						 {1},
						 {2}});

Matrix2D fastPowMod(Matrix2D b, ll int e, ll int m) {

	if (e == 0) {
		return b.identity();
	}
	else if (e % 2 == 0) {
		Matrix2D res = fastPowMod(b, e / 2, m);
		return res * res % m;
	}
	else {
		Matrix2D res = fastPowMod(b, e / 2, m);
		return (res * res % m) * b % m;
	}
}

ll int getSumMod(ll int n, ll int m) {

	Matrix2D f_n;

	if (n % 2 == 0) {
		f_n = tOdd * fastPowMod(t, (n - 2) / 2, m) % m * f_1 % m;
	}
	else {
		f_n = fastPowMod(t, (n - 1) / 2, m) * f_1 % m;
	}

	return f_n.m[0][0];
}

int main() {

	getSumMod(1, MOD);
	getSumMod(2, MOD);
	getSumMod(3, MOD);
	getSumMod(4, MOD);
	getSumMod(5, MOD);
	getSumMod(6, MOD);

	int tc, m;
	scanf("%d %d", &tc, &m);
	REP(ti, tc) {
		ll int l, r;
		scanf("%lld %lld", &l, &r);
		ll int sumR = getSumMod(r + 1, m);
		ll int sumL = getSumMod(l, m);
		//printf("%lld %lld\n", sumR, sumL);

		ll int res = ((sumR - sumL) % m + m) % m;
		printf("%lld\n", res);
	}
	return 0;
}

//Partially Solved