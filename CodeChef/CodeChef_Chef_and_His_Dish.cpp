/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codechef.com/JUNE19A/problems/COOLCHEF

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
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>
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
#define gc getchar_unlocked

ll int factMod[300000];
high_resolution_clock::time_point timer;

class SegmentTree {
  private:
	vector<unordered_map<int, int>> segTree;
	unordered_map<int, int> freqCount;
	int treeSize, arraySize;

	void addChildrenTo(unordered_map<int, int> &parent, unordered_map<int, int> &child) {

		for (auto i = child.begin(); i != child.end(); i++) {
			if (parent.find(i->first) != parent.end()) {
				parent[i->first] += i->second;
			}
			else {
				parent[i->first] = i->second;
			}
		}
	}

	void buildTree(vector<int> const &a, int low, int high, int pos) {
		if (low == high) {
			if (freqCount[a[low]] > 1) {
				segTree[pos].insert(make_pair(a[low], 1));
			}
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			buildTree(a, low, mid, leftChild);
			buildTree(a, mid + 1, high, rightChild);
			addChildrenTo(segTree[pos], segTree[leftChild]);
			addChildrenTo(segTree[pos], segTree[rightChild]);
		}
	}

	void recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos, unordered_map<int, int> &res) {
		if (qlow <= low && qhigh >= high) {
			addChildrenTo(res, segTree[pos]);
		}
		else if (qlow > high || qhigh < low) {
			return;
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild, res);
			recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild, res);
		}
	}

  public:
	SegmentTree(vector<int> const &a) {
		arraySize = a.size();
		int nextPowOf2 = (int)round(pow(2, ceil(log2(arraySize))));

		treeSize = 2 * nextPowOf2 - 1;
		REP(i, treeSize) {
			segTree.push_back({});
		}

		REP(i, a.size()) {
			if (freqCount.find(a[i]) != freqCount.end()) {
				freqCount[a[i]] += 1;
			}
			else {
				freqCount[a[i]] = 1;
			}
		}
		buildTree(a, 0, arraySize - 1, 0);
	}

	void rangeQuerry(int low, int high, unordered_map<int, int> &res) {
		recursiveRangeQuerry(low, high, 0, arraySize - 1, 0, res);
	}
};

void calculateFactMod() {
	factMod[0] = 1;
	FOR(i, 1, 300000 - 1) {
		factMod[i] = (factMod[i - 1] * i) % MOD;
	}
}

ll int invert_mod(ll int a, ll int p) {
	ll int ne = 1, old = 0, q = p, r, h;
	ll int pos = 0;
	while (a > 0) {
		r = q % a;
		q = q / a;
		h = q * ne + old;
		old = ne;
		ne = h;
		q = a;
		a = r;
		pos = !pos;
	}
	return pos ? old : (p - old);
}

int main() {

	calculateFactMod();

	int n, q;
	scanf("%d %d", &n, &q);

	vector<int> a;
	REP(i, n) {
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}

	SegmentTree st(a);

	ll int prevRes = 0;
	REP(i, q) {
		int l1, l2, r1, r2;
		scanf("%d %d %d %d", &l1, &l2, &r1, &r2);
		int l = (l1 * prevRes + l2) % n;
		int r = (r1 * prevRes + r2) % n;
		if (l > r) {
			int temp = l;
			l = r;
			r = temp;
		}

		unordered_map<int, int> dupCount;
		st.rangeQuerry(l, r, dupCount);
		ll int res = factMod[r - l + 1];
		for (auto i = dupCount.begin(); i != dupCount.end(); i++) {
			res = (res * invert_mod(factMod[i->second], MOD)) % MOD;
		}
		printf("%lld\n", res);
		prevRes = res;
	}
	return 0;
}

//Solved