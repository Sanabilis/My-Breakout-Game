#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

namespace my_engine
{
	// ============ //
	// Camera Class //
	// ============ //
	class Camera
	{
	public:
		// Constants //
		static const float angle_sensitivity;
		static const float move_sensitivity;

		// Camera Type Enum //
		enum struct CameraType
		{
			Perspective,
			Orthographic
		};

	protected:
		Vector3 _eye_position;
		Vector3 _direction;

		float _fov;
		float _width;
		float _height;
		float _near;
		float _far;

		CameraType _type;

	public:
		// Constructors //
		Camera();
		Camera(const Vector3& eye_position, const Vector3& direction, float fov, float width, float height, float near, float far, CameraType type);
		Camera(const Camera& camera);

		// Destructor //
		virtual ~Camera() {}

		// Getters //
		const Vector3& get_eye_position() const;
		const Vector3& get_direction() const;
		float get_fov() const;
		float get_width() const;
		float get_height() const;
		float get_aspect() const;
		float get_near() const;
		float get_far() const;
		CameraType get_type() const;

		virtual Matrix4 get_projection() const;
		Matrix4 get_view() const;
		Vector3 get_right() const;
		Vector3 get_up() const;

		// Setters //
		virtual void set_eye_position(const Vector3& eye_position);
		virtual void set_direction(const Vector3& direction);
		void set_fov(float fov);
		void set_width(float width);
		void set_height(float height);
		void set_near(float near);
		void set_far(float far);

		// Set Projection parameters //
		void set_perspective(float fov, float width, float height, float near, float far);
		void set_orthographic(float left, float right, float bottom, float top, float near, float far);

		// Perspective Projection Matrix //
		static Matrix4 perspective(float fov, float aspect, float near, float far);

		// Orthographic Projection Matrix //
		static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static Vector2 orthographic_boundaries(float fov, float distance, float aspect);

		// View Matrix //
		static Matrix4 look_at(const Vector3& position, const Vector3& direction);
	};
} // namespace my_engine