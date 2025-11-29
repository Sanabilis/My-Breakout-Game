#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"
#include "./../scene/scene_model_object.hpp"
#include "./buffer_data.hpp"

#include "lodepng.h"
#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <filesystem>
#include <vector>

namespace my_engine
{
	// ================== //
	// Model Buffer Class //
	// ================== //
	class ModelBuffer
	{
	private:
		// Buffer Data //
		SceneModelObject* _model_object = nullptr;

		GLuint _vertex_arrays = 0;
		GLuint _vertex_buffer = 0;
		GLuint _index_buffer = 0;
		GLuint _model_buffer = 0;
		GLuint _material_buffer = 0;
		GLenum _mode = GL_TRIANGLES;

	public:
		// Constructors //
		ModelBuffer();
		ModelBuffer(SceneModelObject& o, GLenum mode = GL_TRIANGLES);
		void init_buffers();

		// Destructor //
		~ModelBuffer();

		// Getters //
		GLuint get_vertex_arrays() const;
		GLuint get_vertex_buffer() const;
		GLuint get_index_buffer() const;
		GLuint get_model_buffer() const;
		GLuint get_material_buffer() const;
		SceneModelObject* get_model();
		const SceneModelObject* get_model() const;

		// Setters //
		void set_model(SceneModelObject* model_object);

		// Buffer //
		void update_buffers() const;
		void update_vertex_buffer() const;
		void update_index_buffer() const;
		void update_model_buffer() const;
		void update_material_buffer() const;
		void bind_buffers() const;
		void bind_vertex_arrays() const;
		void bind_vertex_buffer() const;
		void bind_index_buffer() const;
		void bind_model_buffer() const;
		void bind_material_buffer() const;
		void bind_texture() const;

		// Draw the Model //
		void draw() const;

		// Size of the Buffers in Bytes
		size_t size_of_vertices() const { return _model_object->get_mesh().vertices_count() * sizeof(Vertex); }
		size_t size_of_indices() const { return _model_object->get_mesh().triangles_count() * sizeof(Triangle); }
		size_t size_of_model_matrices() const { return 3 * sizeof(MatrixData); }
	};
} // namespace my_engine