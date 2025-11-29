#pragma once

#include "./paddle_collider.hpp"
#include "./circle_collider.hpp"

namespace my_engine
{
	// =============== //
	// Paddle Collider //
	// =============== //

	// Constructors //
	PaddleCollider::PaddleCollider() : Collider(), _angle(my_engine::PI / 4.0f), _thickness(0.15f) {}
	PaddleCollider::PaddleCollider(const PolarCoordinates* position, float angle, float thickness) : Collider(position), _angle(angle), _thickness(thickness) {}


	// Getters //
	float PaddleCollider::get_angle() const
	{
		return _angle;
	}

	float PaddleCollider::get_thickness() const
	{
		return _thickness;
	}


	// Setters //
	void PaddleCollider::set_angle(float angle)
	{
		_angle = angle;
	}

	void PaddleCollider::set_thickness(float thickness)
	{
		_thickness = thickness;
	}


	// Collision Methods //
	Vector3 PaddleCollider::collide(const PaddleCollider& other) const
	{
		return Vector3(0.0f);
	}

	Vector3 PaddleCollider::collide(const CircleCollider& other) const
	{
		return -other.collide(*this);
	}
};