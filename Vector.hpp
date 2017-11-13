#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
using namespace std;

template <typename T>
class Vector {
private:
	std::unique_ptr<T[]> arr;
	size_t size;
	size_t capacity;

public:
	Vector();
	Vector(const Vector<T>& v);


	size_t size();
	void resize();


};
#endif