#ifndef ITERATIVE_SOLVERS_HH
#define ITERATIVE_SOLVERS_HH

#include "linear-solver.hh"
#include "iterative-method.hh"

namespace num {
namespace linalg {
	template<typename T>
	class JacobiMethod : public LinearSolver<T>, public IterativeMethod<T> {
	public:
		JacobiMethod() = default;
		JacobiMethod(Matrix<T> a, Matrix<T> b, double tolerance, int max_iterations);

	private:
		void compute() override;
	};

	template<typename T>
	JacobiMethod<T>::JacobiMethod(Matrix<T> a, Matrix<T> b, double tolerance, int max_iterations)
		: LinearSolver<T>(a, b), IterativeMethod<T>(tolerance, max_iterations)
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
			for (std::size_t j = 0; j < this->_x.rows(); j++) {
				T sum = 0;
				for (std::size_t k = 0; k < this->_a.cols(); k++) {
					if (j != k) sum += this->_a(j, k) * x(k, 0);
				}
				this->_x(j, 0) = (this->_b(j, 0) - sum) / this->_a(j, j);
			}
#ifndef N_DEBUG
			std::cout << "i: " << i - 1 << " err: " << norm_2(this->_b - this->_a * this->_x) << "\n";
#endif
		}
#ifndef N_DEBUG
		std::cout << "iterations: " << i - 1 << std::endl;
#endif
	}

	template<typename T>
	class GaussSeidelMethod : public LinearSolver<T>, public IterativeMethod<T> {
	public:
		GaussSeidelMethod() = default;
		GaussSeidelMethod(Matrix<T> a, Matrix<T> b, double tolerance, int max_iterations);

	private:
		void compute() override;
	};

	template<typename T>
	GaussSeidelMethod<T>::GaussSeidelMethod(Matrix<T> a, Matrix<T> b, double tolerance, int max_iterations)
		: LinearSolver<T>(a, b), IterativeMethod<T>(tolerance, max_iterations)
	{
		compute();
	}

	template<typename T>
	void GaussSeidelMethod<T>::compute()
	{
		this->_x = Matrix<T>(this->_a.rows(), 1);
		int i = 0;
		while (i++ < this->_its && norm_2(this->_b - this->_a * this->_x) > this->_tol) {
			for (std::size_t j = 0; j < this->_x.rows(); j++) {
				T sum = 0;
				for (std::size_t k = 0; k < this->_a.cols(); k++) {
					if (j != k) sum += this->_a(j, k) * this->_x(k, 0);
				}
				this->_x(j, 0) = (this->_b(j, 0) - sum) / this->_a(j, j);
			}
#ifndef N_DEBUG
			std::cout << "i: " << i - 1 << " err: " << norm_2(this->_b - this->_a * this->_x) << "\n";
#endif
		}
#ifndef N_DEBUG
		std::cout << "iterations: " << i - 1 << std::endl;
#endif
	}

	template<typename T>
	class SOR : public LinearSolver<T>, public IterativeMethod<T> {
	public:
		SOR();
		SOR(Matrix<T> a, Matrix<T> b, double tolerance, int max_iterations, double relaxation);
	
	private:
		void compute() override;

		double _rlx;
	};

	template<typename T>
	SOR<T>::SOR()
		: _rlx(1.0)
	{ }

	template<typename T>
	SOR<T>::SOR(Matrix<T> a, Matrix<T> b, double tolerance, int max_iterations, double relaxation)
		: LinearSolver<T>(a, b), IterativeMethod<T>(tolerance, max_iterations)
	{
		assert(relaxation >= 0 && relaxation <= 2);
			
		_rlx = relaxation;

		compute();
	}

	template<typename T>
	void SOR<T>::compute()
	{
		this->_x = Matrix<T>(this->_a.rows(), 1);
		int i = 0;
		while (i++ < this->_its && norm_2(this->_b - this->_a * this->_x) > this->_tol) {
			for (std::size_t j = 0; j < this->_x.rows(); j++) {
				T sum = 0;
				for (std::size_t k = 0; k < this->_a.cols(); k++) {
					if (j != k) sum += this->_a(j, k) * this->_x(k, 0);
				}
				this->_x(j, 0) = this->_x(j, 0) + _rlx * (((this->_b(j, 0) - sum) / this->_a(j, j)) - this->_x(j, 0));
			}
#ifndef N_DEBUG
			std::cout << "i: " << i - 1 << " err: " << norm_2(this->_b - this->_a * this->_x) << "\n";
#endif
		}
#ifndef N_DEBUG
		std::cout << "iterations: " << i - 1 << std::endl;
#endif
	}
}
}
	
#endif /* ITERATIVE_SOLVERS_HH */
