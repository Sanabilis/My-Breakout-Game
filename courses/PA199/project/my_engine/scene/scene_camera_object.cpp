#include "./scene_camera_object.hpp"
#include "./../buffers/camera_buffer.hpp"

namespace my_engine
{
	// ======================= //
	// Scene Class for Cameras //
	// ======================= //

	// Constructors //
	SceneCameraObject::SceneCameraObject() : SceneObject()
	{
		_camera = std::make_unique<Camera>();
	}

	SceneCameraObject::SceneCameraObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const Camera& camera) : SceneObject(position, scale, rotation)
	{
		_camera = std::make_unique<Camera>(camera);
	}


	// Getters //
	Camera& SceneCameraObject::get_camera()
	{
		return *_camera;
	}

	const Camera& SceneCameraObject::get_camera() const
	{
		return *_camera;
	}

	CameraBuffer& SceneCameraObject::get_buffer()
	{
		return *_buffer;
	}

	const CameraBuffer& SceneCameraObject::get_buffer() const
	{
		return *_buffer;
	}

	const Vector3& SceneCameraObject::get_eye_position() const
	{
		return _camera->get_eye_position();
	}

	const Vector3& SceneCameraObject::get_direction() const
	{
		return _camera->get_direction();
	}

	float SceneCameraObject::get_fov() const
	{
		return _camera->get_fov();
	}

	float SceneCameraObject::get_width() const
	{
		return _camera->get_width();
	}

	float SceneCameraObject::get_height() const
	{
		return _camera->get_height();
	}

	float SceneCameraObject::get_aspect() const
	{
		return _camera->get_aspect();
	}

	float SceneCameraObject::get_near() const
	{
		return _camera->get_near();
	}

	float SceneCameraObject::get_far() const
	{
		return _camera->get_far();
	}

	Camera::CameraType SceneCameraObject::get_type() const
	{
		return _camera->get_type();
	}

	bool SceneCameraObject::is_active() const
	{
		return _active;
	}


	// Set Projection parameters //
	Matrix4 SceneCameraObject::get_projection() const
	{
		return _camera->get_projection();
	}

	Matrix4 SceneCameraObject::get_view() const
	{
		return _camera->get_view();
	}

	Vector3 SceneCameraObject::get_right() const
	{
		return _camera->get_right();
	}

	Vector3 SceneCameraObject::get_up() const
	{
		return _camera->get_up();
	}


	// Setters //
	void SceneCameraObject::set_buffer(CameraBuffer* buffer)
	{
		_buffer = buffer;
	}

	void SceneCameraObject::set_eye_position(const Vector3& eye_position)
	{
		_position = eye_position;
		_camera->set_eye_position(eye_position);

		if (_buffer != nullptr && _active)
		{
			_buffer->update_view_buffer();
		}
	}

	void SceneCameraObject::set_direction(const Vector3& direction)
	{
		_camera->set_direction(direction);
		
		if (_buffer != nullptr && _active)
		{
			_buffer->update_view_buffer();
		}
	}

	void SceneCameraObject::set_fov(float fov)
	{
		_camera->set_fov(fov);
		
		if (_buffer != nullptr && _active)
		{
			_buffer->update_projection_buffer();
		}
	}

	void SceneCameraObject::set_width(float width)
	{
		_camera->set_width(width);

		if (_buffer != nullptr && _active)
		{
			_buffer->update_view_buffer();
		}
	}

	void SceneCameraObject::set_height(float height)
	{
		_camera->set_height(height);
		
		if (_buffer != nullptr && _active)
		{
			_buffer->update_projection_buffer();
		}
	}

	void SceneCameraObject::set_near(float near)
	{
		_camera->set_near(near);
		
		if (_buffer != nullptr && _active)
		{
			_buffer->update_projection_buffer();
		}
	}

	void SceneCameraObject::set_far(float far)
	{
		_camera->set_far(far);
		
		if (_buffer != nullptr && _active)
		{
			_buffer->update_projection_buffer();
		}
	}

	void SceneCameraObject::set_active()
	{
		_active = true;

		if (_buffer != nullptr)
		{
			if (_buffer->get_camera() != nullptr)
			{
				_buffer->get_camera()->set_inactive();
			}

			_buffer->switch_camera(this);
		}
	}

	void SceneCameraObject::set_inactive()
	{
		_active = false;

		if (_buffer != nullptr)
		{
			_buffer->switch_camera(nullptr);
		}
	}


	// Set Projection parameters //
	void SceneCameraObject::set_perspective(float fov, float width, float height, float near, float far)
	{
		_camera->set_perspective(fov, width, height, near, far);

		if (_buffer != nullptr && _active)
		{
			_buffer->update_projection_buffer();
		}
	}

	void SceneCameraObject::set_orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		_camera->set_orthographic(left, right, bottom, top, near, far);

		if (_buffer != nullptr && _active)
		{
			_buffer->update_projection_buffer();
		}
	}


	// Scene Methods //
	void SceneCameraObject::start() {}
	void SceneCameraObject::update(float delta) {}
	void SceneCameraObject::late_update(float delta) {}
	void SceneCameraObject::physics_update(float delta) {}
}