#pragma once

#include "./camera.hpp"

namespace my_engine
{
	// ==================== //
	// Preview Camera Class //
	// ==================== //
	class PreviewCamera : public Camera
	{
	protected:
		float _yaw;
		float _pitch;
		float _distance;
		Vector3 _center;

	public:
		// Constructors //
		PreviewCamera();
		PreviewCamera(const Vector3& eye_position, const Vector3& dir, float fov, float width, float height, float near, float far, CameraType type);
		PreviewCamera(float yaw, float pitch, float distance, float fov, float width, float height, float near, float far, CameraType type);
		PreviewCamera(const Camera& c);

		// Getters //
		float get_yaw() const;
		float get_pitch() const;
		float get_distance() const;
		const Vector3& get_center() const;
		Matrix4 get_projection() const override;

		// Setters //
		void set_eye_position(const Vector3& eye_position) override;
		void set_direction(const Vector3& direction) override;
		void set_yaw(float yaw);
		void set_pitch(float pitch);
		void set_distance(float distance);
		void set_center(const Vector3& center);

		// Update Methods //
		void update_base_camera();
		void update_sub_camera();
	};
} // namespace my_engine