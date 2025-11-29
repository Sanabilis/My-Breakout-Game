#include "./scene_ball_physics_object.hpp"
#include "./scene_paddle_physics_object.hpp"
#include "./../buffers/model_buffer.hpp"

namespace my_engine
{
	// Constructors //
	SceneBallPhysicsObject::SceneBallPhysicsObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const Mesh& mesh, const Material& material, GLuint texture,
		const Vector3& direction, float velocity, float bounce_factor, float radius) :
		ScenePhysicsObject(position, scale, rotation, mesh, material, texture, direction, velocity, bounce_factor)
	{
		_circle_collider = CircleCollider(&_physics.get_position(), radius);
	}


	// Getters //
	const CircleCollider& SceneBallPhysicsObject::get_collider() const
	{
		return _circle_collider;
	}

	float SceneBallPhysicsObject::get_radius() const
	{
		return _circle_collider.get_radius();
	}


	// Setters //
	void SceneBallPhysicsObject::set_radius(float radius)
	{
		_circle_collider.set_radius(radius);
	}


	// Collision Methods //
	bool SceneBallPhysicsObject::collide(ScenePaddlePhysicsObject& other)
	{
		Vector3 normal = _circle_collider.collide(other.get_collider());

		if (get_collide() && other.get_collide() && !normal.is_zero() && _physics.get_direction().dot(normal) < 0.0f)
		{
			this->on_collision();
			other.on_collision();
			bounce(normal);

			/*
			Vector2 position = _circle_collider.get_position().cartesian();
			Vector2 paddle_pos = other.get_collider().get_position().cartesian();

			float difference = std::acos(position.normalized().dot(paddle_pos.normalized()));
			float paddle_angle = 0.5f * other.get_collider().get_angle();
			float angular_velocity = other.get_angular_velocity();

			if (difference > paddle_angle && (-paddle_pos.x() * position.y() + paddle_pos.y() * position.x() < 0.0f) == (angular_velocity < 0.0f))
			{
				Vector3 velocity = _physics.get_direction() * _physics.get_velocity() + normal * std::abs(angular_velocity);

				_physics.set_direction(velocity);
			}
			*/

			return true;
		}
		
		return false;
	}

	void SceneBallPhysicsObject::on_collision() {}


	// Scene Methods //
	void SceneBallPhysicsObject::start() {}
	void SceneBallPhysicsObject::update(float delta) {}
	void SceneBallPhysicsObject::late_update(float delta) {}

	void SceneBallPhysicsObject::physics_update(float fixed_delta)
	{
		ScenePhysicsObject::physics_update(fixed_delta);
	}
}