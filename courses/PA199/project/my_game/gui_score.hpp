#pragma once

#include "./../application.hpp"

namespace my_engine
{
	class GUIScore : public SceneGUIObject
	{
	public:
		static GUIScore* score;

	protected:
		size_t _counter = 0;
		size_t _divisor = 10;

		GUIScore* _next = nullptr;
		GUIScore* _prev = nullptr;

	public:
		GUIScore
		(
			const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture
		);

		bool is_zero() const;

		GUIScore& operator+=(size_t n);

		void move_right();
		void move_left();
		void update_uv();

		void start() override;
		void update(float delta) override;
		void physics_update(float fixed_delta) override;
		void late_update(float delta) override;

		static void instantiate
		(
			const Vector2& min, const Vector2& max, const Vector2& anchor, size_t counter
		);
	};
} // namespace my_engine