#pragma once

#include "./../vector/vector.hpp"
#include "./matrix_base.hpp"
#include "./matrix_2.hpp"
#include "./matrix_3.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <cassert>

namespace my_engine
{
	// ================ //
	// 4×4 Matrix Class //
	// ================ //
	class Matrix4 : public Matrix<4>
	{
	public:
		// Constants //
		static const Matrix4 IDENTITY;
		static const Matrix4 ZERO;

		// Constructors //
		Matrix4();
		Matrix4(float a);
		Matrix4(const Matrix<4>& m);
		Matrix4(const std::array<Vector<4>, 4>& m);
		Matrix4(const std::array<std::array<float, 4>, 4>& m);
		Matrix4(const Matrix3& m, float f);

		// Static 3D Transformation Matrices in Homogeneous Coordinates //
		static Matrix4 translate_3d(const Vector3& direction);
		static Matrix4 rotate_3d(float radians, const Vector3& axis);
		static Matrix4 scale_3d(const Vector3& axis);
	};
} // namespace my_engine