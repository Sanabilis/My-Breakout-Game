#include "vector_3.hpp"

namespace my_engine
{
	// =============== //
	// 3D Vector Class //
	// =============== //

	// Constants //
	const Vector3 Vector3::ZERO = Vector3();
	const Vector3 Vector3::UP = Vector3(0.f, 1.f, 0.f);
	const Vector3 Vector3::DOWN = Vector3(0.f, -1.f, 0.f);
	const Vector3 Vector3::LEFT = Vector3(-1.f, 0.f, 0.f);
	const Vector3 Vector3::RIGHT = Vector3(1.f, 0.f, 0.f);
	const Vector3 Vector3::FORWARD = Vector3(0.f, 0.f, 1.f);
	const Vector3 Vector3::BACKWARD = Vector3(0.f, 0.f, -1.f);


	// Constructors //
	Vector3::Vector3() : Vector<3>() {}

	Vector3::Vector3(float a) : Vector<3>(a) {}

	Vector3::Vector3(const Vector<3>& v) : Vector<3>(v) {}

	Vector3::Vector3(float x, float y, float z)
	{
		_coord[0] = x;
		_coord[1] = y;
		_coord[2] = z;
	}

	Vector3::Vector3(const Vector2& v, float z)
	{
		_coord[0] = v.x();
		_coord[1] = v.y();
		_coord[2] = z;
	}


	// Cross Product //
	Vector3 Vector3::cross(const Vector3& v) const
	{
		return Vector3(
			y() * v.z() - v.y() * z(),
			z() * v.x() - v.z() * x(),
			x() * v.y() - v.x() * y()
		);
	}
} // namespace my_engine