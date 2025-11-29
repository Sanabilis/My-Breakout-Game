#include "vector_2.hpp"

namespace my_engine
{
	// =============== //
	// 2D Vector Class //
	// =============== //

	// Constansts //
	const Vector2 Vector2::ZERO = Vector2();
	const Vector2 Vector2::UP = Vector2(0.f, 1.f);
	const Vector2 Vector2::DOWN = Vector2(0.f, -1.f);
	const Vector2 Vector2::LEFT = Vector2(-1.f, 0.f);
	const Vector2 Vector2::RIGHT = Vector2(1.f, 0.f);


	// Constructors //
	Vector2::Vector2() : Vector<2>() {}

	Vector2::Vector2(float a) : Vector<2>(a) {}

	Vector2::Vector2(const Vector<2>& v) : Vector<2>(v) {}

	Vector2::Vector2(float x, float y)
	{
		_coord[0] = x;
		_coord[1] = y;
	}
} // namespace my_engine