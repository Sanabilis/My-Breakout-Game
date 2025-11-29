#include "./preview_camera.hpp"

namespace my_engine
{
	// ==================== //
	// Preview Camera Class //
	// ==================== //

	// Constructors //
	PreviewCamera::PreviewCamera() : Camera()
	{
		_yaw = 0.0f;
		_pitch = 0.0f;
		_distance = 0.0f;
	}

	PreviewCamera::PreviewCamera(const Vector3& eye_pos, const Vector3& dir, float fov, float width, float height, float near, float far, CameraType type) :
		Camera(eye_pos, dir, fov, width, height, near, far, type)
	{
		update_sub_camera();
	}

	PreviewCamera::PreviewCamera(float yaw, float pitch, float distance, float fov, float width, float height, float near, float far, CameraType type)
	{
		_yaw = yaw;
		_pitch = pitch;
		_distance = distance;

		_fov = fov;
		_width = width;
		_height = height;
		_near = near;
		_far = far;
		_type = type;

		update_base_camera();
	}

	PreviewCamera::PreviewCamera(const Camera& c) : Camera(c)
	{
		update_sub_camera();
	}


	// Getters //
	float PreviewCamera::get_yaw() const
	{
		return _yaw;
	}

	float PreviewCamera::get_pitch() const
	{
		return _pitch;
	}

	float PreviewCamera::get_distance() const
	{
		return _distance;
	}

	const Vector3& PreviewCamera::get_center() const
	{
		return _center;
	}

	Matrix4 PreviewCamera::get_projection() const
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


	// Setters //
	void PreviewCamera::set_eye_position(const Vector3& eye_position)
	{
		Vector3 offset = eye_position - _eye_position;
		_eye_position = eye_position;
		_center += offset;
		update_sub_camera();
	}

	void PreviewCamera::set_direction(const Vector3& direction)
	{
		_direction = direction;
		update_sub_camera();
	}

	void PreviewCamera::set_yaw(float yaw)
	{
		_yaw = yaw;

		while (_yaw > 2.0f * PI)
		{
			_yaw -= 2.0f * PI;
		}

		while (_yaw < 0.f)
		{
			_yaw += 2.0f * PI;
		}

		update_base_camera();
	}

	void PreviewCamera::set_pitch(float pitch)
	{
		_pitch = std::max(std::min(pitch, 89.0f * PI / 180.0f), -89.0f * PI / 180.0f);
		update_base_camera();
	}

	void PreviewCamera::set_distance(float distance)
	{
		_distance = distance;
		update_base_camera();
	}

	void PreviewCamera::set_center(const Vector3& center)
	{
		Vector3 offset = center - _center;
		_center = center;
		_eye_position += offset;
		update_base_camera();
	}


	// Update Methods //
	void PreviewCamera::update_base_camera()
	{
		_eye_position.x() = _distance * std::cos(_pitch) * -std::sin(_yaw);
		_eye_position.y() = _distance * std::sin(_pitch);
		_eye_position.z() = _distance * std::cos(_pitch) *  std::cos(_yaw);
		_eye_position += _center;

		_direction = (_center - _eye_position).normalized();
	}

	void PreviewCamera::update_sub_camera()
	{
		Vector3 dir = _eye_position - _center;

		_distance = std::sqrt(dir.dot(dir));
		_pitch = std::asin(dir.y() / _distance);
		_yaw = std::atan(dir.z() / dir.x()) + PI;
	}
} // namespace my_engine