#ifndef LINEAR_SOLVER_HH
#define LINEAR_SOLVER_HH

#include <vector>
#include "solver.hh"
#include "matrix.hh"

namespace num {
	template<typename T>
	class LinearSolver : public Solver {
	public:
		LinearSolver() = default;
		LinearSolver(Matrix<T> a, std::vector<T> x);
		std::vector<T> solution() const;

	protected:
		std::vector<T> _x, _solution;
		Matrix<double> _a;
	};

	template<typename T>
	LinearSolver<T>::LinearSolver(Matrix<T> a, std::vector<T> x)
		: _a{ a },
		  _x{ x }
	{ }

	template<typename T>
	std::vector<T> LinearSolver<T>::solution() const
	{
		return _solution;
	}
}

#endif /* LINEAR_SOLVER_HH */
