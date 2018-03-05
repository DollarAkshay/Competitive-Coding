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
class LazySegmentTree {
  private:
	int *updates;
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

	void updateSegmentTree(int updateValue, int qlow, int qhigh, int low, int high, int pos) {

		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;

		// Check if this node needs an update
		if (updates[pos] != 0) {
			segTree[pos] += updates[pos];
			if (low != high) {
				updates[leftChild] += updates[pos];
				updates[rightChild] += updates[pos];
			}
			updates[pos] = 0;
		}

		// Total Overlap
		if (qlow <= low && qhigh >= high) {
			segTree[pos] += updateValue;
			if (low != high) {
				updates[leftChild] += updateValue;
				updates[rightChild] += updateValue;
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
			segTree[pos] = max(segTree[leftChild], segTree[rightChild]);
		}
	}

	T recursiveRangeQuerry(int qlow, int qhigh, int low, int high, int pos) {

		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;
		// Check if this node needs an update
		if (updates[pos] != 0) {
			segTree[pos] += updates[pos];
			if (low != high) {
				updates[leftChild] += updates[pos];
				updates[rightChild] += updates[pos];
			}
			updates[pos] = 0;
		}

		if (qlow <= low && qhigh >= high) {
			return segTree[pos];
		}
		else if (qlow > high || qhigh < low) {
			return MIN_VALUE;
		}
		else if (low != high) {
			int mid = (low + high) / 2;
			return max(recursiveRangeQuerry(qlow, qhigh, low, mid, leftChild),
					   recursiveRangeQuerry(qlow, qhigh, mid + 1, high, rightChild));
		}
	}

  public:
	LazySegmentTree(vector<T> const &a) {
		arraySize = a.size();
		int nextPowOf2 = (int)round(pow(2, ceil(log2(arraySize))));
		treeSize = 2 * nextPowOf2 - 1;
		segTree = (T *)calloc(treeSize, sizeof(T));
		updates = (int *)calloc(treeSize, sizeof(int));
		buildTree(a, 0, arraySize - 1, 0);
	}

	T rangeQuerry(int low, int high) {
		return recursiveRangeQuerry(low, high, 0, arraySize - 1, 0);
	}

	T updateTree(int value, int low, int high) {
		return updateSegmentTree(value, low, high, 0, arraySize - 1, 0);
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
	LazySegmentTree<int> st(a);
	st.printTree();
	return 0;
}