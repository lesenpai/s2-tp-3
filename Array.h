#pragma once
#include <memory>
#include "Circle.h"
#include "utils.h"
using namespace std;

// указатель на дин. массив (структур) и его длина
class Array {
private:
	int _length; // длина массива
public:
	shared_ptr<Circle> p; // ук. на массив структур

	Array() {
		this->p = NULL;
		this->_length = 0;
	}

	Array(shared_ptr<Circle>& ptr, int len) {
		this->p = ptr;
		this->_length = len;

	}

	void clear() {
		this->p = NULL;
		this->_length = 0;
	}

	void push(const Circle& c) {
		this->_length++;
		shared_ptr<Circle> p = (shared_ptr<Circle>)(new Circle[this->_length]());
		for (int i = 0; i < this->_length - 1; i++) {
			p.get()[i] = this->p.get()[i];
		}
		p.get()[this->_length - 1] = c;
		this->p = p;
	}

	Circle& operator[](const int i) {
		return p.get()[i];
	}

	int getLength() {
		return _length;
	}

	void swapCircles(Circle& cir1, Circle& cir2) {
		Circle buff = cir1;
		cir1 = cir2;
		cir2 = buff;
	}
};