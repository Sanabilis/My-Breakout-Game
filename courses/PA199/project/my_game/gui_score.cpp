#include "./gui_score.hpp"

namespace my_engine
{
	GUIScore* GUIScore::score = nullptr;


	GUIScore::GUIScore
	(
		const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture
	) : SceneGUIObject(min, max, uv_min, uv_max, anchor, texture) {}



	bool GUIScore::is_zero() const
	{
		return _counter == 0;
	}



	GUIScore& GUIScore::operator+=(size_t n)
	{
		GUIScore* current = this;

		while (current->_prev != nullptr)
		{
			current = current->_prev;
		}

		while (current != nullptr)
		{
			size_t new_counter = (current->_counter + n);
			current->_counter = new_counter % current->_divisor;

			if (current->_prev == nullptr && new_counter / current->_divisor > 0)
			{
				Vector2 min(current->_mesh.get_vertex(0).v1, current->_mesh.get_vertex(0).v2);
				Vector2 max(current->_mesh.get_vertex(3).v1, current->_mesh.get_vertex(3).v2);

				Vector2 anchor(current->_mesh.get_vertex(0).n1, current->_mesh.get_vertex(0).n2);

				Vector2 min_uv(static_cast<float>((new_counter / current->_divisor) % 10) / 11.0f, 0.0f);
				Vector2 max_uv(static_cast<float>((new_counter / current->_divisor) % 10 + 1) / 11.0f, 1.0f);

				GUIScore* ptr = new GUIScore
				(
					min, max, min_uv, max_uv, anchor, _diffuse_texture
				);

				ptr->_counter = new_counter;
				ptr->_divisor = 10 * current->_divisor;
				ptr->_next = this;

				MyEngine::to_instantiate(ptr, SceneObjectElement::SceneObjectType::GUIObject);
				GUIScore::score = ptr;

				current->move_right();
				current->_prev = ptr;
			}

			current->update_uv();
			current = current->_next;
		}

		return *this;
	}



	void GUIScore::move_right()
	{
		float width = _mesh.get_vertex(2).v1 - _mesh.get_vertex(0).v1;

		_mesh.get_vertex(0).v1 += width;
		_mesh.get_vertex(1).v1 += width;
		_mesh.get_vertex(2).v1 += width;
		_mesh.get_vertex(3).v1 += width;

		_buffer->update_buffers();

		if (_next != nullptr)
		{
			_next->move_right();
		}
	}

	void GUIScore::move_left()
	{
		float width = _mesh.get_vertex(2).v1 - _mesh.get_vertex(0).v1;

		_mesh.get_vertex(0).v1 -= width;
		_mesh.get_vertex(1).v1 -= width;
		_mesh.get_vertex(2).v1 -= width;
		_mesh.get_vertex(3).v1 -= width;

		_buffer->update_buffers();

		if (_prev != nullptr)
		{
			_prev->move_left();
		}
	}

	void GUIScore::update_uv()
	{
		Vector2 min_uv(static_cast<float>(10 * _counter / _divisor) / 11.0f, 0.0f);
		Vector2 max_uv(static_cast<float>(10 * _counter / _divisor + 1) / 11.0f, 1.0f);

		_mesh.get_vertex(0).u = min_uv.x();
		_mesh.get_vertex(0).v = min_uv.y();

		_mesh.get_vertex(1).u = min_uv.x();
		_mesh.get_vertex(1).v = max_uv.y();

		_mesh.get_vertex(2).u = max_uv.x();
		_mesh.get_vertex(2).v = min_uv.y();

		_mesh.get_vertex(3).u = max_uv.x();
		_mesh.get_vertex(3).v = max_uv.y();

		_buffer->update_vertex_buffer();
	}



	void GUIScore::start()
	{
		SceneGUIObject::start();
	}

	void GUIScore::update(float delta)
	{
		SceneGUIObject::update(delta);
	}

	void GUIScore::physics_update(float fixed_delta)
	{
		SceneGUIObject::physics_update(fixed_delta);
	}

	void GUIScore::late_update(float delta)
	{
		SceneGUIObject::late_update(delta);
	}


	void GUIScore::instantiate(const Vector2& min, const Vector2& max, const Vector2& anchor, size_t counter)
	{
		GLuint digits_texture = MyEngine::get_texture("gui_digits");;
		Vector2 gui_width(max.x() - min.x(), 0.0f);
		GUIScore* prev = nullptr;
		size_t i = 0;
		bool set_score = true;

		size_t divisor = 10;

		while (counter / divisor > 0)
		{
			divisor *= 10;
		}

		do {
			size_t counter_divisor = divisor;
			divisor /= 10;

			Vector2 min_uv(static_cast<float>(counter / divisor) / 11.0f, 0.0f);
			Vector2 max_uv(static_cast<float>(counter / divisor + 1) / 11.0f, 1.0f);

			GUIScore* ptr = new GUIScore
			(
				min + static_cast<float>(i) * gui_width, max + static_cast<float>(i) * gui_width, min_uv, max_uv, anchor, digits_texture
			);

			ptr->_counter = counter;
			ptr->_divisor = 10 * divisor;
			ptr->_prev = prev;

			if (ptr->_prev != nullptr)
			{
				ptr->_prev->_next = ptr;
			}
			
			MyEngine::instantiate(ptr, SceneObjectElement::SceneObjectType::GUIObject);

			if (set_score)
			{
				GUIScore::score = ptr;
				set_score = false;
			}

			prev = ptr;
			counter %= divisor;
			i++;
		} while (counter > 0);
	}
}