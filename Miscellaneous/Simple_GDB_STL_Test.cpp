/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//

#include <functional>
#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define pb(x) push_back(x)

int main() {

	vector<int> a;
	REP(i, 10) {
		a.pb(i);
	}

	priority_queue<int> q;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2}) {
		q.push(n);
	}

	printf("Done");
	return 0;
}

//