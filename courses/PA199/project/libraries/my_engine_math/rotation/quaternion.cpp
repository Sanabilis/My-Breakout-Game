#include "./quaternion.hpp"
#include "./axis_angle.hpp"

namespace my_engine
{
	// ================ //
	// Quaternion Class //
	// ================ //
	
	// Constructors //
	Quaternion::Quaternion()
	{
		_coord[0] = 1.f;
		_coord[1] = 0.f;
		_coord[2] = 0.f;
		_coord[3] = 0.f;
	}

	Quaternion::Quaternion(float angle, const Vector3& axis)
	{
		Vector3 unit = axis.normalized();

		_coord[0] = std::cos(angle / 2.f);
		_coord[1] = unit.x() * std::sin(angle / 2.f);
		_coord[2] = unit.y() * std::sin(angle / 2.f);
		_coord[3] = unit.z() * std::sin(angle / 2.f);
	}

	Quaternion::Quaternion(const Vector<4>& q) : Vector<4>(q) {}

	Quaternion::Quaternion(float w, float x, float y, float z)
	{
		_coord[0] = w;
		_coord[1] = x;
		_coord[2] = y;
		_coord[3] = z;
	}


	// Getters //
	float Quaternion::angle() const
	{
		return std::acos(w());
	}

	Vector3 Quaternion::axis() const
	{
		if (std::abs(this->angle()) < 1e-05)
		{
			return Vector3::UP;
		}

		return Vector3(x(), y(), z()) / std::sin(this->angle());
	}


	// Arithmetic Operators //
	Quaternion Quaternion::operator*(float a) const
	{
		Quaternion res;

		res.w() = w() * a;
		res.x() = x() * a;
		res.y() = y() * a;
		res.z() = z() * a;

		return res;
	}

	Quaternion operator*(float a, const Quaternion& q)
	{
		return q * a;
	}

	Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		Quaternion res;

		float s1 = w();
		float s2 = q.w();
		Vector3 v1 = Vector3(x(), y(), z());
		Vector3 v2 = Vector3(q.x(), q.y(), q.z());
		Vector3 r = v1.cross(v2) + s1 * v2 + s2 * v1;

		res.w() = s1 * s2 - v1.dot(v2);
		res.x() = r.x();
		res.y() = r.y();
		res.z() = r.z();

		return res;
	}


	// Assignment Operators //
	Quaternion& Quaternion::operator=(const Quaternion& q)
	{
		w() = q.w();
		x() = q.x();
		y() = q.y();
		z() = q.z();

		return *this;
	}


	// Compound Assignment Operators //
	Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		*this = *this * q;
		return *this;
	}

	Quaternion& Quaternion::operator*=(float a)
	{
		*this = *this * a;
		return *this;
	}


	// Advanced Arithmetic Operations //
	Quaternion Quaternion::log(const Quaternion& q)
	{
		assert(q.is_unit());

		Vector3 temp = q.angle() * q.axis();

		return Quaternion(0.f, temp.x(), temp.y(), temp.z());
	}

	Quaternion Quaternion::exp(const Quaternion& q)
	{
		assert(std::abs(q.w()) < 1e-05);

		if (q.length() < 1e-05)
		{
			return Quaternion(1.f, 0.f, 0.f, 0.f);
		}

		float f = std::sin(q.length()) / q.length();
		Vector3 temp = f * Vector3(q.x(), q.y(), q.z());

		return Quaternion(std::cos(q.length()), temp.x(), temp.y(), temp.z());
	}

	Quaternion Quaternion::exp(const Quaternion& q, float t)
	{
		return exp(t * log(q));
	}


	// Quaternion Conjugate //
	Quaternion Quaternion::conjugate() const
	{
		Quaternion res;

		res.w() = w();
		res.x() = -x();
		res.y() = -y();
		res.z() = -z();

		return res;
	}


	// Quaternion Inverse //
	Quaternion Quaternion::inverse() const
	{
		return this->conjugate() / std::powf(this->length(), 2);
	}


	// 3D Vector Rotation //
	Vector3 Quaternion::rotate(const Vector3& v) const
	{
		assert(this->is_unit());

		Quaternion temp = *this * Quaternion(0.f, v.x(), v.y(), v.z()) * this->inverse();

		return Vector3(temp.x(), temp.y(), temp.z());
	}


	// Quaternion Interpolation //
	Quaternion Quaternion::lerp(const Quaternion& q, float t) const
	{
		return *this * (1.f - t) + q * t;
	}

	Quaternion Quaternion::slerp(const Quaternion& q, float t) const
	{
		return *this * exp(this->conjugate() * q, t);
	}


	// Different Rotation Representations //
	AxisAngle Quaternion::axis_angle() const
	{
		return AxisAngle(this->angle() * 2.f, this->axis());
	}

	Matrix4 Quaternion::rotation_matrix() const
	{
		return Matrix4::rotate_3d(this->angle() * 2.f, this->axis());
	}


	// Print Function //
	void Quaternion::print() const
	{
		std::cout << w();
		char complex[] = { 'n', 'i', 'j', 'k' };

		for (int i = 1; i < this->dimension(); i++)
		{
			if (_coord[i] < 0.f)
			{
				std::cout << " - ";
			}
			else
			{
				std::cout << " + ";
			}

			std::cout << std::abs(x()) << complex[i];
		}
	}
} // namespace my_engine
