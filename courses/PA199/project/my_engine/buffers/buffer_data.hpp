#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

namespace my_engine
{
	// ===================== //
	// Matrix Data Structure //
	// ===================== //
	struct MatrixData
	{
		// Structure to Store Data about Matrices (Projection, View, Model, ...)
		float xx = 1.f, xy = 0.f, xz = 0.f, xw = 0.f; // First Row
		float yx = 0.f, yy = 1.f, yz = 0.f, yw = 0.f; // Second Row
		float zx = 0.f, zy = 0.f, zz = 1.f, zw = 0.f; // Third Row
		float wx = 0.f, wy = 0.f, wz = 0.f, ww = 1.f; // Fourth Row

		// Constructors //
		MatrixData() = default;
		MatrixData(const Matrix4& m);
	};
} // namespace my_engine