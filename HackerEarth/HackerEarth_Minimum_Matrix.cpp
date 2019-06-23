/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

// REFERENCE_IMAGE = https://i.imgur.com/niMf69q.png
//https://www.hackerearth.com/challenges/competitive/june-circuits-19/approximate/minimum-matrix-bypass-0c6b9b86/

// #pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <locale.h>
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
using namespace std::chrono;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int n, m;
int a[500][500];

int maxVal = -1;
pii maxPos;

pii redSize, greenSize, blueSize;

int seqCount = 0;
int scores[100];
vector<pii> sequences[100];

void horizontal_snake() {

	int curMax = a[0][0];
	int score = 0;

	REP(i, n) {
		REP(j, m) {
			int rj = i % 2 == 0 ? j : m - j - 1;
			sequences[seqCount].push_back(make_pair(i, rj));
			if (a[i][rj] > curMax) {
				score += 1;
				curMax = a[i][rj];
			}
		}
	}

	scores[seqCount] = score;
	seqCount++;
}

void vertical_snake() {

	int curMax = a[0][0];
	int score = 0;

	REP(j, m) {
		REP(i, n) {
			int ri = j % 2 == 0 ? i : n - i - 1;
			sequences[seqCount].push_back(make_pair(ri, j));
			if (a[ri][j] > curMax) {
				score += 1;
				curMax = a[ri][j];
			}
		}
	}

	scores[seqCount] = score;
	seqCount++;
}

// Go to max value
// L shape to max
// Red -> Green - > Blue (Refer to REFERENCE_IMAGE)
void maxFirst1() {

	//Check if red zone is proper
	if (redSize.first == 1 || (redSize.first % 2 != 0 && redSize.second % 2 == 0) || (redSize.first * redSize.second == 0 && maxPos.first != 0)) {
		return;
	}

	if (blueSize.first * blueSize.second > 0 &&
		(greenSize.first * greenSize.second == 0 ||
		 (greenSize.first % 2 != 0 && greenSize.second % 2 == 0))) {
		return;
	}

	int curMax = a[0][0];
	int score = 0;
	pii refPoint;

	REP(i, maxPos.first) {
		sequences[seqCount].push_back(make_pair(i, 0));
		if (a[i][0] > curMax) {
			score += 1;
			curMax = a[i][0];
		}
	}

	REP(j, maxPos.second + 1) {
		sequences[seqCount].push_back(make_pair(maxPos.first, j));
		if (a[maxPos.first][j] > curMax) {
			score += 1;
			curMax = a[maxPos.first][j];
		}
	}

	// Solve Red Part
	refPoint = make_pair(maxPos.first - 1, maxPos.second);
	if (redSize.first % 2 == 0) {
		REP(i, redSize.first) {
			REP(j, redSize.second) {
				int ri = i;
				int rj = i % 2 == 0 ? j : redSize.second - 1 - j;
				sequences[seqCount].push_back(make_pair(refPoint.first - ri, refPoint.second - rj));
			}
		}
	}
	else {
		REP(i, redSize.first - 2) {
			REP(j, redSize.second) {
				int ri = i;
				int rj = i % 2 == 0 ? j : redSize.second - 1 - j;
				sequences[seqCount].push_back(make_pair(refPoint.first - ri, refPoint.second - rj));
			}
		}
		FORD(j, redSize.second - 1, 0) {
			REP(i, 2) {
				int ri = j % 2 == 0 ? redSize.first - 2 + i : redSize.first - 1 - i;
				int rj = j;
				sequences[seqCount].push_back(make_pair(refPoint.first - ri, refPoint.second - rj));
			}
		}
	}

	// Solve Green Part
	refPoint = make_pair(0, maxPos.second + 1);
	if (greenSize.second % 2 == 0) {
		REP(i, greenSize.first) {
			REP(j, greenSize.second) {
				int ri = i;
				int rj = i % 2 == 0 ? j : greenSize.second - 1 - j;
				sequences[seqCount].push_back(make_pair(refPoint.first + ri, refPoint.second + rj));
			}
		}
	}
	else {
		REP(i, greenSize.first - 2) {
			REP(j, greenSize.second) {
				int ri = i;
				int rj = i % 2 == 0 ? j : greenSize.second - 1 - j;
				sequences[seqCount].push_back(make_pair(refPoint.first + ri, refPoint.second + rj));
			}
		}

		FORD(j, greenSize.second - 1, 0) {
			REP(i, 2) {
				int ri = j % 2 == 0 ? greenSize.first - 2 + i : greenSize.first - 1 - i;
				int rj = j;
				sequences[seqCount].push_back(make_pair(refPoint.first + ri, refPoint.second + rj));
			}
		}
	}

	// Solve Blue Part
	refPoint = make_pair(n - 1, maxPos.second);
	REP(i, blueSize.first) {
		REP(j, blueSize.second) {
			int ri = i;
			int rj = i % 2 == 0 ? j : blueSize.second - 1 - j;
			sequences[seqCount].push_back(make_pair(refPoint.first - ri, refPoint.second - rj));
		}
	}
	scores[seqCount] = score;
	seqCount++;
}

int findBestApproach() {

	int bestScore = n * m + 1;
	int bestSeq = -1;
	REP(i, seqCount) {
		if (scores[i] < bestScore) {
			bestScore = scores[i];
			bestSeq = i;
		}
	}

	return bestSeq;
}

void visualizeSequence(int s) {

	wchar_t dir[500][500];

	REP(i, m * n - 1) {
		pii cur = sequences[s][i];
		pii next = sequences[s][i + 1];

		// Up
		if (cur.first - next.first == 1 && cur.second == next.second) {
			dir[cur.first][cur.second] = 8593;
		}

		// Down
		if (cur.first - next.first == -1 && cur.second == next.second) {
			dir[cur.first][cur.second] = 8595;
		}

		// Left
		if (cur.first == next.first && cur.second - next.second == 1) {
			dir[cur.first][cur.second] = 8592;
		}

		// Right
		if (cur.first == next.first && cur.second - next.second == -1) {
			dir[cur.first][cur.second] = 8594;
		}
	}

	printf("\n Sequence : \n");
	REP(i, n) {
		REP(j, m) {
			DB("%lc ", dir[i][j]);
		}
		DB("\n");
	}
	DB("\n");
}

int main() {

	setlocale(LC_ALL, "");

	scanf("%d %d", &n, &m);
	REP(i, n) {
		REP(j, m) {
			scanf("%d", &a[i][j]);
			if (a[i][j] > maxVal) {
				maxVal = a[i][j];
				maxPos = make_pair(i, j);
			}
		}
	}

	redSize = maxPos;
	greenSize = make_pair(n, m - 1 - maxPos.second);
	blueSize = make_pair(n - 1 - maxPos.first, maxPos.second + 1);

	horizontal_snake();
	vertical_snake();

	assert(maxPos.first != 0);

	if (n >= 2 && m >= 2) {
		maxFirst1();
	}

	int bestSeq = findBestApproach();

	assert(sequences[bestSeq].size() == n * m);

	visualizeSequence(2);
	REP(i, sequences[bestSeq].size()) {
		// printf("%d %d\n", sequences[bestSeq][i].first + 1, sequences[bestSeq][i].second + 1);
	}

	return 0;
}

//
