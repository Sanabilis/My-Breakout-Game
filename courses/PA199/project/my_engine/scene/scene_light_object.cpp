#include "./scene_light_object.hpp"
#include "./../buffers/light_buffer.hpp"

namespace my_engine
{
	// ====================== //
	// Scene Class for Lights //
	// ====================== //

	// Constructors //
	SceneLightObject::SceneLightObject() : SceneObject() {}

	SceneLightObject::SceneLightObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const Light& light) : SceneObject(position, scale, rotation)
	{
		_light = std::make_unique<Light>(light);
		set_position(position);
	}


	// Getters //
	Light& SceneLightObject::get_light()
	{
		return *_light;
	}

	const Light& SceneLightObject::get_light() const
	{
		return *_light;
	}

	LightBuffer& SceneLightObject::get_buffer()
	{
		return *_buffer;
	}

	const LightBuffer& SceneLightObject::get_buffer() const
	{
		return *_buffer;
	}

	size_t SceneLightObject::get_index() const
	{
		return _index;
	}

	Vector4 SceneLightObject::get_ambient() const
	{
		return _light->get_ambient();
	}

	Vector4 SceneLightObject::get_diffuse() const
	{
		return _light->get_diffuse();
	}

	Vector4 SceneLightObject::get_specular() const
	{
		return _light->get_specular();
	}

	float SceneLightObject::get_constant() const
	{
		return _light->get_constant();
	}

	float SceneLightObject::get_linear() const
	{
		return _light->get_linear();
	}

	float SceneLightObject::get_quadratic() const
	{
		return _light->get_quadratic();
	}

	float SceneLightObject::get_radius() const
	{
		return _light->get_radius();
	}

	bool SceneLightObject::is_point() const
	{
		return _light->is_point();
	}

	// Setters //
	void SceneLightObject::set_position(const Vector3& position)
	{
		SceneObject::set_position(position);
		_light->set_position(position);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_ambient(const Vector4& color)
	{
		_light->set_ambient(color);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_diffuse(const Vector4& color)
	{
		_light->set_diffuse(color);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_specular(const Vector4& color)
	{
		_light->set_specular(color);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_constant(float constant)
	{
		_light->set_constant(constant);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_linear(float linear)
	{
		_light->set_linear(linear);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_quadratic(float quadratic)
	{
		_light->set_quadratic(quadratic);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_radius(float radius)
	{
		_light->set_radius(radius);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_point(bool is_point)
	{
		_light->set_point(is_point);

		if (_buffer != nullptr)
		{
			_buffer->update_buffer(_index);
		}
	}

	void SceneLightObject::set_buffer(LightBuffer* buffer)
	{
		_buffer = buffer;
	}



	// Scene Methods //
	void SceneLightObject::start() {}
	void SceneLightObject::update(float delta) {}
	void SceneLightObject::late_update(float delta) {}
	void SceneLightObject::physics_update(float delta) {}
}