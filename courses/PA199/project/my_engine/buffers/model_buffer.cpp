#pragma once

#include "./model_buffer.hpp"

namespace my_engine
{
	// ================== //
	// Model Buffer Class //
	// ================== //

	// Constructors //
	ModelBuffer::ModelBuffer() = default;
	ModelBuffer::ModelBuffer(SceneModelObject& o, GLenum mode) : _model_object(&o)
	{
		_mode = mode;
		init_buffers();
	}

	void ModelBuffer::init_buffers()
	{
		glGenVertexArrays(1, &_vertex_arrays);
		glBindVertexArray(_vertex_arrays);

		glGenBuffers(1, &_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, size_of_vertices(), _model_object->get_mesh().get_vertices().data(), GL_DYNAMIC_DRAW);
		glEnableVertexArrayAttrib(_vertex_arrays, 0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glEnableVertexArrayAttrib(_vertex_arrays, 1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexArrayAttrib(_vertex_arrays, 2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

		glGenBuffers(1, &_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices(), _model_object->get_mesh().get_triangles().data(), GL_STATIC_DRAW);

		Matrix4 model = _model_object->get_transformation_matrix();

		std::vector<MatrixData> model_matrices =
		{
			MatrixData(model),
			MatrixData(model.inverse()),
			MatrixData(model.inverse().transpose())
		};

		glCreateBuffers(1, &_model_buffer);
		glNamedBufferStorage(_model_buffer, size_of_model_matrices(), model_matrices.data(), GL_DYNAMIC_STORAGE_BIT);

		glCreateBuffers(1, &_material_buffer);
		glNamedBufferStorage(_material_buffer, sizeof(Material), &_model_object->get_material(), GL_DYNAMIC_STORAGE_BIT);
	}


	// Destructor //
	ModelBuffer::~ModelBuffer()
	{
		glDeleteVertexArrays(1, &_vertex_arrays);
		glDeleteBuffers(1, &_vertex_buffer);
		glDeleteBuffers(1, &_index_buffer);
		glDeleteBuffers(1, &_model_buffer);
		glDeleteBuffers(1, &_material_buffer);
	}


	// Getters //
	GLuint ModelBuffer::get_vertex_arrays() const
	{
		return _vertex_arrays;
	}

	GLuint ModelBuffer::get_vertex_buffer() const
	{
		return _vertex_buffer;
	}

	GLuint ModelBuffer::get_index_buffer() const
	{
		return _index_buffer;
	}

	GLuint ModelBuffer::get_model_buffer() const
	{
		return _model_buffer;
	}

	GLuint ModelBuffer::get_material_buffer() const
	{
		return _material_buffer;
	}

	SceneModelObject* ModelBuffer::get_model()
	{
		return _model_object;
	}

	const SceneModelObject* ModelBuffer::get_model() const
	{
		return _model_object;
	}


	// Setters //
	void ModelBuffer::set_model(SceneModelObject* model_object)
	{
		_model_object = model_object;
	}


	// Buffers //
	void ModelBuffer::update_buffers() const
	{
		update_vertex_buffer();
		update_index_buffer();
		update_model_buffer();
		update_material_buffer();
	}

	void ModelBuffer::update_vertex_buffer() const
	{
		glNamedBufferSubData(_vertex_buffer, 0, size_of_vertices(), _model_object->get_mesh().get_vertices().data());
	}

	void ModelBuffer::update_index_buffer() const
	{
		glNamedBufferSubData(_index_buffer, 0, size_of_indices(), _model_object->get_mesh().get_triangles().data());
	}

	void ModelBuffer::update_model_buffer() const
	{
		Matrix4 model = _model_object->get_transformation_matrix();

		std::vector<MatrixData> model_matrices = 
		{
			MatrixData(model),
			MatrixData(model.inverse()),
			MatrixData(model.inverse().transpose())
		};

		glNamedBufferSubData(_model_buffer, 0, size_of_model_matrices(), model_matrices.data());
	}

	void ModelBuffer::update_material_buffer() const
	{
		glNamedBufferSubData(_material_buffer, 0, sizeof(Material), &_model_object->get_material());
	}

	void ModelBuffer::bind_buffers() const
	{
		bind_vertex_arrays();
		bind_vertex_buffer();
		bind_index_buffer();
		bind_model_buffer();
		bind_material_buffer();
		bind_texture();
	}

	void ModelBuffer::bind_vertex_arrays() const
	{
		glBindVertexArray(_vertex_arrays);
	}

	void ModelBuffer::bind_vertex_buffer() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	}

	void ModelBuffer::bind_index_buffer() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	}

	void ModelBuffer::bind_model_buffer() const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, _model_buffer);
	}

	void ModelBuffer::bind_material_buffer() const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, _material_buffer);
	}

	void ModelBuffer::bind_texture() const
	{
		GLint prog = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

		if (_model_object->get_diffuse_texture() != 0)
		{
			if (glGetUniformLocation(prog, "has_diffuse_texture") != -1)
			{
				glUniform1i(1, true);
			}

			glBindTextureUnit(0, _model_object->get_diffuse_texture());
		}
		else if (glGetUniformLocation(prog, "has_diffuse_texture") != -1)
		{
			glUniform1i(1, false);
		}

		if (_model_object->get_normal_texture() != 0)
		{
			if (glGetUniformLocation(prog, "has_normal_texture") != -1)
			{
				glUniform1i(2, true);
			}
				
			glBindTextureUnit(1, _model_object->get_normal_texture());
		}
		else if (glGetUniformLocation(prog, "has_normal_texture") != -1)
		{
			glUniform1i(2, false);
		}
	}


	// Draw the Model //
	void ModelBuffer::draw() const
	{
		bind_buffers();
		glDrawElements(_mode, 3 * _model_object->get_mesh().triangles_count(), GL_UNSIGNED_INT, nullptr);
	}
} // namespace my_engine