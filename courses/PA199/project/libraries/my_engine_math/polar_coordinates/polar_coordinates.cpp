#include "./polar_coordinates.hpp"

namespace my_engine
{
	// ======================= //
	// Polar Coordinates Class //
	// ======================= //

	// Constructors //
	PolarCoordinates::PolarCoordinates() : _radius(1.0f), _angle(0.0f) {}

	PolarCoordinates::PolarCoordinates(float radius, float angle) : _radius(radius), _angle(angle)
	{
		normalize();
	}

	PolarCoordinates::PolarCoordinates(const Vector3& v) : PolarCoordinates(v.xz()) {}

	PolarCoordinates::PolarCoordinates(const Vector2& v)
	{
		_radius = v.magnitude();

		if (v.y() >= 0.0f)
		{
			_angle = std::acos(v.normalized().dot(Vector2::RIGHT));
		}
		else
		{
			_angle = 2.0f * PI - std::acos(v.normalized().dot(Vector2::RIGHT));
		}
	}

	// Getters //
	float PolarCoordinates::get_radius() const
	{
		return _radius;
	}

	float PolarCoordinates::get_angle() const
	{
		return _angle;
	}


	// Setters //
	void PolarCoordinates::set_radius(float radius)
	{
		_radius = radius;
	}
	
	void PolarCoordinates::set_angle(float angle)
	{
		_angle = angle;
		normalize();
	}


	// Assignment Operators //
	PolarCoordinates& PolarCoordinates::operator=(const PolarCoordinates& polar_coordinates)
	{
		_angle = polar_coordinates._angle;
		_radius = polar_coordinates._radius;
		return *this;
	}

	PolarCoordinates& PolarCoordinates::operator=(const Vector2& vector)
	{
		*this = PolarCoordinates(vector);
		return *this;
	}

	PolarCoordinates& PolarCoordinates::operator=(const Vector3& vector)
	{
		return *this = vector.xz();
	}


	// Cartesian Coordinates //
	Vector2 PolarCoordinates::cartesian() const
	{
		return Vector2(std::cos(_angle) * _radius, std::sin(_angle) * _radius);
	}


	// Nomralization //
	void PolarCoordinates::normalize()
	{
		_angle = std::fmod(_angle, 2.0f * PI);

		if (_angle < 0.0f)
		{
			_angle += 2.0f * PI;
		}
	}
} // namespace my_engine