/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-circuits-18/approximate/zulu-plays-football-f089a896/

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
#define MAX 17

int n, k;
int t[MAX - 1];
vector<int> opp[MAX - 1];

double prob = 0;
vector<int> denominator;

int played[MAX];
vector<int> playOrder;

void printOrder(bool valid) {
	printf(valid ? "VALID : " : "INVALID : ");
	REP(i, playOrder.size()) {
		printf("%d -> ", playOrder[i]);
	}
	printf("\n");
}

// Check whether the order in which the teams were played satisfy t
bool valid() {

	int curT = 0;
	REP(i, playOrder.size()) {
		if (playOrder[i] == t[curT]) {
			curT++;
		}

		if (curT == k) {
			break;
		}
	}

	return curT == k;
}

void calcProbability() {
	double d = 1;
	REP(i, denominator.size()) {
		d *= denominator[i];
	}
	prob += 1 / d;
}

void dfs(int curTeam) {

	played[curTeam] = 1;
	playOrder.pb(curTeam);

	if (curTeam == t[k - 1]) {
		if (valid()) {
			calcProbability();
		}
	}
	else {
		vector<int> remainingTeams;
		REP(i, opp[curTeam].size()) {
			if (played[opp[curTeam][i]] == 0) {
				remainingTeams.pb(opp[curTeam][i]);
			}
		}
		// Probability of selecting a team is 1.0/(size of remaining teams)
		denominator.pb(remainingTeams.size());
		REP(i, remainingTeams.size()) {
			dfs(remainingTeams[i]);
		}
		denominator.pop_back();
	}
	played[curTeam] = 0;
	playOrder.pop_back();
}

int main() {

	scanf("%d %d", &n, &k);
	REP(i, k) {
		scanf("%d", &t[i]);
	}

	// Reading beginning teams into opp[1] array
	FOR(i, 1, n) {
		int q;
		scanf("%d", &q);
		REP(j, q) {
			int x;
			scanf("%d", &x);
			opp[i].pb(x);
		}
	}

	// Starts by playing team 1 which will point to the opp[1] array
	dfs(1);
	printf("%.8lf\n", prob);

	return 0;
}

//