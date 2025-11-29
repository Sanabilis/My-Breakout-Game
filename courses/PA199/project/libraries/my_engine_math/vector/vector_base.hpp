#pragma once

#include "./../constants.hpp"

#include <array>
#include <vector>
#include <cmath>
#include <iostream>

namespace my_engine
{
	// ================= //
	// Base Vector Class //
	// ================= //
	template<size_t size>
	class Vector
	{
	protected:
		// Coordinates //
		std::array<float, size> _coord;

	public:
		// Constructors //
		Vector() { _coord.fill(0.f); }
		Vector(float a) { _coord.fill(a); }
		Vector(const Vector<size>& v) { _coord = v._coord; }
		Vector(const std::array<float, size>& coord) { _coord = coord; }

		// Destructors //
		virtual ~Vector() {}

		// Subscript Operators //
		float& operator[](size_t i) { return _coord[i]; }
		const float& operator[](size_t i) const { return _coord[i]; };

		// Arithmetic Operators //
		Vector<size> operator*(float a) const;
		Vector<size> operator/(float a) const;
		Vector<size> operator+(const Vector<size>& v) const;
		Vector<size> operator-(const Vector<size>& v) const;
		Vector<size> operator-() const;

		// Assignment Operator //
		Vector<size>& operator=(const Vector<size>& v);

		// Compound Assignment Operators //
		Vector<size>& operator*=(float a);
		Vector<size>& operator/=(float a);
		Vector<size>& operator+=(const Vector<size>& v);
		Vector<size>& operator-=(const Vector<size>& v);

		// Relational Operators //
		bool operator==(const Vector<size>& v) const;
		bool operator!=(const Vector<size>& v) const;

		// Normalized Vector //
		Vector<size> normalized() const;

		// Dot Product //
		float dot(const Vector<size>& v) const;

		// Vector Magnitude //
		float magnitude() const;

		// Vector Dimension //
		size_t dimension() const { return size; }

		// Vector Tests //
		bool is_unit() const { return std::abs(this->magnitude() - 1.f) < 1e-05; }
		bool is_zero() const { return std::abs(this->magnitude()) < 1e-05; }


		// Raw Data //
		std::vector<float> data() const;

		// Print Function //
		virtual void print() const;
	};

	// Non-Member Arithmetic Operator //
	template<size_t size>
	Vector<size> operator*(float a, const Vector<size>& v);



	// ================= //
	// Base Vector Class //
	// ================= //

	// Arithmetic Operators //
	template<size_t size>
	Vector<size> Vector<size>::operator*(float a) const
	{
		Vector<size> res = *this;

		for (float& x : res._coord)
		{
			x *= a;
		}

		return res;
	}

	template<size_t size>
	Vector<size> operator*(float a, const Vector<size>& v)
	{
		return v * a;
	}

	template<size_t size>
	Vector<size> Vector<size>::operator/(float a) const
	{
		Vector<size> res = *this;

		for (float& x : res._coord)
		{
			x /= a;
		}

		return res;
	}

	template<size_t size>
	Vector<size> Vector<size>::operator+(const Vector<size>& v) const
	{
		Vector<size> res = *this;

		for (int i = 0; i < size; i++)
		{
			res._coord[i] += v._coord[i];
		}

		return res;
	}

	template<size_t size>
	Vector<size> Vector<size>::operator-(const Vector<size>& v) const
	{
		Vector<size> res = *this;

		for (int i = 0; i < size; i++)
		{
			res._coord[i] -= v._coord[i];
		}

		return res;
	}

	template<size_t size>
	Vector<size> Vector<size>::operator-() const
	{
		Vector<size> res = *this;

		for (float& x : res._coord)
		{
			x = -x;
		}

		return res;
	}


	// Assignment Operator //
	template<size_t size>
	Vector<size>& Vector<size>::operator=(const Vector<size>& v)
	{
		for (int i = 0; i < size; i++)
		{
			_coord[i] = v._coord[i];
		}

		return *this;
	}


	// Compound Assignment Operators //
	template<size_t size>
	Vector<size>& Vector<size>::operator*=(float a)
	{
		*this = *this * a;
		return *this;
	}

	template<size_t size>
	Vector<size>& Vector<size>::operator/=(float a)
	{
		*this = *this / a;
		return *this;
	}

	template<size_t size>
	Vector<size>& Vector<size>::operator+=(const Vector<size>& v)
	{
		*this = *this + v;
		return *this;
	}

	template<size_t size>
	Vector<size>& Vector<size>::operator-=(const Vector<size>& v)
	{
		*this = *this - v;
		return *this;
	}


	// Relational Operators //
	template<size_t size>
	bool Vector<size>::operator==(const Vector<size>& v) const
	{
		return (*this - v).magnitude() < 1e-05;
	}

	template<size_t size>
	bool Vector<size>::operator!=(const Vector<size>& v) const
	{
		return !(*this == v);
	}


	// Normalized Vector //
	template<size_t size>
	Vector<size> Vector<size>::normalized() const
	{
		if (this->magnitude() < 1e-05)
		{
			return Vector<size>(0.0f);
		}

		return *this / this->magnitude();
	}


	// Dot Product //
	template<size_t size>
	float Vector<size>::dot(const Vector<size>& v) const
	{
		float res = 0.f;

		for (int i = 0; i < size; i++)
		{
			res += _coord[i] * v._coord[i];
		}

		return res;
	}


	// Vector Magnitude //
	template<size_t size>
	float Vector<size>::magnitude() const
	{
		float res = 0.f;

		for (const float& x : _coord)
		{
			res += std::pow(x, 2.f);
		}

		return std::sqrt(res);
	}


	// Print Function //
	template<size_t size>
	void Vector<size>::print() const
	{
		std::cout << "[ ";

		for (float c : _coord)
		{
			std::cout << c << " ";
		}

		std::cout << "]";
	}


	// Raw Data //
	template<size_t size>
	std::vector<float> Vector<size>::data() const
	{
		return std::vector<float>(_coord.begin(), _coord.end());
	}
} // namespace my_engine