#pragma once

#include "./scene_base_object.hpp"
#include "./../camera/camera.hpp"

namespace my_engine
{
	class CameraBuffer;

	// ============================== //
	// Scene Object Class for Cameras //
	// ============================== //
	class SceneCameraObject : public SceneObject
	{
	protected:
		CameraBuffer* _buffer = nullptr;

		std::unique_ptr<Camera> _camera;
		bool _active = false;

	public:
		// Constructors //
		SceneCameraObject();
		SceneCameraObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
						  const Camera& camera);

		// Getters //
		Camera& get_camera();
		const Camera& get_camera() const;
		CameraBuffer& get_buffer();
		const CameraBuffer& get_buffer() const;

		const Vector3& get_eye_position() const;
		const Vector3& get_direction() const;
		float get_fov() const;
		float get_width() const;
		float get_height() const;
		float get_aspect() const;
		float get_near() const;
		float get_far() const;
		Matrix4 get_projection() const;
		Matrix4 get_view() const;
		Vector3 get_right() const;
		Vector3 get_up() const;
		Camera::CameraType get_type() const;
		bool is_active() const;

		// Setters //
		void set_buffer(CameraBuffer* buffer);
		void set_eye_position(const Vector3& eye_position);
		void set_direction(const Vector3& direction);
		void set_fov(float fov);
		void set_width(float width);
		void set_height(float height);
		void set_near(float near);
		void set_far(float far);
		void set_active();
		void set_inactive();

		// Set Projection parameters //
		void set_perspective(float fov, float width, float height, float near, float far);
		void set_orthographic(float left, float right, float bottom, float top, float near, float far);

		// Scene Methods //
		virtual void start() override;
		virtual void update(float delta) override;
		virtual void late_update(float delta) override;
		virtual void physics_update(float fixed_delta) override;
	};
}