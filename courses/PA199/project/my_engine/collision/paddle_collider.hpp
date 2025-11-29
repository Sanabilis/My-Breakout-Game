#pragma once

#include "./base_collider.hpp"

namespace my_engine
{
	// =============== //
	// Paddle Collider //
	// =============== //
	class PaddleCollider : public Collider
	{
	protected:
		float _angle;
		float _thickness;

	public:
		// Constructors //
		PaddleCollider();
		PaddleCollider(const PolarCoordinates* position, float angle, float thickness);

		// Getters //
		float get_angle() const;
		float get_thickness() const;

		// Setters //
		void set_angle(float angle);
		void set_thickness(float thickness);

		// Collision Methods //
		Vector3 collide(const PaddleCollider& other) const override;
		Vector3 collide(const CircleCollider& other) const override;
	};
} // namespace my_engine