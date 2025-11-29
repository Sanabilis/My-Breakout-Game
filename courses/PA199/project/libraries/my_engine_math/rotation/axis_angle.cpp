#include "./axis_angle.hpp"
#include "./quaternion.hpp"

namespace my_engine
{
	// ================ //
	// Axis Angle Class //
	// ================ //

	// Constructors //
	AxisAngle::AxisAngle() : angle(0.f), axis(Vector3::UP) {}

	AxisAngle::AxisAngle(float angle, const Vector3& axis) : angle(angle), axis(axis.normalized()) {}

	AxisAngle::AxisAngle(const AxisAngle& ax_a) : angle(ax_a.angle), axis(ax_a.axis) {}


	// Equivalent Quaternion //
	Quaternion AxisAngle::quaternion() const
	{
		return Quaternion(angle, axis);
	}


	// 3D Vector Rotation //
	Vector3 AxisAngle::rotate(const Vector3& v)
	{
		Vector3 v1 = std::cos(angle) * v;
		Vector3 v2 = std::sin(angle) * axis.cross(v);
		Vector3 v3 = (1.f - std::cos(angle)) * axis.dot(v) * axis;

		return v1 + v2 + v3;
	}
} // namespace my_engine
