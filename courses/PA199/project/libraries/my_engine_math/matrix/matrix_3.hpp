#pragma once

#include "./../vector/vector.hpp"
#include "./matrix_base.hpp"
#include "./matrix_2.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <cassert>

namespace my_engine
{
	// ================ //
	// 3×3 Matrix Class //
	// ================ //
	class Matrix3 : public Matrix<3>
	{
	public:
		// Constants //
		static const Matrix3 IDENTITY;
		static const Matrix3 ZERO;

		// Constructors //
		Matrix3();
		Matrix3(float a);
		Matrix3(const Matrix<3>& m);
		Matrix3(const std::array<Vector<3>, 3>& m);
		Matrix3(const std::array<std::array<float, 3>, 3>& m);
		Matrix3(const Matrix2& m, float f);

		// Matrix Orthonormalization //
		Matrix<3> orthonormalized() const override;

		// Matrix Deorthonormalization //
		Matrix<3> deorthonormalized() const override;

		// Static 2D Transformation Matrices in Homogeneous Coordinates //
		static Matrix3 translate_2d(const Vector2& direction);
		static Matrix3 rotate_2d(float radians);
		static Matrix3 scale_2d(const Vector2& axis);
		static Matrix3 shear_2d(const Vector2& axis);

		// Static 3D Transformation Matrices //
		static Matrix3 rotate_3d(float radians, const Vector3& axis);
		static Matrix3 scale_3d(const Vector3& axis);
	};
} // namespace my_engine