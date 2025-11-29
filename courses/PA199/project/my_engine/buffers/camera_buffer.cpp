#pragma once

#include "./camera_buffer.hpp"

namespace my_engine
{
	// =================== //
	// Camera Buffer Class //
	// =================== //

	CameraBuffer::CameraBuffer()
	{
		glCreateBuffers(1, &_camera_buffer);
		glNamedBufferStorage(_camera_buffer, size_of_camera_matrices(), nullptr, GL_DYNAMIC_STORAGE_BIT);
	}

	CameraBuffer::CameraBuffer(SceneCameraObject& camera) : _camera(&camera)
	{
		std::vector<MatrixData> camera_matrices =
		{
			MatrixData(_camera->get_projection()),
			MatrixData(_camera->get_projection().inverse()),
			MatrixData(_camera->get_view()),
			MatrixData(_camera->get_view().inverse()),
			MatrixData(_camera->get_view().inverse().transpose())
		};

		glCreateBuffers(1, &_camera_buffer);
		glNamedBufferStorage(_camera_buffer, size_of_camera_matrices(), camera_matrices.data(), GL_DYNAMIC_STORAGE_BIT);
	}


	// Destructor //
	CameraBuffer::~CameraBuffer()
	{
		glDeleteBuffers(1, &_camera_buffer);
	}


	// Getters //
	SceneCameraObject* CameraBuffer::get_camera()
	{
		return _camera;
	}

	GLuint CameraBuffer::get_camera_buffer() const
	{
		return _camera_buffer;
	}


	// Setters //
	void CameraBuffer::switch_camera(SceneCameraObject* camera)
	{
		_camera = camera;

		if (_camera != nullptr)
		{
			update_buffer();
		}
	}


	// Buffer //
	void CameraBuffer::update_buffer() const
	{
		std::vector<MatrixData> camera_matrices =
		{
			MatrixData(_camera->get_projection()),
			MatrixData(_camera->get_projection().inverse()),
			MatrixData(_camera->get_view()),
			MatrixData(_camera->get_view().inverse()),
			MatrixData(_camera->get_view().inverse().transpose())
		};

		glNamedBufferSubData(_camera_buffer, 0, size_of_camera_matrices(), camera_matrices.data());
	}

	void CameraBuffer::update_projection_buffer() const
	{
		const Matrix4& projection = _camera->get_projection();
		std::vector<MatrixData> projection_matrices =
		{
			MatrixData(projection),
			MatrixData(projection.inverse())
		};

		glNamedBufferSubData(_camera_buffer, 0, size_of_projection_matrices(), projection_matrices.data());
	}

	void CameraBuffer::update_view_buffer() const
	{
		Matrix4 view = _camera->get_view();
		std::vector<MatrixData> view_matrices =
		{
			MatrixData(view),
			MatrixData(view.inverse()),
			MatrixData(view.inverse().transpose())
		};

		glNamedBufferSubData(_camera_buffer, size_of_projection_matrices(), size_of_view_matrices(), view_matrices.data());
	}

	void CameraBuffer::bind_buffer() const
	{
		Vector3 eye_position = _camera->get_eye_position();
		Vector3 direction = _camera->get_direction();

		GLint prog = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

		if (glGetUniformLocation(prog, "eye_position") != -1)
		{
			glUniform3f(0, eye_position.x(), eye_position.y(), eye_position.z());
		}
		
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _camera_buffer);
	}
} // namespace my_engine