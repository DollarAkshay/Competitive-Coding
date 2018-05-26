/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/APRIL18A/problems/CUTPLANT

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

int a[100000];
int b[100000];
bool v[100000];

int aMin[317];
int bMax[317];

int GLOB_LBSTEP = 0;
int GLOB_LSTEP = 0;

int GLOB_RBSTEP = 0;
int GLOB_RSTEP = 0;

void findRange(int &l, int &r, int val, int n, int sq) {

	int lBlock = l / sq;

	printf("l, lBlock = %d, %d\n", l, lBlock);

	while (lBlock > -1 && aMin[lBlock] >= val && bMax[lBlock] <= val) {
		lBlock--;
		GLOB_LBSTEP++;
	}

	if (lBlock != l / sq) {
		l = sq * (lBlock + 1);
	}
	printf("l, lBlock = %d, %d\n", l, lBlock);
	while (l > 0 && a[l - 1] >= val && b[l - 1] <= val) {
		l--;
		GLOB_LSTEP++;
	}

	int rBlock = r / sq;
	int maxBlock = (n - 1) / sq;

	printf("r, rBlock, max = %d, %d, %d\n", r, rBlock, maxBlock);

	while (rBlock < maxBlock && aMin[rBlock] >= val && bMax[rBlock] <= val) {
		rBlock++;
		GLOB_RBSTEP++;
	}

	if (rBlock != r / sq) {
		r = sq * (rBlock + 1) - 1;
	}

	printf("r, rBlock = %d, %d\n", r, rBlock);

	while (r < n - 1 && a[r + 1] >= val && b[r + 1] <= val) {
		r++;
		GLOB_RSTEP++;
	}
}

void trim(int l, int r, int h, int sq) {

	printf("TRIM to height %d from %d to %d\n", h, l, r);
	FOR(i, l, r) {
		a[i] = h;
		if (a[i] == b[i]) {
			v[i] = false;
		}
		aMin[i / sq] = min(aMin[i / sq], a[i]);
	}
}

class CompareDist {
  public:
	bool operator()(pii l, pii r) {
		return l.second < r.second || (l.second == r.second && l.first > r.first);
	}
};

int main() {

	int t;
	scanf("%d", &t);
	clock_t tt = clock();
	REP(tc, t) {
		clock_t ti = clock();
		bool impossible = false;
		int n, sq;
		scanf("%d", &n);
		sq = ceil(sqrt((double)n));

		REP(i, n) {
			scanf("%d", &a[i]);
		}

		REP(i, n) {
			scanf("%d", &b[i]);
			if (b[i] > a[i]) {
				impossible = true;
			}
		}

		if (impossible == true) {
			printf("-1\n");
			continue;
		}

		MSX(aMin, 1000000001);
		MSX(bMax, 0);

		REP(i, n) {
			aMin[i / sq] = min(aMin[i / sq], a[i]);
			bMax[i / sq] = max(b[i / sq], b[i]);
			if (a[i] == b[i]) {
				v[i] = false;
			}
			else {
				v[i] = true;
			}
		}

		priority_queue<pii, vector<pii>, CompareDist> pq;
		REP(i, n) {
			pq.push(mp(i, b[i]));
		}

		int res = 0;
		while (true) {
			int pos = -1, max = 0;

			while (pq.empty() == false) {
				pii top = pq.top();
				pq.pop();
				if (v[top.first] == true) {
					pos = top.first;
					max = top.second;
					break;
				}
			}

			if (pos == -1) {
				break;
			}

			int l = pos, r = pos;
			findRange(l, r, max, n, sq);
			trim(l, r, max, sq);
			res++;
		}

		// printf("TIME : %llf sec\n", ((double)clock() - ti) / CLOCKS_PER_SEC);
		printf("%d\n", res);
	}

	// printf("\nTOTAL TIME : %llf sec\n", ((double)clock() - tt) / CLOCKS_PER_SEC);

	// printf("GLOB_LBSTEP = %d\n", GLOB_LBSTEP);
	// printf("GLOB_LSTEP = %d\n", GLOB_LSTEP);
	// printf("GLOB_RBSTEP = %d\n", GLOB_RBSTEP);
	// printf("GLOB_RSTEP = %d\n", GLOB_RSTEP);

	return 0;
}

//
