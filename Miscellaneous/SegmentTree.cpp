#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

// Max Range Querry Segment Tree
template <typename T>
class SegmentTree {
  private:
	T *segTree;
	const T MIN_VALUE = numeric_limits<T>::lowest();
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
			segTree[pos] = max(segTree[leftChild], segTree[rightChild]);
		}
	}

	T recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {
		if (qlow <= low && qhigh >= high) {
			return segTree[pos];
		}
		else if (qlow > high || qhigh < low) {
			return MIN_VALUE;
		}
		else {
			int mid = (low + high) / 2;
			int leftChild = 2 * pos + 1;
			int rightChild = 2 * pos + 2;
			return max(recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild),
					   recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild));
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

	vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
	SegmentTree<int> st(a);
	st.printTree();
	return 0;
}