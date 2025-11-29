#include "./scene_preview_camera_object.hpp"
#include "./../buffers/camera_buffer.hpp"

namespace my_engine
{
	// Constructors //
	ScenePreviewCameraObject::ScenePreviewCameraObject() : SceneCameraObject()
	{

	}

	ScenePreviewCameraObject::ScenePreviewCameraObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const PreviewCamera& camera)
	{
		_position = position;
		_scale = scale;
		_rotation = rotation;

		_camera = std::make_unique<PreviewCamera>(camera);
	}


	// Getters //
	float ScenePreviewCameraObject::get_yaw() const
	{
		return static_cast<PreviewCamera*>(_camera.get())->get_yaw();
	}

	float ScenePreviewCameraObject::get_pitch() const
	{
		return static_cast<PreviewCamera*>(_camera.get())->get_pitch();
	}

	float ScenePreviewCameraObject::get_distance() const
	{
		return static_cast<PreviewCamera*>(_camera.get())->get_distance();
	}

	const Vector3& ScenePreviewCameraObject::get_center() const
	{
		return static_cast<PreviewCamera*>(_camera.get())->get_center();
	}


	// Setters //
	void ScenePreviewCameraObject::set_yaw(float yaw)
	{
		static_cast<PreviewCamera*>(_camera.get())->set_yaw(yaw);
		_buffer->update_view_buffer();
	}

	void ScenePreviewCameraObject::set_pitch(float pitch)
	{
		static_cast<PreviewCamera*>(_camera.get())->set_pitch(pitch);
		_buffer->update_view_buffer();
	}

	void ScenePreviewCameraObject::set_distance(float distance)
	{
		static_cast<PreviewCamera*>(_camera.get())->set_distance(distance);
		_buffer->update_buffer();
	}

	void ScenePreviewCameraObject::set_center(const Vector3& center)
	{
		static_cast<PreviewCamera*>(_camera.get())->set_center(center);
		_buffer->update_buffer();
	}


	// Scene Methods //
	void ScenePreviewCameraObject::start() {}
	void ScenePreviewCameraObject::update(float delta) {}
	void ScenePreviewCameraObject::late_update(float delta) {}
	void ScenePreviewCameraObject::physics_update(float fixed_delta) {}
}