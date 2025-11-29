#pragma once

#include "./../application.hpp"

namespace my_engine
{
	class Paddle : public ScenePaddlePhysicsObject
	{
	protected:
		float _rotation_angle = 0.0f;
		float _rotation_acceleration;
		float _rotation_deceleration;
		float _max_rotation_angle;

	public:
		Paddle
		(
			const Vector3& position, float scale, const Mesh& mesh, const Material& material, GLuint texture,
			const Vector3& direction, float velocity, float bounce_factor, float angle, float thickness,
			float rotation_acceleration, float rotation_deceleration, float max_rotation_angle
		);

		void start() override;
		void update(float delta) override;
		void physics_update(float fixed_delta) override;
		void late_update(float delta) override;

		static void instantiate
		(
			const Vector3& position = Vector3(0.0f), const Vector3& scale = Vector3(1.0f), const Quaternion& rotation = Quaternion(),
			float rotation_acceleration = 2.0f * PI, float rotation_deceleration = 4.0f * PI, float max_rotation_angle = 0.25f * PI
		);
	};
} // namespace my_engine