#ifndef MATRIX_HH
#define MATRIX_HH

#include <cassert>
#include <vector>

namespace num {
	template<typename T>
	class Matrix {
	public:
		Matrix(unsigned rows, unsigned cols);
		T operator()(unsigned row, unsigned col) const;
		T& operator()(unsigned row, unsigned col);
		unsigned rows() const;
		unsigned cols() const;
		void concat(const Matrix<T>& a);

	private:
		unsigned _rows, _cols;
		std::vector<std::vector<T>> _data;
	};
	
	template<typename T>
	Matrix<T>::Matrix(unsigned rows, unsigned cols)
	{
		_rows = rows;
		_cols = cols;
		_data.resize(rows);
		for (int i = 0; i < rows; i++) {
			_data[i].resize(cols);
		}
	}

	template<typename T>
	T Matrix<T>::operator()(unsigned row, unsigned col) const
	{
		assert(row >= 0 && row < _rows);
		assert(col >= 0 && col < _cols);
		
		return _data[row][col];
	}

	template<typename T>
	T& Matrix<T>::operator()(unsigned int row, unsigned int col)
	{
		assert(row >= 0 && row < _rows);
		assert(col >= 0 && col < _cols);
		
		return _data[row][col];
	}

	template<typename T>
	unsigned Matrix<T>::rows() const
	{
		return _rows;
	}

	template<typename T>
	unsigned Matrix<T>::cols() const
	{
		return _cols;
	}

	template<typename T>
	void Matrix<T>::concat(const Matrix<T> &a)
	{
		assert(_rows == a.rows());
		
		_rows += a.rows();
		_cols += a.cols();
		for (int i = 0; i < _rows; i++) {
			_data[i].reserve(_cols + a.cols());
			for (int j = 0; j < a.cols(); j++) {
				_data[i].push_back(a(i, j));
			}		      
		}
	}

	template<typename T>
	Matrix<T> concat_matrices(const Matrix<T> &a, const Matrix<T> &b)
	{
		Matrix<T> m = a;
		m.concat(b);

		return m;
	}

	template<typename T>
	Matrix<T> create_identity_matrix(unsigned rows, unsigned cols)
	{
		assert(rows == cols);
		
		Matrix<T> m{ rows, cols };
		for (int i = 0; i < cols; i++) {
			m(i, i) = static_cast<T>(1);
		}

		return m;
	}
}

#endif /* MATRIX_HH */
