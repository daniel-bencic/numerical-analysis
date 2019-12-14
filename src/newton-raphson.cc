#include <cmath>
#include "newton-raphson.hh"

namespace num {
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
		}
		while (++i < this->_its && std::abs(tmp - _z) > this->_tol);
	}
}
