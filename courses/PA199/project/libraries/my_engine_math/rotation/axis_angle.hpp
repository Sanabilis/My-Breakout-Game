#pragma once

#include "./../constants.hpp"
#include "./../vector/vector.hpp"
#include "./../matrix/matrix.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <cassert>

namespace my_engine
{
	// Declaration of Quaternion Class //
	class Quaternion;


	// ================ //
	// Axis Angle Class //
	// ================ //
	class AxisAngle
	{
		float angle;
		Vector3 axis;

	public:
		// Constructors //
		AxisAngle();
		AxisAngle(float angle, const Vector3& axis);
		AxisAngle(const AxisAngle& ax_a);

		// Equivalent Quaternion //
		Quaternion quaternion() const;

		// 3D Vector Rotation //
		Vector3 rotate(const Vector3& v);
	};
} // namespace my_engine