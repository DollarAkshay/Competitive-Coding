/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://codejam.withgoogle.com/2018/challenges/0000000000007765/dashboard

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define REP(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define MOD 1000000007

vector<char> distinctLetters[10];
set<char> distinctLetterSet[10];
set<string> wordList;

string newWord;
string curWord;
bool found;

int intPow(int b, int e) {
	if (e == 0) {
		return 1;
	}
	else {
		return intPow(b, e - 1) * b;
	}
}

void findNewStringBacktrack(int index, int wordSize) {
	//printf("Found %s\n", curWord.c_str());
	if (index == wordSize) {
		if (wordList.count(curWord) == 0) {
			newWord = curWord;
			found = true;
		}
		return;
	}
	else {
		REP(i, distinctLetters[index].size()) {
			curWord += distinctLetters[index][i];
			findNewStringBacktrack(index + 1, wordSize);
			curWord.pop_back();
			if (found) {
				break;
			}
		}
	}
}

int main() {

	int t;
	scanf("%d", &t);
	REP(tc, t) {

		wordList.clear();
		REP(i, 10) {
			distinctLetters[i].clear();
			distinctLetterSet[i].clear();
		}

		int n, l;
		scanf("%d %d", &n, &l);

		REP(i, n) {
			char s[11];
			scanf("%s", s);
			string word = string(s);
			wordList.insert(word);

			REP(j, word.size()) {
				char c = word[j];
				if (distinctLetterSet[j].count(c) == 0) {
					distinctLetterSet[j].insert(c);
					distinctLetters[j].push_back(c);
				}
			}
		}

		int maxWords = 1;
		REP(i, l) {
			maxWords *= distinctLetters[i].size();
		}

		if (maxWords <= n) {
			printf("Case #%d: -\n", tc + 1);
		}
		else {
			found = false;
			newWord = 'xx';
			curWord = "";
			findNewStringBacktrack(0, l);
			printf("Case #%d: %s\n", tc + 1, newWord.c_str());
		}
	}
	return 0;
}

//Solved Small Input