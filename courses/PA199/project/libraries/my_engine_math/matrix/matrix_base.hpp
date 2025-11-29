#pragma once

#include "./../vector/vector.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <cassert>

namespace my_engine
{
	// ==================== //
	// Default Matrix Class //
	// ==================== //
	template<size_t size>
	class Matrix
	{
	protected:
		// Rows of the Matrix //
		std::array<Vector<size>, size> _rows;

	public:
		// Constructors //
		Matrix();
		Matrix(float a);
		Matrix(const Vector<size>& v);
		Matrix(const Matrix<size>& m);
		Matrix(const std::array<Vector<size>, size>& m);
		Matrix(const std::array<std::array<float, size>, size>& m);

		// Destructor //
		virtual ~Matrix() {}

		// Subscript Operators //
		Vector<size>& operator[](size_t i) { return _rows[i]; }
		const Vector<size>& operator[](size_t i) const { return _rows[i]; }

		// Arithmetic Operators //
		Matrix<size> operator*(float a) const;
		Matrix<size> operator/(float a) const;
		Vector<size> operator*(const Vector<size>& v) const;
		Matrix<size> operator*(const Matrix<size>& m) const;
		Matrix<size> operator+(const Matrix<size>& m) const;
		Matrix<size> operator-(const Matrix<size>& m) const;
		Matrix<size> operator-() const;

		// Assignment Operators //
		Matrix<size>& operator=(const Matrix<size>& m);

		// Compound Assignment Operators //
		Matrix<size>& operator*=(float a);
		Matrix<size>& operator/=(float a);
		Matrix<size>& operator*=(const Vector<size>& v);
		Matrix<size>& operator*=(const Matrix<size>& m);
		Matrix<size>& operator+=(const Matrix<size>& m);
		Matrix<size>& operator-=(const Matrix<size>& m);

		// Relational Operators //
		bool operator==(const Matrix<size>& m) const;
		bool operator!=(const Matrix<size>& m) const;

		// Matrix Orthonormalization //
		virtual Matrix<size> orthonormalized() const;

		// Matrix Deorthonormalization //
		virtual Matrix<size> deorthonormalized() const;

		// Matrix Transpose //
		Matrix<size> transpose() const;

		// Matrix Inverse //
		Matrix<size> inverse() const;

		// Print Function //
		void print() const;
	};

	// Non-Member Arithmetic Operators
	template<size_t size>
	Matrix<size> operator*(float a, const Matrix<size>& m);



	// ==================== //
	// Default Matrix Class //
	// ==================== //

	// Constructors //
	template<size_t size>
	Matrix<size>::Matrix()
	{
		for (Vector<size>& r : _rows)
		{
			r = Vector<size>();
		}
	}

