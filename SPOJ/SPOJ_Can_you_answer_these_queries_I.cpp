/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//http://www.spoj.com/problems/GSS1/

#include <algorithm>
#include <assert.h>
#include <bitset>
#include <ctype.h>
#include <deque>
#include <functional>
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
#define MS0(x) memset(x, 0, sizeof(x))
#define MS1(x) memset(x, 1, sizeof(x))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int a[1000000];

template <typename T>
class SegmentTree {
  private:
	T *segTree;
	const T MIN_VALUE = numeric_limits<T>::lowest();
	int treeSize, arraySize;

	void buildTree(vector<T> const &a, int low, int high, int pos) {
		if (low == high) {
			segTree[pos] = a[low] > 0 ? a[low] : 0;
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			buildTree(a, low, mid, leftChild);
			buildTree(a, mid + 1, high, rightChild);
			segTree[pos] = segTree[leftChild] + segTree[rightChild];
		}
	}

	T recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {
		if (qlow <= low && qhigh >= high) {
			return segTree[pos] > 0 ? segTree[pos] : 0;
		}
		else if (qlow > high || qhigh < low) {
			return 0;
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			return recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild) + recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild);
		}
	}

  public:
	SegmentTree(vector<T> const &a) {
		arraySize = a.size();
		int nextPowOf2 = (int)round(pow(2, ceil(log2(arraySize))));
		treeSize = 2 * nextPowOf2 - 1;
		segTree = (T *)calloc(treeSize, sizeof(T));
		buildTree(a, 0, arraySize - 1, 0);
	}

	T rangeQuerry(int low, int high) {
		return recursiveRangeQuerry(low, high, 0, arraySize - 1, 0);
	}

	void printTree() {
		for (int i = 0; i < treeSize; i++) {
			cout << segTree[i] << " ";
		}
		cout << endl;
	}
};

int main() {

	int n, q;
	scanf("%d", &n);
	REP(i, n) {
		scanf("%d", &a[i]);
	}

	SegmentTree<int> st(vector<int>(a, a + n));

	scanf("%d", &q);
	REP(i, q) {
		int l, r;
		scanf("%d %d", &l, &r);
		assert(l <= r);
		printf("%d\n", st.rangeQuerry(l - 1, r - 1));
	}
	return 0;
}

//