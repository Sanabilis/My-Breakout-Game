#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"
#include "./../scene/scene_camera_object.hpp"
#include "./buffer_data.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

namespace my_engine
{
	// =================== //
	// Camera Buffer Class //
	// =================== //
	class CameraBuffer
	{
	private:
		// Buffer Data //
		SceneCameraObject* _camera = nullptr;
		GLuint _camera_buffer = 0;

	public:
		// Constructors //
		CameraBuffer();
		CameraBuffer(SceneCameraObject& camera);

		// Destructor //
		~CameraBuffer();

		// Getters //
		SceneCameraObject* get_camera();
		GLuint get_camera_buffer() const;

		// Setters //
		void switch_camera(SceneCameraObject* camera);

		// Buffer //
		void update_buffer() const;
		void update_projection_buffer() const;
		void update_view_buffer() const;
		void bind_buffer() const;

		// Size of the Buffer in Bytes //
		size_t size_of_camera_matrices() const { return 5 * sizeof(MatrixData); }
		size_t size_of_projection_matrices() const { return 2 * sizeof(MatrixData); }
		size_t size_of_view_matrices() const { return 3 * sizeof(MatrixData); }
	};
} // namespace my_engine