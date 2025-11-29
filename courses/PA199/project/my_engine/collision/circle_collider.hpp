#pragma once

#include "./base_collider.hpp"

namespace my_engine
{
	// =============== //
	// Circle Collider //
	// =============== //
	class CircleCollider : public Collider
	{
	protected:
		float _radius;

	public:
		// Constructors //
		CircleCollider();
		CircleCollider(const PolarCoordinates* position, float radius);

		// Getters //
		float get_radius() const;

		// Setters //
		void set_radius(float radius);

		// Collision Methods //
		Vector3 collide(const CircleCollider& other) const override;
		Vector3 collide(const PaddleCollider& other) const override;
	};
} // namespace my_engine