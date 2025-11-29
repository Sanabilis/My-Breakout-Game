#pragma once

#include "./../constants.hpp"
#include "./../vector/vector.hpp"
#include "./../matrix/matrix.hpp"

#include <cmath>

namespace my_engine
{
	// ======================= //
	// Polar Coordinates Class //
	// ======================= //
	class PolarCoordinates
	{
	private:
		float _radius;
		float _angle;

	public:
		// Constructors //
		PolarCoordinates();
		PolarCoordinates(float radius, float angle);
		PolarCoordinates(const Vector3& v);
		PolarCoordinates(const Vector2& v);

		// Getters //
		float get_radius() const;
		float get_angle() const;

		// Setters //
		void set_radius(float radius);
		void set_angle(float angle);

		// Assignment Operators //
		PolarCoordinates& operator=(const PolarCoordinates& polar_coordinates);
		PolarCoordinates& operator=(const Vector2& vector);
		PolarCoordinates& operator=(const Vector3& vector);

		// Cartesian Coordinates //
		Vector2 cartesian() const;

	private:
		// Normalization //
		void normalize();
	};
} // namespace my_engine