/*~~~~~~~~~~~~~~~~~~*
 *                  *
 *  $DollarAkshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.hackerearth.com/challenge/competitive/february-circuits-18/algorithm/simple-sum-3-f1585a25/

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <limits>
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

// Max Range Querry with Index Segment Tree
// First element in pair is the index
// Second element in pair is the value
template <typename T>
class SegmentTree {
  private:
	pair<int, T> *segTree;
	const T MIN_VALUE = numeric_limits<T>::lowest();
	int treeSize, arraySize;

	void buildTree(vector<T> const &a, int low, int high, int pos) {
		if (low == high) {
			segTree[pos] = make_pair(low, a[low]);
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			buildTree(a, low, mid, leftChild);
			buildTree(a, mid + 1, high, rightChild);

			if (segTree[leftChild].second > segTree[rightChild].second) {
				segTree[pos] = segTree[leftChild];
			}
			else {
				segTree[pos] = segTree[rightChild];
			}
		}
	}

	pair<int, T> recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {
		if (qlow <= low && qhigh >= high) {
			return segTree[pos];
		}
		else if (qlow > high || qhigh < low) {
			return make_pair(-1, MIN_VALUE);
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			pair<int, T> leftRes = recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild);
			pair<int, T> rightRes = recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild);
			if (leftRes.second > rightRes.second) {
				return leftRes;
			}
			else {
				return rightRes;
			}
		}
	}

  public:
	SegmentTree() {
	}

	SegmentTree(vector<T> const &a) {
		arraySize = a.size();
		int nextPowOf2 = (int)round(pow(2, ceil(log2(arraySize))));
		treeSize = 2 * nextPowOf2 - 1;
		segTree = (pair<int, T> *)calloc(treeSize, sizeof(pair<int, T>));
		buildTree(a, 0, arraySize - 1, 0);
	}

	pair<int, T> rangeQuerry(int low, int high) {
		return recursiveRangeQuerry(low, high, 0, arraySize - 1, 0);
	}

	void printTree() {
		for (int i = 0; i < treeSize; i++) {
			cout << "( " << segTree[i].first << ", " << segTree[i].second << ") | ";
		}
		cout << endl;
	}
};

// 14 = ceil(log2(10^4))
ll int cumSum[100001];
ll int bitsCumSum[100001][14];

ll int Bruteforce(vector<int> &a) {
	ll int res = 0;

	REP(i, a.size()) {
		int max_num = -1;
		FOR(j, i, a.size() - 1) {
			max_num = max(max_num, a[j]);
			int b_or = a[i] | a[j];
			res += max_num * b_or;
		}
	}
	return res;
}

ll int findSum(SegmentTree<int> &st, int low, int high) {

	if (low > high) {
		return 0;
	}

	pair<int, int> maxElement = st.rangeQuerry(low, high);
	int pivot = maxElement.first;
	ll int leftCount = (pivot - low + 1);
	ll int rightCount = (high - pivot + 1);
	ll int sum = rightCount * (cumSum[pivot + 1] - cumSum[low]);
	REP(i, 14) {
		sum += (1 << i) * (bitsCumSum[high + 1][i] - bitsCumSum[pivot][i]) * (leftCount - (bitsCumSum[pivot + 1][i] - bitsCumSum[low][i]));
	}

	return maxElement.second * sum + findSum(st, low, pivot - 1) + findSum(st, pivot + 1, high);
}

int main() {
	int n;
	vector<int> a;
	scanf("%d", &n);
	REP(i, n) {
		int x;
		scanf("%d", &x);
		cumSum[i + 1] = cumSum[i] + x;
		a.pb(x);
		REP(j, 14) {
			bitsCumSum[i + 1][j] = bitsCumSum[i][j] + x % 2;
			x /= 2;
		}
	}

	SegmentTree<int> st(a);
	printf("%lld\n", findSum(st, 0, n - 1));

	return 0;
}

//Solved