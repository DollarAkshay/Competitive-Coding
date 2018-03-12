/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/MARCH18A/problems/MINVOTE

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

int a[100000];
ll int csum[100001];
int votes[100000];

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d", &n);
		REP(i, n) {
			scanf("%d", &a[i]);
			csum[i + 1] = i == 0 ? a[i] : csum[i] + a[i];
		}

		MSX(votes, 0);

		// printf("CSUM : ");
		// REP(i, n + 1) {
		// 	printf("%d ", csum[i]);
		// }
		// printf("\n");

		REP(i, n) {
			int r = upper_bound(begin(csum), begin(csum) + n, csum[i + 1] + a[i]) - begin(csum) - 1;
			int l = lower_bound(begin(csum), begin(csum) + n, csum[i] - a[i]) - begin(csum) - 1;
			l = max(0, l);
			//printf("%d will vote from %d to %d\n", i, l, r);
			FOR(j, l, r) {
				if (j != i) {
					votes[j]++;
				}
			}
		}

		REP(i, n) {
			printf("%d ", votes[i]);
		}
		printf("\n");
	}
	return 0;
}

//Solved ! LOL