/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/MARCH18A/problems/XXOR

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

struct BitCount {
	int f[31];
	BitCount() {
		REP(i, 31) {
			f[i] = 0;
		}
	}

	BitCount(ll int a) {
		REP(i, 31) {
			f[i] = a % 2;
			a /= 2;
		}
	}

	BitCount(int a[31]) {
		REP(i, 31) {
			f[i] = a[i];
		}
	}

	void print(char *name) {
		printf("BitCount of %s : ", name);
		REP(i, 31) {
			printf("%d ", f[i]);
		}
		printf("\n");
	}

	bool operator<(const BitCount &rhs) const {
		REP(i, 31) {
			if (f[i] != rhs.f[i]) {
				return f[i] < rhs.f[i];
			}
		}
		return false;
	}

	BitCount operator+(const BitCount &rhs) const {
		int res[31];
		REP(i, 31) {
			res[i] = f[i] + rhs.f[i];
		}
		return BitCount(res);
	}
};

template <typename T>
class SegmentTree {
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

	// Return Sum of BitCount in range
	T recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {
		if (qlow <= low && qhigh >= high) {
			return segTree[pos];
		}
		else if (qlow > high || qhigh < low) {
			// Bit Count with all 0 values
			return BitCount();
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			// Add both the BitCount
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
};

int main() {

	int n, q;
	vector<BitCount> bc;
	scanf("%d %d", &n, &q);
	REP(i, n) {
		ll int x;
		scanf("%lld", &x);
		bc.pb(BitCount(x));
	}

	SegmentTree<BitCount> st(bc);

	REP(i, q) {
		int l, r;
		scanf("%d %d", &l, &r);
		l--;
		r--;
		int maxBits = r - l + 1;
		BitCount majority = st.rangeQuerry(l, r);

		ll int x = 0;
		REP(i, 31) {
			if (2 * majority.f[i] < maxBits) {
				x += (1LL << i);
			}
		}
		printf("%lld\n", x);
	}

	return 0;
}

//Solved