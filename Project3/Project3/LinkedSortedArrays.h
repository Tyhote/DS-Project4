#ifndef LinkedSortedArrays.h
#include <list>
#include <iostream>
#include "SortedArray.h"
template<class DT>
class LinkedSortedArrays {
protected:
	list<SortedArray<DT>> nameIT;
	int ArraySizeFactor;
public:
	LinkedSortedArrays<DT>(int size) {
		ArraySizeFactor = size;
		typename list<SortedArray<DT>>::iterator it = nameIT.begin();
		nameIT.insert(it, SortedArray<DT>(ArraySizeFactor));
	}

	int size() {
		int acc = 0;
		for (list<SortedArray<DT>> it = nameIT.begin(); it != nameIT.end(); acc += *it.size(), it++);
		return acc;
	}

	int find(const DT& lookFor) {
		typename list<SortedArray<DT>>::iterator it = nameIT.begin();
		int i = 0;
		while (it != nameIT.end()) {
			SortedArray<DT> temp = *it;
			if (lookFor < temp.getMinVal()) {
				return -1;
			}
			if (lookFor < temp.getMaxVal()) {
				int subLocation = temp.find(lookFor);
				return subLocation < 0 ? -i * ArraySizeFactor + subLocation : i * ArraySizeFactor + subLocation;
			}
			it++;
			i++;
		}
		return -1;
	}
	int insert(const DT& newOne) {
		int i = find(newOne);
		if (i == -1) {
			SortedArray<DT> firstArr = *nameIT.begin();
			nameIT.insert(nameIT.begin()++, firstArr.split(ArraySizeFactor / 2));
			firstArr.insert(newOne);
			return -i - 1;
		}
		if (i < 0) {
			if (-i - 1 >= size()) {
				nameIT.insert(nameIT.begin(), SortedArray(ArraySizeFactor));
			}
			typename list<SortedArray<DT>>::iterator it = nameIT.begin();
			for (j = 0; j < (-i - 1) / ArraySizeFactor; j++, it++);
			(*it).insert(newOne);
			return -i - 1;
		}
		return i;
	}

	int remove(const DT& X) {
		int i = find(X);
		if (i < 0) {
			return -1;
		}
		typename list<SortedArray<DT>>::iterator it = nameIT.begin();
		for (j = 0; j < i / ArraySizeFactor; j++, it++);
		SortedArray<DT> items = *it;
		items.remove(X);
		return size();
	}
	template <class DT>
	friend ostream& operator<<(ostream& os, const LinkedSortedArrays<DT> output) {
		for (typename list<SortedArray<DT>>::iterator it = output.nameIT.begin(); it != output.nameIT.end(); it++) {
			os << *it << " ";
		}
		os << *it;
		return os;
	}
};
#endif