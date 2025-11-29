#include "./powerup.hpp"

namespace my_engine
{
	PowerUp::PowerUp
	(
		const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const Mesh& mesh, const Material& material, GLuint texture,
		const Vector3& direction, float velocity, float bounce_factor, float radius, PowerUpType type
	) :
		SceneBallPhysicsObject(position, scale, rotation, mesh, material, texture, direction, velocity, bounce_factor, radius), _type(type) {}



	void PowerUp::on_collision()
	{
		_destroy = true;

		switch (_type)
		{
		case PowerUpType::LifeUp:
			GUILives::lives->operator++();
			break;
		case PowerUpType::ScoreUp:
			*GUIScore::score += 100;
			break;
		}
	}



	void PowerUp::start()
	{
		SceneBallPhysicsObject::start();
	}

	void PowerUp::update(float delta)
	{
		SceneBallPhysicsObject::update(delta);

		if (_position.magnitude() > 2.5f && MyEngine::my_engine.state == GameState::Running)
		{
			_destroy = true;
		}
	}

	void PowerUp::physics_update(float fixed_delta)
	{
		if (MyEngine::my_engine.space_pressed)
		{
			_collide = _physics.get_cartesian_position().magnitude() > 1.5f;
			SceneBallPhysicsObject::physics_update(fixed_delta);
		}
	}

	void PowerUp::late_update(float delta)
	{
		SceneBallPhysicsObject::late_update(delta);
	}


	void PowerUp::instantiate(const Vector3& position, const Vector3& scale, const Quaternion& rotation, PowerUpType type)
	{
		float s = (scale.x() + scale.y() + scale.z()) / 3.0f;

		Material material;

		switch (type)
		{
		case PowerUpType::LifeUp:
			material.ar = 0.196f, material.ag = 0.804f, material.ab = 0.196f, material.aa = 0.5f;
			material.dr = 0.196f, material.dg = 0.804f, material.db = 0.196f, material.da = 0.5f;
			break;
		case PowerUpType::ScoreUp:
			material.ar = 1.0f, material.ag = 0.827f, material.ab = 0.0f, material.aa = 0.5f;
			material.dr = 1.0f, material.dg = 0.827f, material.db = 0.0f, material.da = 0.5f;
			break;
		}

		PowerUp* ptr = new PowerUp
		(
			position, scale, Quaternion(), Mesh::ball(32), material, 0, position, 0.25f, 1.025f, s * 0.5f, type
		);

		MyEngine::to_instantiate(ptr, SceneObjectElement::SceneObjectType::BallPhysicsObject);
	}
}