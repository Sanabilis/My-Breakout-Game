#pragma once

#include <cmath>

namespace my_engine
{
	const float PI = std::atan(1.0f) * 4.0f;
	const float GRAVITY_CONSTANT = 9.81f;

	// Degrees to Radians Conversion //
	float to_rad(float degrees);

	// Radians to Degrees Conversion //
	float to_deg(float radians);
} // namespace my_engine