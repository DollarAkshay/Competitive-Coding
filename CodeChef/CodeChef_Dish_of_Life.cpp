/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/APRIL17/problems/DISHLIFE

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>
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

unordered_set<int> s[1000000];

int main() {

	int t, n, k;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%d %d", &n, &k);
		unordered_set<int> super_set;
		REP(i, n) {
			s[i].clear();
			int p;
			scanf("%d", &p);
			REP(j, p) {
				int x;
				scanf("%d", &x);
				s[i].insert(x);
				super_set.insert(x);
			}
		}
		if (super_set.size() < k) {
			puts("sad");
		}
		else {
			bool some = false;
			unordered_map<int, int> super_set;
			REP(i, n) {
				for (auto it = s[i].begin(); it != s[i].end(); it++) {
					super_set[*it] += 1;
				}
			}

			REP(i, n) {
				for (auto it = s[i].begin(); it != s[i].end(); it++) {
					super_set[*it] -= 1;
				}

				bool all_elements = true;
				FOR(j, 1, k) {
					if (super_set[j] == 0) {
						all_elements = false;
						break;
					}
				}

				if (all_elements) {
					some = true;
					break;
				}

				for (auto it = s[i].begin(); it != s[i].end(); it++) {
					super_set[*it] += 1;
				}
			}
			puts(some ? "some" : "all");
		}
	}
	return 0;
}

//