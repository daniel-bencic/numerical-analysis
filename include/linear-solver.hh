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
		LinearSolver(Matrix<T> a, Matrix<T> b);
		Matrix<T> x() const;

	protected:
		Matrix<T> back_substitution(const Matrix<T>& aug) const;
		Matrix<T> forward_substitution(const Matrix<T>& aug) const;
		
		Matrix<T> _a, _b, _x;
	};

	template<typename T>
	LinearSolver<T>::LinearSolver(Matrix<T> a, Matrix<T> b)
	{
		_a = a;
		_b = b;
	}

	template<typename T>
	Matrix<T> LinearSolver<T>::x() const
	{
		return _x;
	}

	template<typename T>
	Matrix<T> LinearSolver<T>::back_substitution(const Matrix<T>& aug) const
	{
		std::vector<double> res;
		res.resize(aug.rows());
		double r;
		for(std::size_t i = aug.rows() - 1; i > -1; i--) {
			r = aug(i, aug.cols() - 1);
			for(std::size_t j = i + 1; j < aug.cols() - 1; j++) {
				r -= aug(i, j) * res[j];
			}

			res[i] = r / aug(i, i);
		}		
				
		Matrix<T> m_res;
		m_res.append_col(res);

		return m_res;
	}

	template<typename T>
	Matrix<T> LinearSolver<T>::forward_substitution(const Matrix<T>& aug) const
	{
		std::vector<double> res;
                res.resize(aug.rows());
                double r;
                for(std::size_t i = 0; i < aug.rows(); i++) {
                	r = aug(i, aug.cols() - 1);
                        for(std::size_t j = i - 1; j > -1; j--) {
                        	r -= aug(i, j) * res[j];
                        }
                        
			res[i] = r / aug(i, i);
                }
                
		Matrix<T> m_res;
		m_res.append_col(res);

		return m_res;
	}
}

#endif /* LINEAR_SOLVER_HH */
