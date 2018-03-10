/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//

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

struct TreeNode {
	int even, odd;

	TreeNode() {
		even = 0;
		odd = 0;
	}

	TreeNode(int x) {
		if (x % 2 == 0) {
			even = 1;
			odd = 0;
		}
		else {
			odd = 1;
			even = 0;
		}
	}

	TreeNode(int e, int o) {
		even = e;
		odd = o;
	}

	struct TreeNode operator+(TreeNode const &rhs) {
		return TreeNode(even + rhs.even, odd + rhs.odd);
	}

	struct TreeNode operator<(TreeNode const &rhs) {
		return (even < rhs.even) || (even == rhs.even && odd < rhs.odd);
	}
};

// Max Range Querry Segment Tree
template <typename T>
class LazySegmentTree {
  private:
	T *segTree;
	int treeSize, arraySize;

	void buildTree(vector<T> const &a, int low, int high, int pos) {
		if (low == high) {
			segTree[pos] = a[low];
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

	void updateSegmentTree(T updateValue, int qlow, int qhigh, int low, int high, int pos) {

		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;

		// Total Overlap
		if (qlow <= low && qhigh >= high) {
			segTree[pos] = updateValue;
		}
		// No Overlap
		else if (qlow > high || qhigh < low) {
			return;
		}
		//Partial Overlap
		else if (low != high) {
			int mid = (low + high) / 2;
			updateSegmentTree(updateValue, qlow, qhigh, low, mid, leftChild);
			updateSegmentTree(updateValue, qlow, qhigh, mid + 1, high, rightChild);
			segTree[pos] = segTree[leftChild] + segTree[rightChild];
		}
	}

	T recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {

		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;

		if (qlow <= low && qhigh >= high) {
			return segTree[pos];
		}
		else if (qlow > high || qhigh < low) {
			return TreeNode();
		}
		else if (low != high) {
			int mid = (low + high) / 2;
			return recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild) + recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild);
		}
	}

  public:
	LazySegmentTree(vector<T> const &a) {
		arraySize = a.size();
		int nextPowOf2 = (int)round(pow(2, ceil(log2(arraySize))));
		treeSize = 2 * nextPowOf2 - 1;
		segTree = (T *)calloc(treeSize, sizeof(T));
		buildTree(a, 0, arraySize - 1, 0);
	}

	T rangeQuerry(int low, int high) {
		return recursiveRangeQuerry(low, high, 0, arraySize - 1, 0);
	}

	void updateTree(T value, int low, int high) {
		updateSegmentTree(value, low, high, 0, arraySize - 1, 0);
	}

	void printTree() {
		for (int i = 0; i < treeSize; i++) {
			cout << segTree[i] << " ";
		}
		cout << endl;
	}
};

int main() {

	vector<struct TreeNode> a;
	int n;
	scanf("%d", &n);
	REP(i, n) {
		int x;
		scanf("%d", &x);
		a.pb(TreeNode(x));
	}

	LazySegmentTree<struct TreeNode> st(a);

	int q;
	scanf("%d", &q);
	REP(qr, q) {
		int type;
		scanf("%d", &type);
		if (type == 0) {
			int i, x;
			scanf("%d %d", &i, &x);
			i--;
			st.updateTree(TreeNode(x), i, i);
		}
		else {
			int l, r;
			scanf("%d %d", &l, &r);
			TreeNode res = st.rangeQuerry(l - 1, r - 1);
			printf("%d\n", type == 1 ? res.even : res.odd);
		}
	}
	return 0;
}

//Solved