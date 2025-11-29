#include "./scene_paddle_physics_object.hpp"
#include "./../buffers/model_buffer.hpp"

namespace my_engine
{
	// Constructors //
	ScenePaddlePhysicsObject::ScenePaddlePhysicsObject
	(
		const Vector3& position, float scale, const Mesh& mesh, const Material& material, GLuint texture,
		const Vector3& direction, float velocity, float bounce_factor, float angle, float thickness) :
		ScenePhysicsObject(Vector3(0.0f), Vector3(scale), Quaternion(), mesh, material, texture, direction, velocity, bounce_factor
	)
	{
		Vector3 pos = position;
		float angle_offset = 0.0f;

		if (!pos.is_zero())
		{
			angle_offset = PolarCoordinates(position).get_angle();
		}
		else
		{
			pos = Vector3::RIGHT;
		}

		_physics.set_position(pos.normalized() * scale * 0.5f);
		_rotation = Quaternion(angle / 2.0f - angle_offset, Vector3::UP);
		_paddle_collider = PaddleCollider(&_physics.get_position(), angle, thickness * scale);
	}


	// Getters //
	const PaddleCollider& ScenePaddlePhysicsObject::get_collider() const
	{
		return _paddle_collider;
	}

	float ScenePaddlePhysicsObject::get_angle() const
	{
		return _paddle_collider.get_angle();
	}

	float ScenePaddlePhysicsObject::get_thickness() const
	{
		return _paddle_collider.get_thickness();
	}

	float ScenePaddlePhysicsObject::get_angular_velocity() const
	{
		return _angular_velocity;
	}


	// Setters //
	void ScenePaddlePhysicsObject::set_position(const Vector3& position)
	{
		Vector3 pos = position;
		float angle_offset = 0.0f;

		if (!pos.is_zero())
		{
			angle_offset = PolarCoordinates(position).get_angle();
		}
		else
		{
			pos = Vector3::RIGHT;
		}

		_physics.set_position(pos.normalized() * _scale.x() * 0.5f);
		_rotation = Quaternion(_paddle_collider.get_angle() / 2.0f - angle_offset, Vector3::UP);
		_buffer->update_model_buffer();
	}

	void ScenePaddlePhysicsObject::set_angle(float angle)
	{
		_paddle_collider.set_angle(angle);
	}

	void ScenePaddlePhysicsObject::set_thickness(float thickness)
	{
		_paddle_collider.set_thickness(thickness);
	}


	// Collision Methods //
	void ScenePaddlePhysicsObject::on_collision() {}


	// Rotate the Paddle //
	void ScenePaddlePhysicsObject::rotate(float angle, float delta)
	{
		Vector3 old = _physics.get_cartesian_position();
		Quaternion rotation(angle * delta, Vector3::UP);

		_physics.set_position(rotation.rotate(old).normalized() * _scale.x() * 0.5f);
		_rotation = Quaternion(_paddle_collider.get_angle() / 2.0f - _physics.get_position().get_angle() - angle * delta, Vector3::UP);
		_buffer->update_model_buffer();

		Quaternion rotation_velocity(angle, Vector3::UP);
		Vector3 old_normalized = old.normalized();
		_angular_velocity = angle * _physics.get_position().get_radius();
	}


	// Scene Methods //
	void ScenePaddlePhysicsObject::start() {}
	void ScenePaddlePhysicsObject::update(float delta) {}
	void ScenePaddlePhysicsObject::late_update(float delta) {}
	void ScenePaddlePhysicsObject::physics_update(float fixed_delta) {}
}