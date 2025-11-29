#pragma once

#include "./scene_camera_object.hpp"
#include "./../camera/preview_camera.hpp"

namespace my_engine
{
	class CameraBuffer;

	// ===================================== //
	// Scene Object Class for Preview Camera //
	// ===================================== //
	class ScenePreviewCameraObject : public SceneCameraObject
	{
	public:
		// Constructors //
		ScenePreviewCameraObject();
		ScenePreviewCameraObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
			const PreviewCamera& camera);

		// Getters //
		float get_yaw() const;
		float get_pitch() const;
		float get_distance() const;
		const Vector3& get_center() const;

		// Setters //
		void set_yaw(float yaw);
		void set_pitch(float pitch);
		void set_distance(float distance);
		void set_center(const Vector3& center);

		// Scene Methods //
		virtual void start() override;
		virtual void update(float delta) override;
		virtual void late_update(float delta) override;
		virtual void physics_update(float fixed_delta) override;
	};
}