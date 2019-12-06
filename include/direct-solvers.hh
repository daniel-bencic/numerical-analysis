#ifndef DIRECT_SOLVERS_HH
#define DIRECT_SOLVERS_HH

#include "linear-solver.hh"
#include "matrix.hh"

namespace num {
	template<typename T>
	class GaussianElimination : public LinearSolver<T> {
	public:
		GaussianElimination() = default;
		GaussianElimination(Matrix<T> a, std::vector<T> x);

	private:
		void compute() override;
	};

	template<typename T>
	GaussianElimination<T>::GaussianElimination(Matrix<T> a, std::vector<T> x)
		: LinearSolver<T>(a, x)
	{
		compute();
	}

	template<typename T>
	void GaussianElimination<T>::compute()
	{
	   
	}

	template<typename T>
	class LUDecomposition : public LinearSolver<T> {
	public:
		LUDecomposition() = default;
		LUDecomposition(Matrix<T> a, std::vector<T> x);

	private:
		void compute() override;
	};

	template<typename T>
	LUDecomposition<T>::LUDecomposition(Matrix<T> a, std::vector<T> x)
		: LinearSolver<T>(a, x)
	{
		compute();
	}

	template<typename T>
	void LUDecomposition<T>::compute()
	{
		
	}
}

#endif /* DIRECT_SOLVERS_HH */
