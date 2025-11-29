#include "paddle.hpp"

namespace my_engine
{
	Paddle::Paddle
	(
		const Vector3& position, float scale, const Mesh& mesh, const Material& material, GLuint texture,
		const Vector3& direction, float velocity, float bounce_factor, float angle, float thickness,
		float rotation_acceleration, float rotation_deceleration, float max_rotation_angle
	) : ScenePaddlePhysicsObject(position, scale, mesh, material, texture, direction, velocity, bounce_factor, angle, thickness),
		_rotation_acceleration(rotation_acceleration), _rotation_deceleration(rotation_deceleration), _max_rotation_angle(max_rotation_angle)
	{
		_diffuse_texture = MyEngine::get_texture("rock_diffuse");
		_normal_texture = MyEngine::get_texture("rock_normal");
	}


	void Paddle::start()
	{
		ScenePaddlePhysicsObject::start();
	}

	void Paddle::update(float delta)
	{
		ScenePaddlePhysicsObject::update(delta);

		if (MyEngine::my_engine.right_pressed && !MyEngine::my_engine.left_pressed)
		{
			_rotation_angle = std::min(_rotation_angle + _rotation_acceleration * delta, _max_rotation_angle);
		}
		else if (MyEngine::my_engine.left_pressed && !MyEngine::my_engine.right_pressed)
		{
			_rotation_angle = std::max(_rotation_angle - _rotation_acceleration * delta, -_max_rotation_angle);
		}
		else if (_rotation_angle > 0.0f)
		{
			_rotation_angle = std::max(_rotation_angle - _rotation_deceleration * delta, 0.0f);
		}
		else if (_rotation_angle < 0.0f)
		{
			_rotation_angle = std::min(_rotation_angle + _rotation_deceleration * delta, 0.0f);
		}
	}

	void Paddle::physics_update(float fixed_delta)
	{
		ScenePaddlePhysicsObject::physics_update(fixed_delta);

		rotate(_rotation_angle, fixed_delta);
	}

	void Paddle::late_update(float delta)
	{
		ScenePaddlePhysicsObject::late_update(delta);
	}


	void Paddle::instantiate
	(
		const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		float rotation_acceleration, float rotation_deceleration, float max_rotation_angle
	)
	{
		float s = (scale.x() + scale.y() + scale.z()) / 3.0f;
		float width = 0.2f;
		float height = 0.5f;
		float angle = PI / 6.0f;

		Paddle* ptr = new Paddle
		(
			position, s, Mesh::paddle(32, angle, width / s, height / s),
			Material::DEFAULT_MATERIAL, 0, Vector3::FORWARD, 0.0f, 0.0f, angle, width / s,
			rotation_acceleration, rotation_deceleration, max_rotation_angle
		);

		MyEngine::instantiate(ptr, SceneObjectElement::SceneObjectType::PaddlePhysicsObject);
	}
}