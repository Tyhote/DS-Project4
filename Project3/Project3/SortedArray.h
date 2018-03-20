#ifndef SortedArray.h
#include <iostream>
#include <list>
using namespace std;
template <class DT>
class SortedArray {
private:
	DT* itemArray;
	DT* minElement;
	DT* maxElement;
	unsigned long numElements;
	unsigned long arraySize;

	int binarySearch(DT& toFind) {
		int left = 0;
		int right = numElements;
		while (left < right) {
			int mid = left + (right - left) / 2;

			if (itemArray[mid] == lookFor) {
				return mid;
			}

			if (itemArray[mid] < lookFor) {
				left = mid + 1;
			}

			if (itemArray[mid] > lookFor) {
				right = mid - 1;
			}
		}

		return -m - 1;
	}
public:
	template <class DT>
	friend ostream& operator<<(ostream& os, const SortedArray<DT> arr) {
		for (int i = 0; i < arr.numElements - 1; i++) {
			os << arr.itemArray[i] << " ";
		}
		if (arr.numElements != 0) {
			os << arr.itemArray[arr.numElements - 1];
		}
	}

	SortedArray<DT>() {
		SortedArray(10);
	}

	SortedArray<DT>(int size) {
		itemArray[size];
		numElements = 0;
		arraySize = size;
	}

	int size() {
		return numElements;
	}

	//Gets item from DT array at index
	DT* operator[](int index) {
		return itemArray[index];
	}

	DT* getMinVal() {
		return minElement;
	}

	DT* getMaxVal() {
		return maxElement;
	}

	bool operator>(SortedArray<DT> compareTo) {
		for (int i = 0; i < numElements && i < compareTo.size(); i++) {
			if (itemArray[i] <= compareTo[i]) {
				return false;
			}
		}
		if (numElements < comareTo.size()) {
			return false;
		}
		return true;
	}

	bool operator<(SortedArray<DT> compareTo) {
		for (int i = 0; i < numElements && i < compareTo.size(); i++) {
			if (itemArray[i] >= compareTo[i]) {
				return false;
			}
		}
		if (numElements > compareTo.size()) {
			return false;
		}
		return true;
	}

	bool operator==(SortedArray<DT> compareTo) {
		for (int i = 0; i < numElements && i < compareTo.size(); i++) {
			if (itemArray[i] != compareTo[i]) {
				return false;
			}
		}
		if (numElements != compareTo.size()) {
			return false;
		}
		return true;
	}

	void update() {
		minElement = itemArray[0];
		maxElement = itemArray[numElements - 1];
	}

	int find(DT& lookFor) {
		return binarySearch(lookFor);
	}

	int insert(DT& newElement) {
		if (numElements < arraySize) {
			int i = binarySearch(newElement);
			if (i < 0) {
				i = -i - 1;
				for (int j = numElements; j > i; j--) {
					itemArray[j] = itemArray[j - 1];
				}
				itemArray[j] = newElement;
				numElements++;
				update();
			}
			return i;
		}
		return -1;
	}

	int remove(DT& oldElement) {
		if (numElements < arraySize) {
			int i = binarySearch(oldElement);
			if (i < 0) {
				return -1;
			}
			if (i < numElements) {
				for (; i < numElements; i++) {
					itemArray[i] = itemArray[i + 1];
				}
			}
			else {
				itemArray[i] = NULL;
			}
			update();
			return --numElements;
		}
		return -1;
	}

	SortedArray<DT> split(int i) {
		SortedArray<DT> temp = SortedArray<DT>(arraySize);
		for (; i < arraySize; i++) {
			temp.insert(itemArray[i]);
			itemArray[i] = NULL;
			numElements--;
		}
		return temp;
	}

	void join(SortedArray<DT>& P) {
		if ((numElements + P.size) > arraySize) {
			return;
		}
		int i = 0;
		int j = 0;
		int k = 0;
		DT* temp = DT[arraySize];
		
		while (i < numElements && j < P.size()) {
			if (itemArray[i] < P[j]) {
				temp[k] = itemArray[i];
				i++;
			}
			else {
				temp[k] = P[j];
				j++;
			}
			k++;
		}

		while (i < arraySize) {
			temp[k] = itemArray[i];
			i++;
			k++;
		}
		while (j < P.size()) {
			temp[k] = P[j];
			j++;
			k++;
		}
		itemArray = temp;
		update();
	}

};
#endif