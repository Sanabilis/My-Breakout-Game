#pragma once

#include "./../application.hpp"

namespace my_engine
{
	class PowerUp : public SceneBallPhysicsObject
	{
	public:
		enum struct PowerUpType
		{
			LifeUp,
			ScoreUp
		};

	protected:
		PowerUpType _type;

	public:
		PowerUp
		(
			const Vector3& position, const Vector3& scale, const Quaternion& rotation,
			const Mesh& mesh, const Material& material, GLuint texture,
			const Vector3& direction, float velocity, float bounce_factor, float radius, PowerUpType type
		);

		// Collision Methods //
		virtual void on_collision() override;

		void start() override;
		void update(float delta) override;
		void physics_update(float fixed_delta) override;
		void late_update(float delta) override;

		static void instantiate
		(
			const Vector3& position = Vector3(0.0f), const Vector3& scale = Vector3(1.0f), const Quaternion& rotation = Quaternion(), PowerUpType type = PowerUpType::LifeUp
		);
	};
} // namespace my_engine