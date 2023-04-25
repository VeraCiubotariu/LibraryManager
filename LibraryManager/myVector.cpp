#include "myVector.h"
#define NULL 0

template<typename ElemType>
vector<ElemType>::vector() {
	elems = new ElemType[10];
	len = 0;
	cap = 10;
}

template<typename ElemType>
vector<ElemType>::~vector() {
	delete[] elems;
}

template<typename ElemType>
int vector<ElemType>::size() const {
	return len;
}

template<typename ElemType>
void vector<ElemType>::resize() {
	ElemType* newElem = new ElemType[2 * cap];
	
	for (int i = 0; i < len; i++) {
		newElem[i] = elems[i];
	}

	delete[] elems;
	
	elems = newElem;
	cap = cap * 2;
}

template<typename ElemType>
void vector<ElemType>::push_back(ElemType e) {
	if (len == cap) {
		resize();
	}

	elems[len] = e;
	len++;
}

template<typename ElemType>
void vector<ElemType>::pop_back() {
	elems[len] = NULL;
	len--;
}