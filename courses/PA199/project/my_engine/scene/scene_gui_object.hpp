#pragma once

#include "./scene_model_object.hpp"

namespace my_engine
{
	// ========================== //
	// Scene Object Class for GUI //
	// ========================== //
	class SceneGUIObject : public SceneModelObject
	{
	public:
		// Constructors //
		SceneGUIObject();
		SceneGUIObject(const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture);

		bool destroy_on_victory() const override;

		// Scene Methods //
		virtual void start() override;
		virtual void update(float delta) override;
		virtual void late_update(float delta) override;
		virtual void physics_update(float fixed_delta) override;
	};
}