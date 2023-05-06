#pragma once
#include <iostream>

template<typename ElemType>
class IteratorVector;

template<typename ElemType>
class MyVector {
private:
	ElemType* elems;
	int len;
	int cap;

public:
	/// <summary>
	/// The constructor of the class
	/// </summary>
	MyVector() {
		elems = new ElemType[2];
		len = 0;
		cap = 2;
	}
	
	/// <summary>
	/// The destructor of the class
	/// </summary>
	~MyVector() {
		delete[] elems;
	}

	/// <summary>
	/// The copy constructor of the class
	/// </summary>
	/// <param name="v"></param>
	MyVector(const MyVector& v) {
		this->cap = v.cap;
		this->len = v.len;
		this->elems = new ElemType[v.cap];

		for (int i = 0; i < v.len; i++) {
			this->elems[i] = v.elems[i];
		}
	}

	/// <summary>
	/// The move constructor of the class
	/// </summary>
	/// <param name="ot"> vector&& </param>
	MyVector(MyVector&& ot) {
		elems = ot.elems;
		len = ot.len;
		cap = ot.cap;

		ot.elems = nullptr;
		ot.len = 0;
		ot.cap = 0;
	}

	/// <summary>
	/// Move assignment
	/// </summary>
	/// <param name="ot"> vector&& </param>
	/// <returns> vector& </returns>
	MyVector& operator=(MyVector&& ot) {
		if (this == &ot) {
			return *this;
		}
		delete[] elems;
		elems = ot.elems;
		len = ot.len;
		cap = ot.cap;

		ot.elems = nullptr;
		ot.len = 0;
		ot.cap = 0;
		return *this;
	}

	/// <summary>
	/// Overwrites the elements of this vector with the elements of ot // copy assignment
	/// </summary>
	/// <param name="ot"> vector </param>
	/// <returns> vector </returns>
	MyVector& operator=(const MyVector& ot) {
		if (this == &ot) {
			return *this;
		}
		delete[] elems;
		elems = new ElemType[ot.cap];

		for (int i = 0; i < ot.len; i++) {
			elems[i] = ot.elems[i];
		}

		this->len = ot.len;
		this->cap = ot.cap;
		return *this;
	}

	/// <summary>
	/// Returns the element fromm the given position
	/// </summary>
	/// <param name="pos"> int </param>
	/// <returns> ElemType </returns>
	ElemType& operator[](const int pos) const {
		return elems[pos];
	}

	/// <summary>
	/// Returns the size of the vector
	/// </summary>
	/// <returns> int </returns>
	int size() const {
		return len;
	}

	/// <summary>
	/// Resizes the vector, so it can store more elements
	/// </summary>
	void resize() {
		ElemType* newElem = new ElemType[2 * cap];

		for (int i = 0; i < len; i++) {
			newElem[i] = elems[i];
		}

		delete[] elems;

		elems = newElem;
		cap = cap * 2;
	}

	/// <summary>
	/// Adds a new element on the last position. If the vector is full, the function also resizes it
	/// </summary>
	/// <param name="e"> ElemType </param>
	void push_back(const ElemType& e) {
		if (len == cap) {
			resize();
		}

		elems[len] = e;
		len++;
	}

	/// <summary>
	/// Removes the last element of the vector
	/// </summary>
	void pop_back() {
		len--;
	}

	friend class IteratorVector<ElemType>;

	/// <summary>
	/// Returns the iterator pointing to the first position of the vector
	/// </summary>
	IteratorVector<ElemType> begin() {
		return IteratorVector<ElemType>(*this);
	}

	/// <summary>
	/// Returns the iterator pointing to the position after the last one of the vector
	/// </summary>
	IteratorVector<ElemType> end() {
		return IteratorVector<ElemType>(*this, len);
	}
};

template<typename ElemType>
class IteratorVector {
private:
	MyVector<ElemType> v;
	int pos = 0;
public:
	/// <summary>
	/// The constructor of the class
	/// </summary>
	IteratorVector(const MyVector<ElemType>& v) {
		this->v = v;
	}

	/// <summary>
	/// The other construcotr of the class, providing the position
	/// </summary>
	/// <param name="v"> vector& </param>
	/// <param name="pos"> int </param>
	IteratorVector(const MyVector<ElemType>& v, int pos) {
		this->v = v;
		this->pos = pos;
	}
	
	/// <summary>
	/// Checks if the iterator is valid
	/// </summary>
	/// <returns> true, if the iterator is valid
	///           false, otherwise </returns>
	bool valid() const {
		return pos < v.len;
	}

	/// <summary>
	/// Returns the element of the vector that the iterator is pointing to
	/// </summary>
	/// <returns> ElemType& </returns>
	ElemType& element() const {
		return v.elems[pos];
	}

	/// <summary>
	/// Goes to the next position
	/// </summary>
	void next() {
		pos++;
	}

	ElemType& operator*() {
		return element();
	}

	IteratorVector& operator++() {
		next();
		return *this;
	}

	bool operator==(const IteratorVector& ot) {
		return pos == ot.pos;
	}

	bool operator!=(const IteratorVector& ot) {
		return !(*this == ot);
	}
};