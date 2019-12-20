#include <cmath>
#include <iostream>
#include "newton-raphson.hh"

namespace num {
namespace root {
	NewtonRaphson::NewtonRaphson()
		: _z(0.0), _fn(nullptr), _d_fn(nullptr)
	{ }

	NewtonRaphson::NewtonRaphson(double (*func)(double), double(*d_func)(double), double start, double tolerance, int max_iterations)
		: IterativeMethod<double>(tolerance, max_iterations), _z(start), _fn(func), _d_fn(d_func)
	{
		compute();
	}

	double NewtonRaphson::zero() const
	{
		return _z;
	}

	void NewtonRaphson::compute()
	{
		double tmp = 0.0;
		int i = 0;
		do {
			tmp = _z;
			_z = _z - (_fn(_z) / _d_fn(_z));
			
#ifndef N_DEBUG
			std::cout << "i: " << i << " x: " << tmp << " err: " << std::abs(tmp - _z) << "\n";
#endif
		}
		while (++i < this->_its && std::abs(tmp - _z) > this->_tol);

#ifndef N_DEBUG
		std::cout << "iterations: " << i << std::endl;
#endif
	}
}	
}

