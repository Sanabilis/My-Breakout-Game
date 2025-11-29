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
	// Declaration of Axis Angle Class //
	class AxisAngle;


	// ================ //
	// Quaternion Class //
	// ================ //
	class Quaternion : public Vector<4>
	{
	public:
		// Constructors //
		Quaternion();
		Quaternion(float angle, const Vector3& axis);
		Quaternion(const Vector<4>& q);
		Quaternion(float w, float a, float b, float c);

		// Getters //
		float& w() { return _coord[0]; }
		const float& w() const { return _coord[0]; }
		float& x() { return _coord[1]; }
		const float& x() const { return _coord[1]; }
		float& y() { return _coord[2]; }
		const float& y() const { return _coord[2]; }
		float& z() { return _coord[3]; }
		const float& z() const { return _coord[3]; }
		float angle() const;
		Vector3 axis() const;

		// Arithmetic Operators //
		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator*(float a) const;

		// Assignment Operator //
		Quaternion& operator=(const Quaternion& q);

		// Compound Assignment Operators //
		Quaternion& operator*=(const Quaternion& q);
		Quaternion& operator*=(float a);

		// Advanced Arithmetic Operations //
		static Quaternion log(const Quaternion& q);
		static Quaternion exp(const Quaternion& q);
		static Quaternion exp(const Quaternion& q, float t);

		// Quaternion Length //
		float length() const { return this->magnitude(); }

		// Quaternion Conjugate //
		Quaternion conjugate() const;

		// Quaternion Inverse //
		Quaternion inverse() const;

		// 3D Vector Rotation //
		Vector3 rotate(const Vector3& v) const;

		// Quaternion Interpolation //
		Quaternion lerp(const Quaternion& q, float t) const;
		Quaternion slerp(const Quaternion& q, float t) const;
		
		// Different Rotation Representations //
		AxisAngle axis_angle() const;
		Matrix4 rotation_matrix() const;

		// Print Function //
		void print() const override;
	};

	// Non-Member Arithmetic Operator //
	Quaternion operator*(float a, const Quaternion& q);
} // namespace my_engine