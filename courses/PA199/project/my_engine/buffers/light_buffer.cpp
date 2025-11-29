#pragma once

#include "./light_buffer.hpp"

namespace my_engine
{
	// ================== //
	// Light Buffer Class //
	// ================== //

	// Constructors //
	LightBuffer::LightBuffer()
	{
		glCreateBuffers(1, &_light_buffer);
		glNamedBufferStorage(_light_buffer, _light_buffer_size * sizeof(Light), nullptr, GL_DYNAMIC_STORAGE_BIT);
	}

	LightBuffer::LightBuffer(SceneLightObject& light)
	{
		_lights.push_back(&light);

		glCreateBuffers(1, &_light_buffer);
		glNamedBufferStorage(_light_buffer, _light_buffer_size * sizeof(Light), nullptr, GL_DYNAMIC_STORAGE_BIT);
		update_buffer(0);
	}


	// Destructor //
	LightBuffer::~LightBuffer()
	{
		glDeleteBuffers(1, &_light_buffer);
	}


	// Getters //
	GLuint LightBuffer::get_light_buffer()
	{
		return _light_buffer;
	}


	// Setters //
	void LightBuffer::set_light(size_t index, SceneLightObject* light)
	{
		if (index >= _lights.size())
		{
			add_light(light);
		}
		else if (index >= 0)
		{
			_lights[index] = light;
			update_buffer(index);
		}
	}

	void LightBuffer::add_light(SceneLightObject* light)
	{
		_lights.push_back(light);
		_lights[_lights.size() - 1]->_index = _lights.size() - 1;

		if (_lights.size() > _light_buffer_size)
		{
			update_buffer();
		}
		else
		{
			update_buffer(_lights.size() - 1);
		}
	}

	void LightBuffer::remove_light(size_t index)
	{
		if (index >= 0 && index < _lights.size())
		{
			_lights.erase(_lights.begin() + index);

			for (size_t i = index; i < _lights.size(); i++)
			{
				update_buffer(i);
				_lights[i]->_index--;
			}
		}
	}

	void LightBuffer::set_global_ambient(const Vector3& color)
	{
		_global_ambient = color;
	}


	// Buffer //
	void LightBuffer::update_buffer()
	{
		if (_lights.size() > _light_buffer_size)
		{
			while (_lights.size() > _light_buffer_size)
			{
				_light_buffer_size += 8;
			}

			glBufferStorage(_light_buffer, _light_buffer_size * sizeof(Light), nullptr, GL_DYNAMIC_STORAGE_BIT);
		}

		for (size_t i = 0; i < _lights.size(); i++)
		{
			update_buffer(i);
		}
	}

	void LightBuffer::update_buffer(size_t index)
	{
		glNamedBufferSubData(_light_buffer, index * sizeof(Light), sizeof(Light), &_lights[index]->get_light());
	}

	void LightBuffer::bind_buffer()
	{
		GLint prog = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

		if (glGetUniformLocation(prog, "lights_count") != -1)
		{
			glUniform1ui(3, _lights.size());
		}

		if (glGetUniformLocation(prog, "global_ambient") != -1)
		{
			glUniform3f(4, _global_ambient.x(), _global_ambient.y(), _global_ambient.z());
		}

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, _light_buffer);
	}
} // namespace my_engine