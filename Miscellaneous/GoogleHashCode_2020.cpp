/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://hashcodejudge.withgoogle.com/#/rounds/6313004828196864/

#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <random>
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
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define FILL(a, x) fill(begin(a), end(a), x)
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

string testcase_id[6] = {"a", "b", "c", "d", "e", "f"};
mt19937 mt(666);

int b, l, d;

struct Library {
	int id;
	int books, signup, ship;
	int total_book_score;
	vector<int> book_ids;

	Library() {}
};

bool library_sorter(Library const &lhs, Library const &rhs) {
	return (float)lhs.total_book_score / lhs.ship > (float)rhs.total_book_score / rhs.ship;
}

int s[100000];
struct Library library[100000];
bool book_shipped[100000];

int main() {

	REP(tc, 6) {
		string ip_filename = ".\\data\\" + testcase_id[tc] + "_input.txt";
		string op_filename = ".\\data\\" + testcase_id[tc] + "_output.txt";
		FILE *ip = fopen(ip_filename.c_str(), "r");
		FILE *op = fopen(op_filename.c_str(), "w");

		fscanf(ip, "%d %d %d", &b, &l, &d);
		REP(i, b) {
			fscanf(ip, "%d", &s[i]);
		}

		REP(i, l) {
			library[i].id = i;
			fscanf(ip, "%d %d %d", &library[i].books, &library[i].signup, &library[i].ship);
			library[i].book_ids.clear();
			library[i].total_book_score = 0;
			REP(j, library[i].books) {
				int book_id;
				fscanf(ip, "%d", &book_id);
				library[i].book_ids.push_back(book_id);
				library[i].total_book_score += s[book_id];
			}
		}

		// vector<int> lib_order;
		// REP(i, l) {
		// 	lib_order.push_back(i);
		// }
		// shuffle(lib_order.begin(), lib_order.end(), mt);
		sort(begin(library), begin(library) + l, library_sorter);

		int total_libs = 0;
		FILL(book_shipped, 0);
		REP(i, l) {
			int books_left = 0;
			REP(j, library[i].books) {
				if (book_shipped[library[i].book_ids[j]] == 0) {
					book_shipped[library[i].book_ids[j]] = 1;
					books_left += 1;
				}
			}
			if (books_left != 0) {
				total_libs += 1;
			}
		}
		fprintf(op, "%d\n", total_libs);

		FILL(book_shipped, 0);
		REP(i, l) {
			int books_left = 0;
			REP(j, library[i].books) {
				if (book_shipped[library[i].book_ids[j]] == 0) {
					books_left += 1;
				}
			}

			if (books_left != 0) {
				fprintf(op, "%d %d\n", library[i].id, books_left);
				// printf("%d ", library[i].ship);
				REP(j, library[i].books) {
					if (book_shipped[library[i].book_ids[j]] == 0) {
						fprintf(op, "%d ", library[i].book_ids[j]);
						book_shipped[library[i].book_ids[j]] = 1;
					}
				}
				fprintf(op, "\n");
			}
		}
		printf("Testcase %s done\n", testcase_id[tc].c_str());
	}

	return 0;
}

// Random Submission