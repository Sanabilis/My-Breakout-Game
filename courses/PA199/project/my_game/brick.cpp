#include "./brick.hpp"

namespace my_engine
{
	size_t Brick::bricks_count = 0;

	Brick::Brick
	(
		const Vector3& position, float scale, const Mesh& mesh, const Material& material, GLuint texture,
		const Vector3& direction, float velocity, float bounce_factor, float angle, float thickness, size_t health
	) : ScenePaddlePhysicsObject(position, scale, mesh, material, texture, direction, velocity, bounce_factor, angle, thickness), _health(health)
	{
		bricks_count++;

		_health += rand() % 3;
		_init_health = _health;

		switch (_health)
		{
		case 1:
			_diffuse_texture = MyEngine::get_texture("rock_broken_diffuse");
			_normal_texture = MyEngine::get_texture("rock_broken_normal");
			break;
		case 2:
			_diffuse_texture = MyEngine::get_texture("rock_cracked_diffuse");
			_normal_texture = MyEngine::get_texture("rock_cracked_normal");
			break;
		case 3:
			_diffuse_texture = MyEngine::get_texture("rock_diffuse");
			_normal_texture = MyEngine::get_texture("rock_normal");
			break;
		}
	}



	bool Brick::use_alpha() const
	{
		return MyEngine::get_camera_type() == Camera::CameraType::Perspective;
	}


	// Setters //
	void Brick::set_diffuse_texture(GLuint texture)
	{
		_diffuse_texture = texture;

		if (_below != nullptr)
		{
			_below->set_diffuse_texture(texture);
		}
	}
	
	void Brick::set_normal_texture(GLuint texture)
	{
		_normal_texture = texture;

		if (_below != nullptr)
		{
			_below->set_normal_texture(texture);
		}
	}



	void Brick::on_collision()
	{
		_health--;

		switch (_health)
		{
		case 2:
			_diffuse_texture = MyEngine::get_texture("rock_cracked_diffuse");
			_normal_texture = MyEngine::get_texture("rock_cracked_normal");

			break;
		case 1:
			_diffuse_texture = MyEngine::get_texture("rock_broken_diffuse");
			_normal_texture = MyEngine::get_texture("rock_broken_normal");

			break;
		case 0:
			int random = rand() % 20;

			if (random == 0)
			{
				PowerUp::instantiate(_physics.get_cartesian_position(), Vector3(0.125f), Quaternion(), PowerUp::PowerUpType::LifeUp);
			}
			else if (random > 0 && random < 5)
			{
				PowerUp::instantiate(_physics.get_cartesian_position(), Vector3(0.125f), Quaternion(), PowerUp::PowerUpType::ScoreUp);
			}

			_destroy = true;
			bricks_count--;

			*GUIScore::score += 10 * _init_health;
			Brick* above = _above;

			if (above != nullptr)
			{
				above->_below = nullptr;
				above->set_collide(true);
			}

			while (above != nullptr)
			{
				above->_offset--;
				above = above->_above;
			}

			if (bricks_count <= 0)
			{
				MyEngine::my_engine.state = GameState::Victory;
				MyEngine::my_engine.time_factor = 0.0f;
			}

			break;
		}
	}



	void Brick::start()
	{
		ScenePaddlePhysicsObject::start();
	}

	void Brick::update(float delta)
	{
		ScenePaddlePhysicsObject::update(delta);
	}

	void Brick::physics_update(float fixed_delta)
	{
		ScenePaddlePhysicsObject::physics_update(fixed_delta);

		_position = Vector3(0.0f, 0.25f * static_cast<float>(_offset), 0.0f);
		_buffer->update_model_buffer();
	}

	void Brick::late_update(float delta)
	{
		ScenePaddlePhysicsObject::late_update(delta);
	}


	void Brick::instantiate(const Vector3& position, const Vector3& scale, const Quaternion& rotation, size_t health, size_t count)
	{
		float s = (scale.x() + scale.y() + scale.z()) / 3.0f;
		float angle = PI / 6.0f;
		float width = 0.15f / s;
		float height = 0.25f / s;
		size_t level = 32;

		Brick* prev = nullptr;

		for (size_t i = 0; i < count; i++)
		{
			Brick* ptr = new Brick
			(
				position, s, Mesh::paddle(level, angle, width, height), Material::DEFAULT_MATERIAL, 0, Vector3::FORWARD, 0.0f, 0.0f, angle, width, health
			);

			if (prev != nullptr)
			{
				ptr->_below = prev;
				ptr->_offset = ptr->_below->_offset + 1;
				ptr->_collide = false;
				prev->_above = ptr;
			}

			MyEngine::instantiate(ptr, SceneObjectElement::SceneObjectType::PaddlePhysicsObject);
			prev = ptr;
		}
	}
}