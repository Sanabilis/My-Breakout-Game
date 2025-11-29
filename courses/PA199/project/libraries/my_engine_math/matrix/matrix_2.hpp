#pragma once

#include "./../vector/vector.hpp"
#include "./matrix_base.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <cassert>

namespace my_engine
{
	// ================ //
	// 2×2 Matrix Class //
	// ================ //
	class Matrix2 : public Matrix<2>
	{
	public:
		// Constants //
		static const Matrix2 IDENTITY;
		static const Matrix2 ZERO;

		// Constructors //
		Matrix2();
		Matrix2(float a);
		Matrix2(const Matrix<2>& m);
		Matrix2(const std::array<Vector<2>, 2>& m);
		Matrix2(const std::array<std::array<float, 2>, 2>& m);

		// Matrix Orthonormalization //
		Matrix<2> orthonormalized() const override;

		// Matrix Deorthonormalization //
		Matrix<2> deorthonormalized() const override;

		// Static 2D Transformation Matrices //
		static Matrix2 rotate_2d(float radians);
		static Matrix2 scale_2d(const Vector2& axis);
		static Matrix2 shear_2d(const Vector2& axis);
	};
} // namespace my_engine