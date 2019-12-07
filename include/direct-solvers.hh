#ifndef DIRECT_SOLVERS_HH
#define DIRECT_SOLVERS_HH

#include "linear-solver.hh"
#include "matrix.hh"

namespace num {
	template<typename T>
	class GaussianElimination : public LinearSolver<T> {
	public:
		GaussianElimination() = default;
		GaussianElimination(Matrix<T> a, Matrix<T> b);

	private:
		void compute() override;
	};

	template<typename T>
	GaussianElimination<T>::GaussianElimination(Matrix<T> a, Matrix<T> b)
		: LinearSolver<T>(a, b)
	{
		compute();
	}

	template<typename T>
	void GaussianElimination<T>::compute()
	{
		Matrix<T> aug = concat_matrices(this->_a, this->_b);
		for(int i = 0; i < aug.cols() - 1; i++) {
                        for(int j = i + 1; j < aug.rows(); j++) {
                                double mult = -(aug(j, i) / aug(i, i));
                                for(int k = i; k < aug.cols(); k++) {
                                        aug(j, k) = aug(j, k) + aug(i, k) * mult;
                                }
                        }
                }
    
		this->_x = this->back_substitution(aug);
	}

	template<typename T>
	class LUDecomposition : public LinearSolver<T> {
	public:
		LUDecomposition() = default;
		LUDecomposition(Matrix<T> a, Matrix<T> b);
		Matrix<T> l() const;
		Matrix<T> r() const;

	private:
		void compute() override;

		Matrix<T> _l, _r;
	};

	template<typename T>
	LUDecomposition<T>::LUDecomposition(Matrix<T> a, Matrix<T> b)
		: LinearSolver<T>(a, b)
	{
		compute();
	}

	template<typename T>
	Matrix<T> LUDecomposition<T>::l() const
	{
		return _l;
	}

	template<typename T>
	Matrix<T> LUDecomposition<T>::r() const
	{
		return _r;
	}

	template<typename T>
	void LUDecomposition<T>::compute()
	{
		_l = create_identity_matrix<T>(this->_a.rows(), this->_a.cols());
		_r = this->_a;
                for(int i = 0; i < _r.cols() - 1; i++) {
                        for(int j = i + 1; j < _r.rows(); j++) {
                                _l(j, i) = _r(j,i) / _r(i, i);

                                for(int k = i; k < _r.cols(); k++) {
                                        _r(j, k) = _r(j, k) - _r(i, k) * _l(j, i);
                                }
                        }
                }

		Matrix<T> res_y = this->forward_substitution(concat_matrices(_l, this->_b));
		this->_x = this->back_substitution(concat_matrices(_r, res_y));
	}
}

#endif /* DIRECT_SOLVERS_HH */
