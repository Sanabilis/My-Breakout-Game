#include "vector_4.hpp"

namespace my_engine
{
	// =============== //
	// 4D Vector Class //
	// =============== //
	
	// Constants //
	const Vector4 Vector4::ZERO = Vector4();


	// Constructors //
	Vector4::Vector4() : Vector<4>() {}

	Vector4::Vector4(float a) : Vector<4>(a) {}

	Vector4::Vector4(const Vector<4>& v) : Vector<4>(v) {}

	Vector4::Vector4(float x, float y, float z, float w)
	{
		_coord[0] = x;
		_coord[1] = y;
		_coord[2] = z;
		_coord[3] = w;
	}

	Vector4::Vector4(const Vector3& v, float w)
	{
		_coord[0] = v.x();
		_coord[1] = v.y();
		_coord[2] = v.z();
		_coord[3] = w;
	}
} // namespace my_engine