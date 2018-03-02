/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerrank.com/contests/101hack53/challenges/cut-board

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

int a[1000000];

void specialCase(int m, int n, int x, int y) {

	FOR(i, x + 1, m) {
		printf("1 %d 1 %d\n", i, i + 1);
		i++;
	}

	FOR(i, 2, n - 1) {
		// 1 Vertical Domino
		printf("%d 1 %d 1\n", i, i + 1);
		FOR(j, 2, m) {
			printf("%d %d %d %d\n", i, j, i, j + 1);
			printf("%d %d %d %d\n", i + 1, j, i + 1, j + 1);
			j++;
		}
		i++;
	}

	FORD(i, m - y, 1) {
		printf("%d %d %d %d\n", n, i, n, i - 1);
		i--;
	}
}

int main() {

	int n, m, x, y;
	scanf("%d %d %d %d", &n, &m, &x, &y);
	//assert(n != 2);
	int totalCells = n * m - x - y;
	if (totalCells % 2 == 0) {
		int dominoCount = totalCells / 2;
		printf("YES\n%d\n", dominoCount);

		if (m % 2 == 1 && (m - y) % 2 == 0 && (m - x) % 2 == 0) {
			specialCase(m, n, x, y);
		}
		else {

			int k = 0;
			int topDir = 1, botDir = -1;
			pii top = mp(x + 1, 1), bot = mp(m - y, n);

			while (k < dominoCount / 2) {
				// ******** Lay Dominoes from Top ********
				if ((topDir == 1 && top.first + 1 <= m) || (topDir == -1 && top.first - 1 >= 1)) {
					// Horizontal Domino
					printf("%d %d %d %d\n", top.second, top.first, top.second, top.first + topDir);
				}
				else if ((topDir == 1 && top.first <= m) || (topDir == -1 && top.first >= 1)) {
					// Vertical Domino
					printf("%d %d %d %d\n", top.second, top.first, top.second + 1, top.first);
				}

				// Calculate next top
				if ((topDir == 1 && top.first == m - 1) || (topDir == -1 && top.first == 2)) {
					top.first = topDir == -1 ? 1 : m;
					top.second++;
					topDir = -topDir;
				}
				else if ((topDir == 1 && top.first == m) || (topDir == -1 && top.first == 1)) {
					top.first = topDir == -1 ? 2 : m - 1;
					top.second++;
					topDir = -topDir;
				}
				else {
					top.first += topDir * 2;
				}

				// ******** Lay Dominoes from Bottom ********
				if ((botDir == 1 && bot.first + 1 <= m) || (botDir == -1 && bot.first - 1 >= 1)) {
					// Horizontal Domino
					printf("%d %d %d %d\n", bot.second, bot.first, bot.second, bot.first + botDir);
				}
				else if ((botDir == 1 && bot.first <= m) || (botDir == -1 && bot.first >= 1)) {
					// Vertical Domino
					printf("%d %d %d %d\n", bot.second, bot.first, bot.second - 1, bot.first);
				}

				// Calculate next bot
				if ((botDir == 1 && bot.first == m - 1) || (botDir == -1 && bot.first == 2)) {
					bot.first = botDir == -1 ? 1 : m;
					bot.second--;
					botDir = -botDir;
				}
				else if ((botDir == 1 && bot.first == m) || (botDir == -1 && bot.first == 1)) {
					bot.first = botDir == -1 ? 2 : m - 1;
					bot.second--;
					botDir = -botDir;
				}
				else {
					bot.first += botDir * 2;
				}

				k++;
			}

			if (dominoCount % 2 == 1) {
				if ((topDir == 1 && top.first + 1 <= m) || (topDir == -1 && top.first - 1 >= 1)) {
					// Horizontal Domino
					printf("%d %d %d %d\n", top.second, top.first, top.second, top.first + topDir);
				}
				else if ((topDir == 1 && top.first <= m) || (topDir == -1 && top.first >= 1)) {
					// Vertical Domino
					printf("%d %d %d %d\n", top.second, top.first, top.second + 1, top.first);
				}
			}
		}
	}
	else {
		printf("NO");
	}
	return 0;
}

//