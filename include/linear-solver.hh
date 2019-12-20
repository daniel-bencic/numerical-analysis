#ifndef LINEAR_SOLVER_HH
#define LINEAR_SOLVER_HH

#include <vector>
#include "solver.hh"
#include "matrix.hh"

namespace num {
namespace linalg {
	template<typename T>
	class LinearSolver : public Solver {
	public:
		LinearSolver() = default;
		LinearSolver(num::linalg::Matrix<T> a, num::linalg::Matrix<T> b);
		num::linalg::Matrix<T> x() const;

	protected:	
		num::linalg::Matrix<T> _a, _b, _x;
	};

	template<typename T>
	LinearSolver<T>::LinearSolver(num::linalg::Matrix<T> a, num::linalg::Matrix<T> b)
		: _a(a), _b(b)
	{ }

	template<typename T>
	num::linalg::Matrix<T> LinearSolver<T>::x() const
	{
		return _x;
	}
}
}
	
#endif /* LINEAR_SOLVER_HH */
