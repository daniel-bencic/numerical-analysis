#ifndef ITERATIVE_SOLVERS_HH
#define ITERATIVE_SOLVERS_HH

#include "linear-solver.hh"

namespace num {
	template<typename T>
	class JacobiMethod : public LinearSolver<T> {
		
	};

	template<typename T>
	class GaussSeidelMethod : public LinearSolver<T> {
		
	};
}

#endif /* ITERATIVE_SOLVERS_HH */
