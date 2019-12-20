#ifndef NEWTON_RAPHSON_HH
#define NEWTON_RAPHSON_HH

#include <iostream>
#include "solver.hh"
#include "iterative-method.hh"

namespace num {
namespace root {
	template<typename T>
	class NewtonRaphson : public Solver, public IterativeMethod<T> {
	public:
		NewtonRaphson();
		NewtonRaphson(T (*func)(T), T(*d_func)(T), T start, T tolerance, int max_iterations);
		double zero() const;

	private:
		void compute() override;
		
		T _z;
		T (*_fn)(T);
		T (*_d_fn)(T);
	};

	template<typename T>
	NewtonRaphson<T>::NewtonRaphson()
		: _z(static_cast<T>(0)), _fn(nullptr), _d_fn(nullptr)
	{ }

	template<typename T>
	NewtonRaphson<T>::NewtonRaphson(T (*func)(T), T(*d_func)(T), T start, T tolerance, int max_iterations)
		: IterativeMethod<T>(tolerance, max_iterations), _z(start), _fn(func), _d_fn(d_func)
	{
		compute();
	}

	template<typename T>
	double NewtonRaphson<T>::zero() const
	{
		return _z;
	}

	template<typename T>
	void NewtonRaphson<T>::compute()
	{
		T tmp = static_cast<T>(0);
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

#endif /* NEWTON_RAPHSON_HH */
