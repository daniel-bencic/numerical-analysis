#ifndef NEWTON_RAPHSON_HH
#define NEWTON_RAPHSON_HH

#include "solver.hh"
#include "iterative-method.hh"

namespace num {
	class NewtonRaphson : public Solver, public IterativeMethod<double> {
	public:
		NewtonRaphson();
		NewtonRaphson(double (*func)(double), double(*d_func)(double), double start, double tolerance, int max_iterations);
		double zero() const;

	private:
		void compute() override;
		
		double _z;
		double (*_fn)(double);
		double (*_d_fn)(double);
	};
}

#endif /* NEWTON_RAPHSON_HH */