	template<size_t size>
	Matrix<size>::Matrix(float a)
	{
		for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (i != j)
			{
				_rows[i][j] = 0.f;
			}
			else
			{
				_rows[i][j] = a;
			}
		}
	}

	template<size_t size>
	Matrix<size>::Matrix(const Vector<size>& v)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i != j)
				{
					_rows[i][j] = 0.f;
				}
				else
				{
					_rows[i][j] = v[i];
				}
			}
		}
	}

	template<size_t size>
	Matrix<size>::Matrix(const Matrix<size>& m)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				_rows[i][j] = m._rows[i][j];
			}
		}
	}

	template<size_t size>
	Matrix<size>::Matrix(const std::array<Vector<size>, size>& m)
	{
		for (int i = 0; i < size; i++)
		{
			_rows[i] = m[i];
		}
	}

	template<size_t size>
	Matrix<size>::Matrix(const std::array<std::array<float, size>, size>& m)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				_rows[i][j] = m[i][j];
			}
		}
	}


	// Arithmetic Operators //
	template<size_t size>
	Matrix<size> Matrix<size>::operator*(float a) const
	{
		Matrix<size> result;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result._rows[i][j] = _rows[i][j] * a;
			}
		}

		return result;
	}

	template<size_t size>
	Matrix<size> operator*(float a, const Matrix<size>& m)
	{
		return m * a;
	}

	template<size_t size>
	Matrix<size> Matrix<size>::operator/(float a) const
	{
		Matrix<size> result;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result._rows[i][j] = _rows[i][j] / a;
			}
		}

		return result;
	}

	template<size_t size>
	Vector<size> Matrix<size>::operator*(const Vector<size>& v) const
	{
		Vector<size> result;

		for (int i = 0; i < size; i++)
		{
			result[i] = _rows[i].dot(v);
		}

		return result;
	}

	template<size_t size>
	Matrix<size> Matrix<size>::operator*(const Matrix<size>& m) const
	{
		Matrix<size> res;
		Matrix<size> temp = m.transpose();

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				res._rows[i][j] = _rows[i].dot(temp._rows[j]);
			}
		}

		return res;
	}

	template<size_t size>
	Matrix<size> Matrix<size>::operator+(const Matrix<size>& m) const
	{
		Matrix<size> result;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result._rows[i][j] = _rows[i][j] + m._rows[i][j];
			}
		}

		return result;
	}

	template<size_t size>
	Matrix<size> Matrix<size>::operator-(const Matrix<size>& m) const
	{
		Matrix<size> result;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result._rows[i][j] = _rows[i][j] - m._rows[i][j];
			}
		}

		return result;
	}

	template<size_t size>
	Matrix<size> Matrix<size>::operator-() const
	{
		Matrix<size> result;

		for (int i = 0; i < size; i++)
		{
			result._rows[i] = -_rows[i];
		}

		return *this;
	}


	// Assignment Operators //
	template<size_t size>
	Matrix<size>& Matrix<size>::operator=(const Matrix<size>& m)
	{
		for (int i = 0; i < size; i++)
		{
			_rows[i] = m._rows[i];
		}

		return *this;
	}


	// Compound Assignment Operators //
	template<size_t size>
	Matrix<size>& Matrix<size>::operator*=(float a)
	{
		*this = *this * a;
		return *this;
	}

	template<size_t size>
	Matrix<size>& Matrix<size>::operator/=(float a)
	{
		*this = *this / a;
		return *this;
	}

	template<size_t size>
	Matrix<size>& Matrix<size>::operator*=(const Vector<size>& v)
	{
		*this = *this * v;
		return *this;
	}

	template<size_t size>
	Matrix<size>& Matrix<size>::operator*=(const Matrix<size>& m)
	{
		*this = *this * m;
		return *this;
	}

	template<size_t size>
	Matrix<size>& Matrix<size>::operator+=(const Matrix<size>& m)
	{
		*this = *this + m;
		return *this;
	}

	template<size_t size>
	Matrix<size>& Matrix<size>::operator-=(const Matrix<size>& m)
	{
		*this = *this - m;
		return *this;
	}


	// Relational Operators //
	template<size_t size>
	bool Matrix<size>::operator==(const Matrix<size>& m) const
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (std::abs(_rows[i][j] - m._rows[i][j]) >= 1e-05)
				{
					return false;
				}
			}
		}

		return true;
	}

	template<size_t size>
	bool Matrix<size>::operator!=(const Matrix<size>& m) const
	{
		return !(*this == m);
	}


	// Matrix Orthonormalization //
	template<size_t size>
	Matrix<size> Matrix<size>::orthonormalized() const
	{
		return Matrix<size>(1.f);
	}


	// Matrix Deorthonormalization //
	template<size_t size>
	Matrix<size> Matrix<size>::deorthonormalized() const
	{
		return Matrix<size>(1.f);
	}


	// Matrix Transpose //
	template<size_t size>
	Matrix<size> Matrix<size>::transpose() const
	{
		Matrix<size> result;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result._rows[i][j] = _rows[j][i];
			}
		}

		return result;
	}


	// Matrix Inverse //
	template<size_t size>
	Matrix<size> Matrix<size>::inverse() const
	{
		Matrix<size> temp = *this;
		Matrix<size> result(1.f);

		// Top-to-Bottom Gaussian Elimination
		for (int i = 0; i < size; i++)
		{
			// Swap Rows
			if (std::abs(temp._rows[i][i]) < 1e-05)
			{
				int j = i + 1;

				while (j < size && temp._rows[j][i] < 1e-05)
				{
					j++;
				}

				if (j >= size)
				{
					return Matrix<size>(1.f);
				}

				Vector<size> r = result._rows[j];
				result._rows[j] = result._rows[i];
				result._rows[i] = r;

				r = temp._rows[j];
				temp._rows[j] = temp._rows[i];
				temp._rows[i] = r;
			}

			for (int j = i + 1; j < size; j++)
			{
				float f = temp._rows[j][i] / temp._rows[i][i];

				result._rows[j] = result._rows[j] - f * result._rows[i];
				temp._rows[j] = temp._rows[j] - f * temp._rows[i];
			}
		}

		// Bottom-to-Top Gaussian Elimination
		for (int i = size - 1; i >= 0; i--)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				float f = temp[j][i] / temp._rows[i][i];

				result._rows[j] = result._rows[j] - f * result[i];
				temp._rows[j] = temp._rows[j] - f * temp[i];
			}

			result._rows[i] = result._rows[i] / temp._rows[i][i];
			temp._rows[i] = temp._rows[i] / temp._rows[i][i];
		}

		return result;
	}


	// Print Function //
	template<size_t size>
	void Matrix<size>::print() const
	{
		for (const Vector<size>& r : _rows)
		{
			r.print();
			std::cout << std::endl;
		}
	}
} // namespace my_engine