/*~~~~~~~~~~~~~~~~~~*
*                  *
* $Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <random>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define MS0(x) memset(x, 0, sizeof(x))
#define MS1(x) memset(x, 1, sizeof(x))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define MOD 1000000007

int a[1000000];
vector<int> graph[1000000];
int degree[1000000];

FILE *fp = fopen(".\\data\\input.txt", "w");

mt19937 mt(time(NULL));

void printArray(vector<ll int> v) {
	REP(i, v.size()) {
		fprintf(fp, "%lld ", v[i]);
	}
	fprintf(fp, "\n");
}

ll int randomInt(ll int low, ll int high) {

	uniform_int_distribution<ll int> dist(low, high);

	return dist(mt);
}

void randomLowerString(int len) {

	REP(i, len)
	fprintf(fp, "%c", 'a' + rand() % 26);
	fprintf(fp, "\n");
}

void randomString(char s, int diff, int len) {

	REP(i, len)
	fprintf(fp, "%c", s + rand() % diff);
	fprintf(fp, "\n");
}

void randomUpperString(int len) {

	REP(i, len)
	fprintf(fp, "%c", 'A' + rand() % 26);
	fprintf(fp, "\n");
}

vector<ll int> randomArray(ll int low, ll int high, int n) {

	vector<ll int> res;
	REP(i, n) {
		res.push_back(randomInt(low, high));
	}
	return res;
}

string generatenumberstring(int len) {

	string res;

	while (res.size() < len) {
		int rand = randomInt(0, 9);
		if (rand == 0)
			res += "ZERO";
		else if (rand == 1)
			res += "ONE";
		else if (rand == 2)
			res += "TWO";
		else if (rand == 3)
			res += "THREE";
		else if (rand == 4)
			res += "FOUR";
		else if (rand == 5)
			res += "FIVE";
		else if (rand == 6)
			res += "SIX";
		else if (rand == 7)
			res += "SEVEN";
		else if (rand == 8)
			res += "EIGHT";
		else if (rand == 9)
			res += "NINE";
	}

	REP(i, res.size() / 2) {
		int a = randomInt(0, res.size() - 1);
		int b = randomInt(0, res.size() - 1);

		char t = res[a];
		res[a] = res[b];
		res[b] = t;
	}

	return res;
}

// Create and print a tree with first node index as 1
void generateRandomTree(int n) {

	// https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence
	vector<ll int> sequence = randomArray(1, n - 1, n - 2);

	FOR(i, 1, n) {
		degree[i] = 1;
		graph[i].clear();
	}

	REP(i, sequence.size()) {
		degree[sequence[i]] += 1;
	}

	REP(i, sequence.size()) {
		int u = sequence[i];
		FOR(j, 1, n) {
			if (degree[j] == 1) {
				graph[u].push_back(j);
				graph[j].push_back(u);
				degree[u] -= 1;
				degree[j] -= 1;
				break;
			}
		}
	}

	int u = 0, v = 0;
	FOR(i, 1, n) {
		if (degree[i] == 1) {
			if (u == 0) {
				u = i;
			}
			else {
				v = i;
			}
		}
	}

	graph[u].push_back(v);
	graph[v].push_back(u);
	degree[u] -= 1;
	degree[v] -= 1;

	FOR(i, 1, n) {
		REP(j, graph[i].size()) {
			int v = graph[i][j];
			if (i < v) {
				fprintf(fp, "%d %d\n", i, v);
			}
		}
	}
}

int main() {

	ll int t = randomInt(100, 100);
	fprintf(fp, "%lld\n", t);

	REP(tc, t) {
		ll int n = randomInt(5, 7);
		fprintf(fp, "%d\n", n);
		printArray(randomArray(1, 10, n));
	}

	printf("\nDONE :)\n\n");
	fclose(fp);
	return 0;
}