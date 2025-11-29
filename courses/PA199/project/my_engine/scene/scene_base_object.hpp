#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

namespace my_engine
{
	// ======================= //
	// Base Scene Object Class //
	// ======================= //
	class SceneObject
	{
	protected:
		Vector3 _position;
		Vector3 _scale;
		Quaternion _rotation;

		bool _destroy = false;

	public:
		SceneObject();
		SceneObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation);

		// Destructor //
		virtual ~SceneObject() {}

		// Getters //
		Vector3 get_position() const;
		Vector3 get_scale() const;
		Quaternion get_rotation() const;
		virtual Matrix4 get_transformation_matrix() const;

		// Set the Object to Destroy It //
		virtual bool destroy() const;
		virtual bool destroy_on_victory() const;

		// Setters //
		virtual void set_position(const Vector3& position);
		virtual void set_scale(const Vector3& scale);
		virtual void set_rotation(const Quaternion& rotation);

		// Scene Methods //
		virtual void start() = 0;
		virtual void update(float delta) = 0;
		virtual void late_update(float delta) = 0;
		virtual void physics_update(float fixed_delta) = 0;
	};
}