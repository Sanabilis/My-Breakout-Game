#pragma once

#include "./scene_physics_object.hpp"
#include "./../collision/collider.hpp"

namespace my_engine
{
	class ScenePaddlePhysicsObject;

	class SceneBallPhysicsObject : public ScenePhysicsObject
	{
	protected:
		CircleCollider _circle_collider;

	public:
		// Constructors //
		SceneBallPhysicsObject
		(
			const Vector3& position, const Vector3& scale, const Quaternion& rotation,
			const Mesh& mesh, const Material& material, GLuint texture,
			const Vector3& direction, float velocity, float bounce_factor, float radius
		);

		// Getters //
		const CircleCollider& get_collider() const;
		float get_radius() const;

		// Setters //
		void set_radius(float radius);

		// Collision Methods //
		bool collide(ScenePaddlePhysicsObject& other);
		virtual void on_collision() override;

		// Scene Methods //
		void start() override;
		void update(float delta) override;
		void late_update(float delta) override;
		void physics_update(float fixed_delta) override;
	};
}