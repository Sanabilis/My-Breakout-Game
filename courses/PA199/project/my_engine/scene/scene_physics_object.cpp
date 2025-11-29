#include "./scene_physics_object.hpp"
#include "./../buffers/model_buffer.hpp"

namespace my_engine
{
	// Constructors //
	ScenePhysicsObject::ScenePhysicsObject() : SceneModelObject()
	{
		_physics.set_position(_position);
	}

	ScenePhysicsObject::ScenePhysicsObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
										   const Mesh& mesh, const Material& material, GLuint texture,
										   const Vector3& direction, float velocity, float bounce_factor) :
		SceneModelObject(position, scale, rotation, mesh, material, texture)
	{
		_physics.set_position(position);
		_physics.set_direction(direction);
		_physics.set_velocity(velocity);
		_physics.set_bounce_factor(bounce_factor);
	}


	// Getters //
	PolarCoordinates ScenePhysicsObject::get_polar_coordinates() const
	{
		return PolarCoordinates(_physics.get_position());
	}

	const Vector3& ScenePhysicsObject::get_direction() const
	{
		return _physics.get_direction();
	}

	float ScenePhysicsObject::get_velocity() const
	{
		return _physics.get_velocity();
	}

	float ScenePhysicsObject::get_bounce_factor() const
	{
		return _physics.get_bounce_factor();
	}

	bool ScenePhysicsObject::get_collide() const
	{
		return _collide;
	}


	// Setters //
	void ScenePhysicsObject::set_position(const Vector3& position)
	{
		_position = position;
		_physics.set_position(position);
		_buffer->update_model_buffer();
	}

	void ScenePhysicsObject::set_direction(const Vector3& direction)
	{
		_physics.set_direction(direction);
	}

	void ScenePhysicsObject::set_velocity(float velocity)
	{
		_physics.set_velocity(velocity);
	}

	void ScenePhysicsObject::set_bounce_factor(float bounce_factor)
	{
		_physics.set_bounce_factor(bounce_factor);
	}

	void ScenePhysicsObject::set_collide(bool collide)
	{
		_collide = collide;
	}


	// Movement Methods //
	void ScenePhysicsObject::move(float delta)
	{
		_physics.move(delta);
		_position = _physics.get_cartesian_position();
		_buffer->update_model_buffer();
	}

	void ScenePhysicsObject::bounce(const Vector3& normal)
	{
		_physics.bounce(normal);
	}


	// Scene Methods //
	void ScenePhysicsObject::start() {}
	void ScenePhysicsObject::update(float delta) {}
	void ScenePhysicsObject::late_update(float delta) {}

	void ScenePhysicsObject::physics_update(float fixed_delta)
	{
		move(fixed_delta);
	}
}