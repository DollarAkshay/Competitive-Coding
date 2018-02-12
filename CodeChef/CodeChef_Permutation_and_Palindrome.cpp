/*~~~~~~~~~~~~~~~~~~*
*                  *
* Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/FEB18/problems/PERMPAL

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

char s[1000001];
char p[1000001];
int res[1000001];
vector<int> char_loc[26];

void getCharLocations(int len) {
	REP(i, 26) {
		char_loc[i].clear();
	}

	FORD(i, len - 1, 0) {
		char_loc[s[i] - 'a'].pb(i);
	}
}

void generatePalindrome(int len) {
	REP(i, len) {
		p[i] = s[res[i]];
	}
	p[len] = 0;
	printf("%s\n\n", p);
}

bool canPalindrome() {

	int odd = 0, even = 0;
	REP(i, 26) {
		if (char_loc[i].size() % 2 == 0) {
			even++;
		}
		else {
			odd++;
		}
	}

	return odd <= 1;
}

int main() {

	int t, n;
	scanf("%d", &t);
	REP(tc, t) {
		scanf("%s", s);
		int len = strlen(s);
		getCharLocations(len);
		if (canPalindrome()) {
			int k = 0;
			REP(i, 26) {
				while (char_loc[i].empty() == false) {
					if (char_loc[i].size() == 1) {
						res[len / 2] = char_loc[i].back();
						char_loc[i].pop_back();
					}
					else {
						res[k] = char_loc[i].back();
						char_loc[i].pop_back();
						res[len - 1 - k] = char_loc[i].back();
						char_loc[i].pop_back();
						k++;
					}
				}
			}

			REP(i, len) {
				printf("%d ", res[i] + 1);
			}
			printf("\n");
			// generatePalindrome(len);
		}
		else {
			puts("-1");
		}
	}
	return 0;
}

//Solved