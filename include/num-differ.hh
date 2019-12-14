#ifndef NUM_DIFF_HH
#define NUM_DIFF_HH

#include "solver.hh"
#include "matrix.hh"

namespace num {
	template<typename T>
	class NumDiffer : public Solver {
	public:
		NumDiffer();
		NumDiffer(Matrix<T> vals, double h, int order);
		Matrix<T> derivated() const;
				
	private:
		void compute() override;
		
		double _h, _fac;
		Matrix<T> _coeff, _vals, _deriv;
	};

	template<typename T>
	NumDiffer<T>::NumDiffer()
		: _h(0.0), _fac(0.0)
	{ }

	template<typename T>
	NumDiffer<T>::NumDiffer(Matrix<T> vals, double h, int order)
		: _vals(vals), _h(h)
	{
		assert(vals.rows() >= 3);

		_coeff = Matrix<T>(vals.rows(), vals.rows());
		if (order == 1) {
			_coeff(0, 1) = static_cast<T>(1);
			_coeff(_coeff.rows() - 1, _coeff.cols() - 2) = static_cast<T>(-1);
			for (std::size_t i = 1; i < _coeff.rows() - 1; i++) {
				_coeff(i, i - 1) = static_cast<T>(-1);
				_coeff(i, i + 1) = static_cast<T>(1);
			}

			_fac = 1 / (2 * h);
		} else if (order == 2) {
			_coeff(0, 0) = static_cast<T>(-2);
			_coeff(0, 1) = static_cast<T>(1);
			_coeff(_coeff.rows() - 1, _coeff.cols() - 2) = static_cast<T>(-1);
			_coeff(_coeff.rows() - 1, _coeff.cols() -1) = static_cast<T>(-2);
			for (std::size_t i = 1; i < _coeff.rows() - 1; i++) {
				_coeff(i, i - 1) = static_cast<T>(1);
				_coeff(i, i) = static_cast<T>(-2);
				_coeff(i, i + 1) = static_cast<T>(1);
			}

			_fac = 1 / (h * h);
		}

		std::cout << _coeff << std::endl;

		compute();
	}

	template<typename T>
	Matrix<T> NumDiffer<T>::derivated() const
	{
		return _deriv;
	}

	template<typename T>
	void NumDiffer<T>::compute()
	{
		_deriv =  _coeff * _vals * _fac;
	}
}

#endif /* NUM_DIFF_HH */
