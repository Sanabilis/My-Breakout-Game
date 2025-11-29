#pragma once

#include "./scene_model_object.hpp"
#include "./../physics/physics_object.hpp"

namespace my_engine
{
	class ScenePhysicsObject : public SceneModelObject
	{
	protected:
		PhysicsObject _physics;
		bool _collide = true;
		
	public:
		// Constructors //
		ScenePhysicsObject();
		ScenePhysicsObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
						   const Mesh& mesh, const Material& material, GLuint texture,
						   const Vector3& direction, float velocity, float bounce_factor);

		// Getters //
		PolarCoordinates get_polar_coordinates() const;
		const Vector3& get_direction() const;
		float get_velocity() const;
		float get_bounce_factor() const;
		bool get_collide() const;

		// Setters //
		void set_position(const Vector3& position) override;
		void set_direction(const Vector3& direction);
		void set_velocity(float velocity);
		void set_bounce_factor(float bounce_factor);
		void set_collide(bool collide);

		// Physics Methods //
		virtual void move(float delta);
		virtual void bounce(const Vector3& normal);
		virtual void on_collision() = 0;

		// Scene Methods //
		void start() override;
		void update(float delta) override;
		void late_update(float delta) override;
		void physics_update(float fixed_delta) override;
	};
}