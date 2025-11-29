#pragma once

#include "./vector_base.hpp"

namespace my_engine
{
	// =============== //
	// 2D Vector Class //
	// =============== //
	class Vector2 : public Vector<2>
	{
	public:
		// Constansts //
		static const Vector2 ZERO;
		static const Vector2 UP;
		static const Vector2 DOWN;
		static const Vector2 LEFT;
		static const Vector2 RIGHT;

		// Constructors //
		Vector2();
		Vector2(float a);
		Vector2(const Vector<2>& v);
		Vector2(float x, float y);

		// Getters //
		float& x() { return _coord[0]; }
		const float& x() const { return _coord[0]; }
		float& y() { return _coord[1]; }
		const float& y() const  { return _coord[1]; }
	};
} // namespace my_engine