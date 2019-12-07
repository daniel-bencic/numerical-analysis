#ifndef ITERATIVE_SOLVERS_HH
#define ITERATIVE_SOLVERS_HH

#include "linear-solver.hh"

namespace num {
	template<typename T>
	class IterativeSolver : public LinearSolver<T> {
	public:
		IterativeSolver();
		IterativeSolver(Matrix<T> a, Matrix<T> b, T tolerance, int max_iterations);
		
	protected:
		T _tol;
		int _its;
	};

	template<typename T>
	IterativeSolver<T>::IterativeSolver()
	{
		_tol = static_cast<T>(0);
		_its = 0;
	}

	template<typename T>
	IterativeSolver<T>::IterativeSolver(Matrix<T>a, Matrix<T>b, T tolerance, int max_iterations)
		: LinearSolver<T>(a, b)
	{
		_tol = tolerance;
		_its = max_iterations;
	}
	
	template<typename T>
	class JacobiMethod : public IterativeSolver<T> {
	public:
		JacobiMethod() = default;
		JacobiMethod(Matrix<T> a, Matrix<T> b, T tolerance, int max_iterations);

	private:
		void compute() override;
	};

	template<typename T>
	JacobiMethod<T>::JacobiMethod(Matrix<T> a, Matrix<T> b, T tolerance, int max_iterations)
		: IterativeSolver<T>(a, b, tolerance, max_iterations)
	{
		compute();
	}

	template<typename T>
	void JacobiMethod<T>::compute()
	{
		this->_x = Matrix<T>(this->_a.rows(), 1);
		int i = 0;
		while (i++ < this->_its && norm_2(this->_b - this->_a * this->_x) > this->_tol) {
			Matrix<T> x = this->_x;
			for (int j = 0; j < this->_x.rows(); j++) {
				T sum = 0;
				for (int k = 0; k < this->_a.cols(); k++) {
					if (j != k) sum += this->_a(j, k) * x(k, 0);
				}
				this->_x(j, 0) = (this->_b(j, 0) - sum) / this->_a(j, j);
			}
		}
	}

	template<typename T>
	class GaussSeidelMethod : public IterativeSolver<T> {
	public:
		GaussSeidelMethod() = default;
		GaussSeidelMethod(Matrix<T> a, Matrix<T> b, T tolerance, int max_iterations);

	private:
		void compute() override;
	};

	template<typename T>
	GaussSeidelMethod<T>::GaussSeidelMethod(Matrix<T> a, Matrix<T> b, T tolerance, int max_iterations)
		: IterativeSolver<T>(a, b, tolerance, max_iterations)
	{
		compute();
	}

	template<typename T>
	void GaussSeidelMethod<T>::compute()
	{
		this->_x = Matrix<T>(this->_a.rows(), 1);
		int i = 0;
		while (i++ < this->_its && norm_2(this->_b - this->_a * this->_x) > this->_tol) {
			for (int j = 0; j < this->_x.rows(); j++) {
				T sum = 0;
				for (int k = 0; k < this->_a.cols(); k++) {
					if (j != k) sum += this->_a(j, k) * this->_x(k, 0);
				}
				this->_x(j, 0) = (this->_b(j, 0) - sum) / this->_a(j, j);
			}	
		}
	}
}

#endif /* ITERATIVE_SOLVERS_HH */
