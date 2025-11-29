#pragma once

#include "./buffer_data.hpp"

namespace my_engine
{
	// ================= //
	// Matrix Data Class //
	// ================= //
	
	// Constructors //
	MatrixData::MatrixData(const Matrix4& m)
	{
		xx = m[0][0];
		xy = m[0][1];
		xz = m[0][2];
		xw = m[0][3];

		yx = m[1][0];
		yy = m[1][1];
		yz = m[1][2];
		yw = m[1][3];

		zx = m[2][0];
		zy = m[2][1];
		zz = m[2][2];
		zw = m[2][3];

		wx = m[3][0];
		wy = m[3][1];
		wz = m[3][2];
		ww = m[3][3];
	}
} // namespace my_engine