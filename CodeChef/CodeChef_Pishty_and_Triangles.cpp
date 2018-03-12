/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/MARCH18A/problems/PSHTRG

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

struct Triangle {
	vector<ll int> sides;

	Triangle() {
		sides.clear();
	}

	Triangle(ll int a) {
		sides.clear();
		sides.pb(a);
	}

	Triangle(ll int a, ll int b, ll int c) {
		sides.clear();
		sides.pb(a);
		sides.pb(b);
		sides.pb(c);
	}

	Triangle(vector<ll int> a) {
		sides.clear();
		REP(i, a.size()) {
			sides.pb(a[i]);
		}
	}

	ll int getMaxPerimeter() {
		if (sides.size() < 3) {
			return 0;
		}

		ll int maxPeri = 0, n = sides.size() - 1;
		FOR(i, 0, n) {
			FOR(j, i + 1, n) {
				FOR(k, j + 1, n) {
					if (sides[i] < sides[j] + sides[k] &&
						sides[j] < sides[i] + sides[k] &&
						sides[k] < sides[i] + sides[j] &&
						maxPeri < sides[k] + sides[i] + sides[j]) {
						maxPeri = sides[k] + sides[i] + sides[j];
					}
				}
			}
		}

		return maxPeri;
	}

	struct Triangle &operator+=(const ll int right) {
		this->sides[0] += right;
		return *this;
	}

	bool operator<(const struct Triangle &rhs) const {
		REP(i, min(sides.size(), rhs.sides.size())) {
			if (sides[i] != rhs.sides[i]) {
				return sides[i] < rhs.sides[i];
			}
		}
		return true;
	}
};

ostream &operator<<(ostream &os, const struct Triangle &rhs) {

	REP(i, rhs.sides.size()) {
		os << rhs.sides[i] << " ";
	}
	return os;
}

struct Triangle largestPerimeterTirangle(const struct Triangle t1, const struct Triangle t2) {

	vector<ll int> all_sides;
	REP(i, t1.sides.size()) {
		all_sides.pb(t1.sides[i]);
	}
	REP(i, t2.sides.size()) {
		all_sides.pb(t2.sides[i]);
	}

	if (all_sides.size() < 3) {
		return Triangle(all_sides);
	}

	SORT(all_sides, all_sides.size());
	REV(all_sides, all_sides.size());

	vector<ll int> bestSides;

	FOR(i, 0, all_sides.size() - 1) {
		FOR(j, i + 1, all_sides.size() - 1) {
			FOR(k, j + 1, all_sides.size() - 1) {
				if (all_sides[i] < all_sides[j] + all_sides[k] &&
					all_sides[j] < all_sides[i] + all_sides[k] &&
					all_sides[k] < all_sides[i] + all_sides[j]) {
					bestSides.pb(all_sides[i]);
					bestSides.pb(all_sides[j]);
					bestSides.pb(all_sides[k]);
					return Triangle(bestSides);
				}
			}
		}
		bestSides.pb(all_sides[i]);
	}

	return Triangle(all_sides);
}

template <typename T>
class LazySegmentTree {
  private:
	ll int *updates;
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
			segTree[pos] = largestPerimeterTirangle(segTree[leftChild], segTree[rightChild]);
		}
	}

	void updateSegmentTree(ll int updateValue, int qlow, int qhigh, int low, int high, int pos) {

		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;

		// Check if this node needs an update.. Not needed for this problem

		// Total Overlap
		if (qlow <= low && qhigh >= high) {
			segTree[pos] = updateValue;
			if (low != high) {
				updates[leftChild] = updateValue;
				updates[rightChild] = updateValue;
			}
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
			segTree[pos] = largestPerimeterTirangle(segTree[leftChild], segTree[rightChild]);
		}
	}

	T recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {

		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;

		// Check if this node needs an update...not required for this problem

		if (qlow <= low && qhigh >= high) {
			return segTree[pos];
		}
		else if (qlow > high || qhigh < low) {
			return Triangle();
		}
		else if (low != high) {
			int mid = (low + high) / 2;
			return largestPerimeterTirangle(recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild),
											recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild));
		}
	}

  public:
	LazySegmentTree(vector<T> const &a) {
		arraySize = a.size();
		int nextPowOf2 = (int)round(pow(2, ceil(log2(arraySize))));
		treeSize = 2 * nextPowOf2 - 1;
		segTree = (T *)calloc(treeSize, sizeof(T));
		updates = (ll int *)calloc(treeSize, sizeof(ll int));
		buildTree(a, 0, arraySize - 1, 0);
	}

	T rangeQuerry(int low, int high) {
		return recursiveRangeQuerry(low, high, 0, arraySize - 1, 0);
	}

	void updateTree(int position, ll int value) {
		updateSegmentTree(value, position, position, 0, arraySize - 1, 0);
	}

	void printTree() {
		for (int i = 0; i < treeSize; i++) {
			cout << i << " = " << segTree[i] << "\n";
		}
		cout << endl;
	}
};

int main() {

	int n, q;
	scanf("%d %d", &n, &q);
	vector<struct Triangle> a;
	REP(i, n) {
		int x;
		scanf("%d", &x);
		a.pb(Triangle(x));
	}

	LazySegmentTree<struct Triangle> st(a);

	REP(i, q) {
		int type, l, r;
		scanf("%d %d %d", &type, &l, &r);
		if (type == 1) {
			st.updateTree(l - 1, r);
		}
		else {
			Triangle best = st.rangeQuerry(l - 1, r - 1);
			printf("%lld\n", best.getMaxPerimeter());
		}
	}

	return 0;
}

//Solved