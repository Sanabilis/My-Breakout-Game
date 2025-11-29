#pragma once

#include "./../application.hpp"

namespace my_engine
{
	class Brick : public ScenePaddlePhysicsObject
	{
	protected:
		size_t _health;
		size_t _init_health;
		size_t _offset = 0;
		Brick* _below = nullptr;
		Brick* _above = nullptr;

	public:
		static size_t bricks_count;

	public:
		Brick
		(
			const Vector3& position, float scale, const Mesh& mesh, const Material& material, GLuint texture,
			const Vector3& direction, float velocity, float bounce_factor, float angle, float thickness, size_t health
		);

		virtual bool use_alpha() const override;

		// Setters //
		virtual void set_diffuse_texture(GLuint texture) override;
		virtual void set_normal_texture(GLuint texture) override;

		// Collision Methods //
		virtual void on_collision() override;

		void start() override;
		void update(float delta) override;
		void physics_update(float fixed_delta) override;
		void late_update(float delta) override;

		static void instantiate
		(
			const Vector3& position = Vector3(0.0f), const Vector3& scale = Vector3(1.0f), const Quaternion& rotation = Quaternion(),
			size_t health = 1, size_t count = 3
		);
	};
} // namespace my_engine