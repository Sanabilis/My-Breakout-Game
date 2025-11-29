#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"
#include "./../scene/scene_light_object.hpp"
#include "./buffer_data.hpp"

#include "lodepng.h"
#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <filesystem>
#include <vector>

namespace my_engine
{
	// ================== //
	// Light Buffer Class //
	// ================== //
	class LightBuffer
	{
	private:
		// Buffer Data //
		std::vector<SceneLightObject*> _lights;

		GLuint _light_buffer = 0;
		size_t _light_buffer_size = 8;
		Vector3 _global_ambient;

	public:
		// Constructors //
		LightBuffer();
		LightBuffer(SceneLightObject& light);

		// Destructor //
		~LightBuffer();

		// Getters //
		GLuint get_light_buffer();

		// Setters //
		void set_light(size_t index, SceneLightObject* light);
		void add_light(SceneLightObject* light);
		void remove_light(size_t index);
		void set_global_ambient(const Vector3& color);

		// Buffer //
		void update_buffer();
		void update_buffer(size_t index);
		void bind_buffer();
		
		// Size of the Buffers in Bytes
		size_t size_of_lights() const { return _lights.size() * sizeof(Light); }
	};
} // namespace my_engine