#include "newton-raphson.hh"

namespace num {
	NewtonRaphson::NewtonRaphson()
		: _z(0.0), _fn(nullptr), _d_fn(nullptr)
	{ }

	NewtonRaphson::NewtonRaphson(double (*func)(double), double(*d_func)(double), double tolerance, int max_iterations)
		: IterativeMethod<double>(tolerance, max_iterations), _fn(func), _d_fn(d_func)
	{
		compute();
	}

	double NewtonRaphson::zero() const
	{
		return _z;
	}

	void NewtonRaphson::compute()
	{
		
	}
}
