#include "./constants.hpp"

namespace my_engine
{
	// Degrees to Radians Conversion //
	float to_rad(float degrees)
	{
		return degrees * PI / 180.f;
	}


	// Radians ro Degrees Conversion //
	float to_deg(float radians)
	{
		return radians * 180.f / PI;
	}
} // namespace my_engine