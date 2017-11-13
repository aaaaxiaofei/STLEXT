#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <thread> 
#include <mutex>
#include <condition_variable>
using namespace std;

// Lock
// mutex mtx;
// mtx.lock();
// mtx.unlock();
// std::lock_guard<std::mutex> lock(mtx);

template <typename T>
class Vector {
private:
	std::unique_ptr<T[]> arr;
	size_t _size;
	size_t _capacity;
	size_t _increase_size;

public:
	Vector();
	// copy constructor
	Vector(Vector<T>& v);
	// fill constructor
	Vector(size_t n, const T& num);
	// move constructor
	Vector(Vector<T>&& v);
	// deconstructor
	~Vector();

	// size
	size_t size();
	bool empty();
	void resize(size_t new_size);

	// Functions
	void push_back(T x);
	void pop_back();
	T& back();

	// Iterator
	typedef T* iterator;
	typedef const T* const const_iterator;
	iterator begin();
	iterator end();

	// operator
	T& operator[](int index);

};

// default constructor
template <typename T>
Vector<T>::Vector() {
	_size = 0;
	_capacity = 0;
	_increase_size = 1;
	arr = move(unique_ptr<T[]>(new T[_capacity]));
}

// fill constructor
template <typename T>
Vector<T>::Vector(size_t n, const T& num) {
	_size = n;
	_capacity = n;
	_increase_size = _capacity/2;

	arr = move(unique_ptr<T[]>(new T[_capacity]));

	for (size_t i = 0; i < _size; i++) {
		arr[i] = num;
	}
}

// Copy constructor
template <typename T>
Vector<T>::Vector(Vector<T>& v) {
	cout << "Copy constructor" << endl;
	size_t n = v.size();
	_size = n;
	_capacity = n;
	_increase_size = _capacity;

	arr = move(unique_ptr<T[]>(new T[_capacity]));

	for (size_t i = 0; i < n; i++) {
		arr[i] = v[i];
	}
}

// Move constructor
template <typename T>
Vector<T>::Vector(Vector<T>&& v) {
	cout << "Move constructor" << endl;
	size_t n = v.size();
	_size = n;
	_capacity = n;
	_increase_size = _capacity;
	arr = move(v);
}

// Deconstructor
template <typename T>
Vector<T>::~Vector() {

}

template <typename T>
void Vector<T>::push_back(T x) {

	if (_size == _capacity) {
		cout << "size is " << _size << ", resize to " << _capacity + _increase_size << endl;
		_capacity += _increase_size;
		_increase_size = _capacity;
		resize(_capacity);

	}

	arr[_size++] = x;
}

template <typename T>
void Vector<T>::pop_back() {
	if (_size > 0) {
		_size--;
	}
}

template <typename T>
T& Vector<T>::back() {
	if (_size) {
		return arr[_size-1];
	}
}

template <typename T>
size_t Vector<T>::size() {
	return _size;
}

template <typename T>
bool Vector<T>::empty() {
	return _size == 0;
}

template <typename T>
void Vector<T>::resize(size_t new_size) {
	_capacity = new_size;
	_increase_size = _capacity;

	unique_ptr<T[]> new_arr = unique_ptr<T[]>(new T[_capacity]);

	for (size_t i = 0; i < _size; i++) {
		new_arr[i] = arr[i];
	}

	arr = move(new_arr);

}

// Iterator
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
	return arr.get();
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
	return arr.get() + _size;
}

template <typename T>
T& Vector<T>::operator[](int index) {
	return arr[index];
}







#endif