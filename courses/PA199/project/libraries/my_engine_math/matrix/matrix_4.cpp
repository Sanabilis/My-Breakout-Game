#include "./matrix_4.hpp"

namespace my_engine
{
	// ================ //
	// 4×4 Matrix Class //
	// ================ //

	// Constants //
	const Matrix4 Matrix4::IDENTITY = Matrix4(1.f);
	const Matrix4 Matrix4::ZERO = Matrix4();


	// Constructors //
	Matrix4::Matrix4() : Matrix<4>() {}

	Matrix4::Matrix4(float a) : Matrix<4>(a) {}

	Matrix4::Matrix4(const Matrix<4>& m) : Matrix<4>(m) {}

	Matrix4::Matrix4(const std::array<Vector<4>, 4>& m) : Matrix<4>(m) {}

	Matrix4::Matrix4(const std::array<std::array<float, 4>, 4>& m) : Matrix<4>(m) {}

	Matrix4::Matrix4(const Matrix3& m, float f)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i < 3 && j < 3)
				{
					_rows[i][j] = m[i][j];
				}
				else if (i != j)
				{
					_rows[i][j] = 0.f;
				}
				else
				{
					_rows[i][j] = f;
				}
			}
		}
	}


	// Static 3D Transformation Matrices in Homogeneous Coordinates //
	Matrix4 Matrix4::translate_3d(const Vector3& direction)
	{
		return Matrix4
		({
			1.f, 0.f, 0.f, direction.x(),
			0.f, 1.f, 0.f, direction.y(),
			0.f, 0.f, 1.f, direction.z(),
			0.f, 0.f, 0.f, 1.f
		});
	}

	Matrix4 Matrix4::rotate_3d(float radians, const Vector3& axis)
	{
		return Matrix4(Matrix3::rotate_3d(radians, axis), 1.f);
	}

	Matrix4 Matrix4::scale_3d(const Vector3& axis)
	{
		return Matrix4(Matrix3::scale_3d(axis), 1.f);
	}
} // namespace my_engine