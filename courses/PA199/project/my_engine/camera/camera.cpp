#include "./camera.hpp"

namespace my_engine
{
	// ============ //
	// Camera Class //
	// ============ //

	// Constants //
	const float Camera::angle_sensitivity = 0.005f;
	const float Camera::move_sensitivity = 0.008f;

	// Constructors //
	Camera::Camera()
	{
		_eye_position = Vector3::ZERO;
		_direction = Vector3::FORWARD;
		
		_fov = PI / 3.0f;
		_width = 1920.0f;
		_height = 1080.0f;
		_near = 0.01f;
		_far = 1000.0f;

		_type = CameraType::Perspective;
	}

	Camera::Camera(const Vector3& eye_position, const Vector3& dir, float fov, float width, float height, float near, float far, CameraType type)
	{
		_eye_position = eye_position;
		_direction = dir.normalized();
		
		_fov = fov;
		_width = width;
		_height = height;
		_near = near;
		_far = far;

		_type = type;
	}

	Camera::Camera(const Camera& camera)
	{
		_eye_position = camera._eye_position;
		_direction = camera._direction;
		
		_fov = camera._fov;
		_width = camera._width;
		_height = camera._height;
		_near = camera._near;
		_far = camera._far;

		_type = camera._type;
	}


	// Getters //
	const Vector3& Camera::get_eye_position() const
	{
		return _eye_position;
	}

	const Vector3& Camera::get_direction() const
	{
		return _direction;
	}

	float Camera::get_fov() const
	{
		return _fov;
	}

	float Camera::get_width() const
	{
		return _width;
	}

	float Camera::get_height() const
	{
		return _height;
	}

	float Camera::get_aspect() const
	{
		return _width / _height;
	}

	float Camera::get_near() const
	{
		return _near;
	}

	float Camera::get_far() const
	{
		return _far;
	}

	Camera::CameraType Camera::get_type() const
	{
		return _type;
	}

	Matrix4 Camera::get_projection() const
	{
		switch (_type)
		{
		case CameraType::Perspective:
			return perspective(_fov, _width / _height, _near, _far);
			break;
		case CameraType::Orthographic:
			return orthographic(-_width / 2.0f, _width / 2.0f, -_height / 2.0f, _height / 2.0f, _near, _far);
			break;
		}
	}

	Matrix4 Camera::get_view() const
	{
		return look_at(_eye_position, _eye_position + _direction);
	}

	Vector3 Camera::get_right() const
	{
		if (_direction == Vector3::UP || _direction == Vector3::DOWN)
		{
			return Vector3::RIGHT;
		}

		return Vector3::UP.cross(_direction).normalized();
	}

	Vector3 Camera::get_up() const
	{
		Vector3 right = get_right();
		return _direction.cross(right).normalized();
	}


	// Setters //
	void Camera::set_eye_position(const Vector3& eye_position)
	{
		_eye_position = eye_position;
	}

	void Camera::set_direction(const Vector3& direction)
	{
		_direction = direction.normalized();
	}

	void Camera::set_fov(float fov)
	{
		_fov = fov;
	}

	void Camera::set_width(float width)
	{
		_width = width;
	}

	void Camera::set_height(float height)
	{
		_height = height;
	}

	void Camera::set_near(float near)
	{
		_near = near;
	}

	void Camera::set_far(float far)
	{
		_far = far;
	}


	// Set Projection parameters //
	void Camera::set_perspective(float fov, float width, float height, float near, float far)
	{
		_fov = fov;
		_width = width;
		_height = height;
		_near = near;
		_far = far;

		_type = CameraType::Perspective;
	}

	void Camera::set_orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		_width = right - left;
		_height = top - bottom;
		_near = near;
		_far = far;

		_type = CameraType::Orthographic;
	}


	// Perspective Projection Matrix //
	Matrix4 Camera::perspective(float fov, float aspect, float near, float far)
	{
		float fv = std::tan(fov / 2.f);

		return Matrix4
		({
			1.f / (fv*aspect), 0.f,		  0.f,							0.f,
			0.f,			   1.f / fv,  0.f,							0.f,
			0.f,			   0.f,		 -(far+near) / (far-near),	   -1.f,
			0.f,			   0.f,		 -(2.f*far*near) / (far-near),	0.f
		});
	}


	// Orthographic Projection Matrix //
	Matrix4 Camera::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		return Matrix4
		({
			2.f / (right-left), 0.f,				 0.f,					  0.f,
			0.f,				2.f / (top-bottom),  0.f,					  0.f,
			0.f,				0.f,				-2.f / (far-near),		  0.f,
			0.f,				0.f,				-(far+near) / (far-near), 1.f
		});
	}

	Vector2 Camera::orthographic_boundaries(float fov, float distance, float aspect)
	{
		float fov_factor = std::tan(fov / 2.f);

		return Vector2(fov_factor * distance * aspect, fov_factor * distance);
	}


	// View Matrix //
	Matrix4 Camera::look_at(const Vector3& position, const Vector3& point)
	{
		Vector3 dir = -(point - position).normalized();
		Vector3 right = Vector3::UP.cross(dir).normalized();
		Vector3 up = dir.cross(right).normalized();

		if (dir.is_zero())
		{
			dir = Vector3::FORWARD;
		}

		if (dir == Vector3::UP || dir == Vector3::DOWN)
		{
			right = Vector3::RIGHT;
			up = dir.cross(right).normalized();
		}

		Matrix4 view = Matrix4(Matrix3({ right, up, dir }), 1.f) * Matrix4::translate_3d(-position);
		return view.transpose();
	}
} // namespace my_engine