#ifndef MATRIX_HH
#define MATRIX_HH

#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>

namespace num {
	template<typename T>
	class Matrix {
	public:
		Matrix(const unsigned rows, const unsigned cols);
		T operator()(const unsigned row, const unsigned col) const;
		T& operator()(const unsigned row, const unsigned col);
		unsigned rows() const;
		unsigned cols() const;
		void transpose();
		void concat(const Matrix<T>& a);

	private:
		unsigned _rows, _cols;
		std::vector<std::vector<T>> _data;
	};
	
	template<typename T>
	Matrix<T>::Matrix(const unsigned rows, const unsigned cols)
	{
		_rows = rows;
		_cols = cols;
		_data.resize(rows);
		for (int i = 0; i < rows; i++) {
			_data[i].resize(cols);
		}
	}

	template<typename T>
	T Matrix<T>::operator()(const unsigned row, const unsigned col) const
	{
		assert(row >= 0 && row < _rows);
		assert(col >= 0 && col < _cols);
		
		return _data[row][col];
	}

	template<typename T>
	T& Matrix<T>::operator()(const unsigned int row, const unsigned int col)
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
	void Matrix<T>::transpose()
	{
		std::vector<std::vector<T>> data;
		data.resize(_cols);
		for (int i = 0; i < _cols; i++) {
			data[i].resize(_rows);
			for (int j = 0; j < _rows; j++) {
				data[i][j] = _data[j][i];
			}
		}
		_data = data;
		unsigned rows = _rows;
		_rows = _cols;
		_cols = rows;
	}

	template<typename T>
	void Matrix<T>::concat(const Matrix<T> &a)
	{
		assert(_rows == a.rows());
		
		for (int i = 0; i < _rows; i++) {
			_data[i].reserve(_cols + a.cols());
			for (int j = 0; j < a.cols(); j++) {
				_data[i].push_back(a(i, j));
			}		      
		}
		_cols += a.cols();
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Matrix<T>& a)
	{
		std::ios::fmtflags flags = os.flags();
		os.setf(std::ios::left, std::ios::adjustfield);
		for (int i = 0; i < a.rows(); i++) {
			for (int j = 0; j < a.cols(); j++) {
				os << std::setw(10) << a(i, j);
			}
			os << "\n";
		}
		os.flags(flags);

		return os;
	}

	template<typename T>
	Matrix<T> transpose_matrix(const Matrix<T>& a)
	{
		Matrix<T> m = a;
		m.transpose();

		return m;
	}

	template<typename T>
	Matrix<T> concat_matrices(const Matrix<T> &a, const Matrix<T> &b)
	{
		Matrix<T> m = a;
		m.concat(b);

		return m;
	}

	template<typename T>
	Matrix<T> create_identity_matrix(const unsigned rows, const unsigned cols)
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
