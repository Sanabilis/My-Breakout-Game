#include "./matrix_3.hpp"

namespace my_engine
{
	// ================ //
	// 3×3 Matrix Class //
	// ================ //

	// Constants //
	const Matrix3 Matrix3::IDENTITY = Matrix3(1.f);
	const Matrix3 Matrix3::ZERO = Matrix3();


	// Constructors //
	Matrix3::Matrix3() : Matrix<3>() {}

	Matrix3::Matrix3(float a) : Matrix<3>(a) {}

	Matrix3::Matrix3(const Matrix<3>& m) : Matrix<3>(m) {}

	Matrix3::Matrix3(const std::array<Vector<3>, 3>& m) : Matrix<3>(m) {}

	Matrix3::Matrix3(const std::array<std::array<float, 3>, 3>& m) : Matrix<3>(m) {}

	Matrix3::Matrix3(const Matrix2& m, float f)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i < 2 && j < 2)
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


	// Matrix Orthonormalization //
	Matrix<3> Matrix3::orthonormalized() const
	{
		Vector3 x_basis = Vector3(_rows[0][0], _rows[1][0], _rows[2][0]).normalized();
		Vector3 y_basis = Vector3(_rows[0][1], _rows[1][1], _rows[2][1]).normalized();
		Vector3 z_basis = Vector3(_rows[0][2], _rows[1][2], _rows[2][2]).normalized();

		y_basis = z_basis.cross(x_basis).normalized();
		z_basis = x_basis.cross(y_basis).normalized();

		return Matrix<3>({ x_basis[0], y_basis[0], z_basis[0], x_basis[1], y_basis[1], z_basis[1], x_basis[2], y_basis[2], z_basis[2] });
	}


	// Matrix Deorthonormalization //
	Matrix<3> Matrix3::deorthonormalized() const
	{
		return this->orthonormalized();
	}


	// Static 2D Transformation Matrices in Homogeneous Coordinates //
	Matrix3 Matrix3::translate_2d(const Vector2& direction)
	{
		return Matrix3
		({
			1.f, 0.f, direction.x(),
			0.f, 1.f, direction.y(),
			0.f, 0.f, 1.f
		});
	}

	Matrix3 Matrix3::rotate_2d(float radians)
	{
		return Matrix3(Matrix2::rotate_2d(radians), 1.f);
	}

	Matrix3 Matrix3::scale_2d(const Vector2& axis)
	{
		return Matrix3(Matrix2::scale_2d(axis), 1.f);
	}

	Matrix3 Matrix3::shear_2d(const Vector2& axis)
	{
		return Matrix3(Matrix2::shear_2d(axis), 1.f);
	}


	// Static 3D Transformation Matrices //
	Matrix3 Matrix3::rotate_3d(float radians, const Vector3& axis)
	{
		float cos = std::cos(radians);
		float sin = std::sin(radians);
		float inv_cos = 1 - cos;
		float inv_sin = 1 - sin;

		Vector3 unit = axis.normalized();
		float a_x = unit.x();
		float a_y = unit.y();
		float a_z = unit.z();

		return Matrix3
		({
			inv_cos * a_x * a_x + cos,			inv_cos * a_x * a_y - a_z * sin,	inv_cos * a_x * a_z + a_y * sin,
			a_x * a_y * inv_cos + a_z * sin,	inv_cos * a_y * a_y + cos,			inv_cos * a_y * a_z - a_x * sin,
			a_z * a_x * inv_cos - a_y * sin,	inv_cos * a_y * a_z + a_x * sin,	inv_cos * a_z * a_z + cos
		});
	}

	Matrix3 Matrix3::scale_3d(const Vector3& axis)
	{
		return Matrix3({ axis.x(), 0.f, 0.f, 0.f, axis.y(), 0.f, 0.f, 0.f, axis.z() });
	}
} // namespace my_engine