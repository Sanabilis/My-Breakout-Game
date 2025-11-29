#include "./matrix_2.hpp"

namespace my_engine
{
	// ================ //
	// 2×2 Matrix Class //
	// ================ //

	// Constants //
	const Matrix2 Matrix2::IDENTITY = Matrix2(1.f);
	const Matrix2 Matrix2::ZERO = Matrix2();


	// Constructors //
	Matrix2::Matrix2() : Matrix<2>() {}

	Matrix2::Matrix2(float a) : Matrix<2>(a) {}

	Matrix2::Matrix2(const Matrix<2>& m) : Matrix<2>(m) {}

	Matrix2::Matrix2(const std::array<Vector<2>, 2>& m) : Matrix<2>(m) {}

	Matrix2::Matrix2(const std::array<std::array<float, 2>, 2>& m) : Matrix<2>(m) {}



	// Matrix Orthonormalization //
	Matrix<2> Matrix2::orthonormalized() const
	{
		Vector2 x_basis = Vector2(_rows[0][0], _rows[1][0]).normalized();
		Vector2 y_basis = Vector2(_rows[0][1], _rows[1][1]).normalized();

		y_basis = Vector2(-x_basis.y(), x_basis.x()).normalized();

		return Matrix<2>({ x_basis.x(), y_basis.x(), x_basis.y(), y_basis.y() });
	}


	// Matrix Deorthonormalization //
	Matrix<2> Matrix2::deorthonormalized() const
	{
		return this->orthonormalized();
	}


	// Static 2D Transformation Matrices //
	Matrix2 Matrix2::rotate_2d(float radians)
	{
		return Matrix2
		({
			std::cos(radians), -std::sin(radians),
			std::sin(radians), std::cos(radians)
		});
	}

	Matrix2 Matrix2::scale_2d(const Vector2& axis)
	{
		return Matrix2({ axis.x(), 0.f, 0.f, axis.y() });
	}

	Matrix2 Matrix2::shear_2d(const Vector2& axis)
	{
		return Matrix2({ 1.f, axis.y(), axis.x(), 1.f });
	}
} // namespace my_engine