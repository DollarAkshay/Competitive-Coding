/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/hiring/ninjacart-developer-hiring-challenge/problems/277602f9c7834e589b7677e686fc5bb8/

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

int emp[1001];
vector<int> outFloor[1001];
vector<int> inFloor[1001];

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {

		int n, p, w;
		scanf("%d", &n);
		scanf("%d %d", &p, &w);
		REP(i, n - 1) {
			scanf("%d", &emp[i]);
		}

		REP(i, n - 1) {
			vector<int> temp;
			REP(j, emp[i]) {
				int x;
				scanf("%d", &x);
				x--;
				temp.pb(x);
			}
			REP(j, emp[i]) {
				int x;
				scanf("%d", &x);
				inFloor[i].pb(x);
				outFloor[temp[j]].pb(x);
			}
		}

		int curP = 0, curW = 0;
		int endFloor = n;
		REP(i, n) {
			//Remove all people
			REP(j, outFloor[i].size()) {
				curP--;
				curW -= outFloor[i][j];
			}

			REP(j, inFloor[i].size()) {
				curP++;
				curW += inFloor[i][j];
			}

			if (curP > p || curW > w) {
				endFloor = i + 1;

				break;
			}
		}

		printf("%d\n", endFloor);

		REP(i, n) {
			outFloor[i].clear();
			inFloor[i].clear();
		}
	}
	return 0;
}

//Solved