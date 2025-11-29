#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

namespace my_engine
{
	class CircleCollider;
	class PaddleCollider;

	// ============= //
	// Base Collider //
	// ============= //
	class Collider
	{
	protected:
		const PolarCoordinates* _position;

	public:
		// Constructors //
		Collider();
		Collider(const PolarCoordinates* position);

		// Destructor //
		virtual ~Collider() {}

		// Getters //
		const PolarCoordinates& get_position() const;

		// Collision Methods //
		virtual Vector3 collide(const CircleCollider& other) const = 0;
		virtual Vector3 collide(const PaddleCollider& other) const = 0;
	};
} // namespace my_engine