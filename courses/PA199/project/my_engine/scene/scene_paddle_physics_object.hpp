#pragma once

#include "./scene_physics_object.hpp"
#include "./../collision/collider.hpp"

namespace my_engine
{
	class SceneBallPhysicsObject;

	class ScenePaddlePhysicsObject : public ScenePhysicsObject
	{
	protected:
		PaddleCollider _paddle_collider;
		float _angular_velocity = 0.0f;

	public:
		// Constructors //
		ScenePaddlePhysicsObject
		(
			const Vector3& position, float scale, const Mesh& mesh, const Material& material, GLuint texture,
			const Vector3& direction, float velocity, float bounce_factor, float angle, float thickness
		);

		// Getters //
		const PaddleCollider& get_collider() const;
		float get_angle() const;
		float get_thickness() const;
		float get_angular_velocity() const;

		// Setters //
		void set_position(const Vector3& position) override;
		void set_angle(float angle);
		void set_thickness(float thickness);

		// Collision Methods //
		virtual void on_collision() override;

		// Rotate the Paddle //
		void rotate(float angle, float delta);

		// Scene Methods //
		void start() override;
		void update(float delta) override;
		void late_update(float delta) override;
		void physics_update(float fixed_delta) override;
	};
}