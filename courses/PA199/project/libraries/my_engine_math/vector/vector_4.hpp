#pragma once

#include "./vector_base.hpp"
#include "./vector_2.hpp"
#include "./vector_3.hpp"

namespace my_engine
{
	// =============== //
	// 4D Vector Class //
	// =============== //
	class Vector4 : public Vector<4>
	{
	public:
		// Constants //
		static const Vector4 ZERO;

		// Constructors //
		Vector4();
		Vector4(float a);
		Vector4(const Vector<4>& v);
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector3& v, float w);

		// Getters //
		float& x() { return _coord[0]; }
		const float& x() const { return _coord[0]; }
		float& y() { return _coord[1]; }
		const float& y() const { return _coord[1]; }
		float& z() { return _coord[2]; }
		const float& z() const { return _coord[2]; }
		float& w() { return _coord[3]; }
		const float& w() const { return _coord[3]; }
		Vector2 xy() const { return Vector2(_coord[0], _coord[1]); }
		Vector2 xz() const { return Vector2(_coord[0], _coord[2]); }
		Vector2 yz() const { return Vector2(_coord[1], _coord[2]); }
		Vector3 xyz() const { return Vector3(_coord[0], _coord[1], _coord[2]); }
	};
} // namespace my_engine