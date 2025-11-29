#pragma once

#include "./vector_base.hpp"
#include "./vector_2.hpp"

namespace my_engine
{
	// =============== //
	// 3D Vector Class //
	// =============== //
	class Vector3 : public Vector<3>
	{
	public:
		// Constants //
		static const Vector3 ZERO;
		static const Vector3 UP;
		static const Vector3 DOWN;
		static const Vector3 LEFT;
		static const Vector3 RIGHT;
		static const Vector3 FORWARD;
		static const Vector3 BACKWARD;

		// Constructors //
		Vector3();
		Vector3(float a);
		Vector3(const Vector<3>& v);
		Vector3(float x, float y, float z);
		Vector3(const Vector2& v, float z);

		// Getters //
		float& x() { return _coord[0]; }
		const float& x() const { return _coord[0]; }
		float& y() { return _coord[1]; }
		const float& y() const { return _coord[1]; }
		float& z() { return _coord[2]; }
		const float& z() const { return _coord[2]; }
		Vector2 xy() const { return Vector2(_coord[0], _coord[1]); }
		Vector2 xz() const { return Vector2(_coord[0], _coord[2]); }
		Vector2 yz() const { return Vector2(_coord[1], _coord[2]); }

		// Cross Product //
		Vector3 cross(const Vector3& v) const;
	};
} // namespace my_engine