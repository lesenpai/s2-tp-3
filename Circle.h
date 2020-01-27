#pragma once
#include <exception>
#include "utils.h"

/*
	describes a circle
*/
struct Circle {
private:
	double _r;
public:
	double x, y;
	bool done;

	Circle() {
		this->x = 0;
		this->y = 0;
		this->_r = 1;
		this->done = false;
	}

	Circle(double x, double y, double r) {
		this->x = x;
		this->y = y;
		this->_r = setR(r);
		this->done = true;
	}

	double setR(double r) {
		if (r <= 0) throw std::exception("Non positive radius");
		else {
			this->_r = r;
			return r;
		}
	}

	double getR() {
		return this->_r;
	}

	bool has(std::string& key) {
		switch (sci(key.c_str())) {
			case sci("x"): return true;
			case sci("y"): return true;
			case sci("r"): return true;
			default: return false;
		}
	}

	double& operator[](std::string& key) {
		if (this->has(key)) {
			switch (sci(key.c_str())) {
				case sci("x"): return this->x;
				case sci("y"): return this->y;
				case sci("r"): return this->_r;
			}
		}
		throw std::exception("no such property");
	}
};
