#include "./gui_lives.hpp"

namespace my_engine
{
	GUILives* GUILives::lives = nullptr;


	GUILives::GUILives
	(
		const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture
	) : SceneGUIObject(min, max, uv_min, uv_max, anchor, texture) {}


	bool GUILives::is_zero() const
	{
		return _next == nullptr && _prev == nullptr;
	}


	GUILives& GUILives::operator++()
	{
		GUILives* current = this;

		while (current->_next != nullptr)
		{
			current = current->_next;
		}

		Vector2 min(current->_mesh.get_vertex(0).v1, current->_mesh.get_vertex(0).v2);
		Vector2 max(current->_mesh.get_vertex(3).v1, current->_mesh.get_vertex(3).v2);

		Vector2 min_uv(0.0f), max_uv(1.0f);

		Vector2 anchor(current->_mesh.get_vertex(0).n1, current->_mesh.get_vertex(0).n2);
		Vector2 gui_width(max.x() - min.x(), 0.0f);

		GUILives* ptr = new GUILives
		(
			min - gui_width, max - gui_width, min_uv, max_uv, anchor, _diffuse_texture
		);

		ptr->_prev = current;
		current->_next = ptr;

		MyEngine::to_instantiate(ptr, SceneObjectElement::SceneObjectType::GUIObject);

		return *this;
	}

	GUILives& GUILives::operator--()
	{
		GUILives* ptr = this;

		while (ptr->_next != nullptr)
		{
			ptr = ptr->_next;
		}

		if (ptr->_prev != nullptr)
		{
			ptr->_destroy = true;
			ptr->_prev->_next = nullptr;
		}

		return *this;
	}


	void GUILives::start()
	{
		SceneGUIObject::start();
	}

	void GUILives::update(float delta)
	{
		SceneGUIObject::update(delta);
	}

	void GUILives::physics_update(float fixed_delta)
	{
		SceneGUIObject::physics_update(fixed_delta);
	}

	void GUILives::late_update(float delta)
	{
		SceneGUIObject::late_update(delta);
	}


	void GUILives::instantiate(const Vector2& min, const Vector2& max, const Vector2& anchor, size_t lives)
	{
		GLuint lives_texture = MyEngine::get_texture("gui_heart");;
		Vector2 gui_width(max.x() - min.x(), 0.0f), min_uv(0.0f), max_uv(1.0f);
		GUILives* prev = new GUILives
		(
			Vector2(0.0f), Vector2(0.0), Vector2(0.0f), Vector2(0.0), anchor, lives_texture
		);

		GUILives::lives = prev;

		for (size_t i = 0; i < lives; i++) {
			GUILives* ptr = new GUILives
			(
				min - static_cast<float>(i) * gui_width, max - static_cast<float>(i) * gui_width, min_uv, max_uv, anchor, lives_texture
			);

			ptr->_prev = prev;
			ptr->_prev->_next = ptr;

			MyEngine::instantiate(ptr, SceneObjectElement::SceneObjectType::GUIObject);
			prev = ptr;
		}
	}
}