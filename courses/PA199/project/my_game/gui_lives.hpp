#pragma once

#include "./../application.hpp"

namespace my_engine
{
	class GUILives : public SceneGUIObject
	{
	public:
		static GUILives* lives;

	protected:
		GUILives* _next = nullptr;
		GUILives* _prev = nullptr;

	public:
		GUILives
		(
			const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture
		);

		GUILives& operator++();
		GUILives& operator--();

		bool is_zero() const;

		void start() override;
		void update(float delta) override;
		void physics_update(float fixed_delta) override;
		void late_update(float delta) override;

		static void instantiate
		(
			const Vector2& min, const Vector2& max, const Vector2& anchor, size_t lives
		);
	};
} // namespace my_engine