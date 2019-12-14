#ifndef MATRIX_HH
#define MATRIX_HH

#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

namespace num {
	template<typename T>
	class Matrix {
	public:
		Matrix();
		Matrix(const unsigned rows, const unsigned cols);
		T operator()(const unsigned row, const unsigned col) const;
		T& operator()(const unsigned row, const unsigned col);
		const std::vector<T>& operator[](const unsigned row) const;
		std::vector<T>& operator[](const unsigned row);
		unsigned rows() const;
		unsigned cols() const;
		void transpose();
		void concat(const Matrix<T>& a);
		void append_row(const std::vector<double>& row);
		void append_col(const std::vector<double>& col);

	private:
		unsigned _rows, _cols;
		std::vector<std::vector<T>> _data;
	};

	template<typename T>
	Matrix<T>::Matrix()
		: _rows(0), _cols(0)
	{ }
	
	template<typename T>
	Matrix<T>::Matrix(const unsigned rows, const unsigned cols)
		: _rows(rows), _cols(cols)
	{
		_data.resize(rows);
		for (std::size_t i = 0; i < rows; i++) {
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
	const std::vector<T>& Matrix<T>::operator[](const unsigned row) const
	{
		assert(row >= 0 && row < _rows);
		
		return _data[row];
	}

	template<typename T>
	std::vector<T>& Matrix<T>::operator[](const unsigned int row)
	{
		assert(row >= 0 && row < _rows);
		
		return _data[row];
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
		for (std::size_t i = 0; i < _cols; i++) {
			data[i].resize(_rows);
			for (std::size_t j = 0; j < _rows; j++) {
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
		
		for (std::size_t i = 0; i < _rows; i++) {
			_data[i].reserve(_cols + a.cols());
			for (std::size_t j = 0; j < a.cols(); j++) {
				_data[i].push_back(a(i, j));
			}		      
		}
		_cols += a.cols();
	}

	template<typename T>
	void Matrix<T>::append_row(const std::vector<double>& row)
	{
		if (_cols == 0) _cols = row.size();
		
		assert(row.size() == _cols);

		_data.push_back(row);
		_rows++;
	}

	template<typename T>
	void Matrix<T>::append_col(const std::vector<double>& col)
	{
		if (_rows == 0) {
			_rows = col.size();
			_data.resize(col.size());
		} 
		
		assert(col.size() == _rows);

		for (std::size_t i = 0; i < col.size(); i++) {
			_data[i].push_back(col[i]);
		}
		_cols++;
	}

	template<typename T>
	Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
	{
		assert(a.rows() == b.rows());
		assert(a.cols() == b.cols());
		
		Matrix<T> m = a;
		for (std::size_t i = 0; i < a.rows(); i++) {
			for (std::size_t j = 0; j < a.cols(); j++) {
				m(i, j) += b(i, j);
			}
		}
		
		return m;
	}

	template<typename T>
	Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
	{
		assert(a.rows() == b.rows());
		assert(a.cols() == b.cols());
		
		Matrix<T> m = a;
		for (std::size_t i = 0; i < a.rows(); i++) {
			for (std::size_t j = 0; j < a.cols(); j++) {
				m(i, j) -= b(i, j);
			}
		}
		
		return m;
	}

	template<typename T>
	Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
	{
		assert(a.cols() == b.rows());
		
		Matrix<T> m(a.rows(), b.cols());
		for (std::size_t i = 0; i < m.rows(); i++) {
			for (std::size_t j = 0; j < m.cols(); j++) {
				for (std::size_t k = 0; k < a.cols(); k++) {
					m(i, j) += a(i, k) * b(k, j); 
				}
			}
		}

		return m;
	}

	template<typename T>
	Matrix<T> operator*(const Matrix<T>& a, const T c)
	{		
		Matrix<T> m(a.rows(), a.cols());
		for (std::size_t i = 0; i < m.rows(); i++) {
			for (std::size_t j = 0; j < m.cols(); j++) {
				m(i, j) = a(i, j) * c;
			}
		}

		return m;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Matrix<T>& a)
	{
		std::ios::fmtflags flags = os.flags();
		os.setf(std::ios::left, std::ios::adjustfield);
		for (std::size_t i = 0; i < a.rows(); i++) {
			for (std::size_t j = 0; j < a.cols(); j++) {
				os << std::setw(10) << a(i, j);
			}
			if (i == a.rows() - 1) break;
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
		for (std::size_t i = 0; i < cols; i++) {
			m(i, i) = static_cast<T>(1);
		}

		return m;
	}

	template<typename T>
	T norm_2(const Matrix<T>& v)
	{
		assert(v.cols() == 1);

		T sum = 0;
		for (std::size_t i = 0; i < v.rows(); i++) {
			sum += v(i, 0) * v(i, 0);
		}

		return std::sqrt(sum);
	}
}

#endif /* MATRIX_HH */
