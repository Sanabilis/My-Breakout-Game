#include "./scene_gui_object.hpp"

namespace my_engine
{
	// Constructors //
	SceneGUIObject::SceneGUIObject() : SceneModelObject()
	{
		_mesh = Mesh::sprite(Vector2(-1.0f), Vector2(1.0f), Vector2(0.0f), Vector2(1.0f), Vector2(0.0f));
	}

	SceneGUIObject::SceneGUIObject(const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture) : SceneModelObject()
	{
		_mesh = Mesh::sprite(min, max, uv_min, uv_max, anchor);
		_diffuse_texture = texture;
	}


	bool SceneGUIObject::destroy_on_victory() const
	{
		return false;
	}


	// Scene Methods //
	void SceneGUIObject::start() {}
	void SceneGUIObject::update(float delta) {}
	void SceneGUIObject::late_update(float delta) {}
	void SceneGUIObject::physics_update(float fixed_delta) {}
}