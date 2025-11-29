#include "./ball.hpp"

namespace my_engine
{
	SceneBallPhysicsObject* Ball::game_ball = nullptr;

	Ball::Ball
	(
		const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const Mesh& mesh, const Material& material, GLuint texture,
		const Vector3& direction, float velocity, float bounce_factor, float radius
	) :
		SceneBallPhysicsObject(position, scale, rotation, mesh, material, texture, direction, velocity, bounce_factor, radius)
	{
		_diffuse_texture = MyEngine::get_texture("fabric_diffuse");
		_normal_texture = MyEngine::get_texture("fabric_normal");
	}

	void Ball::start()
	{
		SceneBallPhysicsObject::start();
	}

	void Ball::update(float delta)
	{
		SceneBallPhysicsObject::update(delta);

		if (_position.magnitude() > 2.5f && MyEngine::my_engine.state == GameState::Running)
		{
			GUILives::lives->operator--();

			if (GUILives::lives->is_zero())
			{
				MyEngine::my_engine.state = GameState::Defeat;
				MyEngine::my_engine.time_factor = 0.0f;
			}
			else
			{
				MyEngine::my_engine.respawn();
			}
		}
	}

	void Ball::physics_update(float fixed_delta)
	{
		if (MyEngine::my_engine.space_pressed)
		{
			set_velocity(std::min(get_velocity(), 1.0f));

			Vector3 scale = get_scale();
			float radius = 0.5f * (scale.x() + scale.y() + scale.z()) / 3.0f;

			Vector3 rotation_axis = Vector3::UP.cross(get_direction());
			float rotation_angle = get_velocity() * fixed_delta / radius;

			Quaternion current_rotation = get_rotation();
			Quaternion rotation(rotation_angle, rotation_axis);

			set_rotation(rotation * current_rotation);

			SceneBallPhysicsObject::physics_update(fixed_delta);
		}
	}

	void Ball::late_update(float delta)
	{
		SceneBallPhysicsObject::late_update(delta);
	}


	void Ball::instantiate(const Vector3& position, const Vector3& scale, const Quaternion& rotation)
	{
		float direction_randomness = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) - 0.5f;
		Vector3 new_direction = Quaternion(0.25f * direction_randomness * PI, Vector3::UP).rotate(-position.normalized());
		float s = (scale.x() + scale.y() + scale.z()) / 3.0f;

		Material material;

		material.sr = 0.0f, material.sg = 0.0f, material.sb = 0.0f;

		Ball* ptr = new Ball
		(
			position, scale, Quaternion(), Mesh::ball(32), material, 0, new_direction, 0.5f, 1.025f, s * 0.5f
		);

		MyEngine::instantiate(ptr, SceneObjectElement::SceneObjectType::BallPhysicsObject);
	}
}