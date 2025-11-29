#pragma once

#include "./base_collider.hpp"

namespace my_engine
{
	// ============= //
	// Base Collider //
	// ============= //
	
	// Constructors //
	Collider::Collider() : _position(nullptr) {}
	Collider::Collider(const PolarCoordinates* position) : _position(position) {}


	// Getters //
	const PolarCoordinates& Collider::get_position() const
	{
		return *_position;
	}
};