#include "./mesh.hpp"

namespace my_engine
{
	// Default Material //
	Material Material::DEFAULT_MATERIAL = Material();

	// ========== //
	// Mesh Class //
	// ========== //

	// Constructors //
	Mesh::Mesh() = default;

	Mesh::Mesh(const Mesh& m)
	{
		_vertices = m._vertices;
		_triangles = m._triangles;
	}


	// Getters //
	const std::vector<Vertex>& Mesh::get_vertices() const
	{
		return _vertices;
	}

	const std::vector<Triangle>& Mesh::get_triangles() const
	{
		return _triangles;
	}

	const Vertex& Mesh::get_vertex(size_t index) const
	{
		return _vertices[index];
	}

	const Triangle& Mesh::get_triangle(size_t index) const
	{
		return _triangles[index];
	}

	Vertex& Mesh::get_vertex(size_t index)
	{
		return _vertices[index];
	}

	Triangle& Mesh::get_triangle(size_t index)
	{
		return _triangles[index];
	}


	// Assignment Operator //
	Mesh& Mesh::operator=(const Mesh& m)
	{
		_vertices = m._vertices;
		_triangles = m._triangles;

		return *this;
	}


	// Number of Vertices / Triangles //
	size_t Mesh::vertices_count() const
	{
		return _vertices.size();
	}

	size_t Mesh::triangles_count() const
	{
		return _triangles.size();
	}


	// Static Methods to Generate Mesh //
	Mesh Mesh::plane(size_t level)
	{
		assert(level >= 3);

		Mesh res;

		res._vertices =
		{
			{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f },
			{ 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f }
		};

		for (int i = 1; i < level; i++)
		{
			float cos = std::cos(2.0f * static_cast<float>(i) * PI / level);
			float sin = std::sin(2.0f * static_cast<float>(i) * PI / level);

			res._vertices.push_back({  sin / 2.0f, 0.0f, cos / 2.0f, 0.0f, 1.0f, 0.0f, sin / 2.0f + 0.5f, cos / 2.0f + 0.5f });
			res._triangles.push_back({ 0, static_cast<GLuint>(i + 1),  static_cast<GLuint>(i) });
		}

		res._triangles.push_back({ 0, static_cast<GLuint>(level),  1 });

		return res;
	}

	Mesh Mesh::cube()
	{
		Mesh res;

		res._vertices =
		{
			{ -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f },
			{ -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f },
			{  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f },
			{  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f },
			
			{  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f },
			{  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f },
			{  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f },
			{  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f },

			{  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f },
			{  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f },
			{ -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f },
			{ -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f },
			
			{ -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f },
			{ -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f },
			{ -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f },
			{ -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f },

			{ -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f },
			{ -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f },
			{  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f },
			{  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f },
			
			{ -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f },
			{ -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f },
			{  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f },
			{  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f }
		};

		res._triangles =
		{
			{ 0,  1,  2 },  { 0,  2,  3 },
			{ 4,  5,  6 },  { 4,  6,  7 },
			{ 8,  9,  10 }, { 8,  10, 11 },
			{ 12, 13, 14 },	{ 12, 14, 15 },
			{ 16, 17, 18 },	{ 16, 18, 19 },
			{ 20, 21, 22 },	{ 20, 22, 23 }
		};

		return res;
	}

	Mesh Mesh::paddle(size_t level, float angle, float width, float height)
	{
		assert(level >= 4);
		assert(width > 0.01f && width < 0.49f);
		assert(height > 0.01f);

		Mesh res;

		if (angle < 2.0f * PI && angle > 0.0f)
		{
			res._triangles =
			{
				{ 0, 1, 2 },
				{ 1, 2, 3 }
			};
		}
		else if (angle > 0.0f)
		{
			angle = 2.0f * PI;
		}
		else
		{
			return res;
		}

		float uv_step = 1.0f / static_cast<float>(level);

		// Add the First Face
		res._vertices =
		{
			{ 0.5f + width / 2.0f,	height / 2.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.5f, 1.0f        },
			{ 0.5f + width / 2.0f, -height / 2.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.5f, 0.0f        },
			{ 0.5f - width / 2.0f,	height / 2.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f        },
			{ 0.5f - width / 2.0f, -height / 2.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f        },

			{ 0.5f + width / 2.0f, -height / 2.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f        },
			{ 0.5f + width / 2.0f,	height / 2.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 2.0f / 3.0f },
			{ 0.5f + width / 2.0f,	height / 2.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 2.0f / 3.0f },
			{ 0.5f - width / 2.0f,	height / 2.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f        },

			{ 0.5f - width / 2.0f,	height / 2.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f        },
			{ 0.5f - width / 2.0f, -height / 2.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f / 3.0f },
			{ 0.5f - width / 2.0f, -height / 2.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f / 3.0f },
			{ 0.5f + width / 2.0f, -height / 2.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f        }
		};

		for (int i = 1; i <= level; i++)
		{
			float cos = std::cos(i * angle / level);
			float sin = std::sin(i * angle / level);

			Vector3 v1 = Vector3(cos, 0.0f, sin) * 0.5f + Vector3(cos, 0.0f, sin) * width / 2.0f;
			Vector3 v2 = v1 - Vector3(cos, 0.0f, sin) * width;
			Vector3 n = Vector3(cos, 0.0f, sin);

			float u = static_cast<float>(i) * uv_step;

			// Add Vertices
			res._vertices.push_back({ v1.x(), -height / 2.0f, v1.z(),  n.x(),  0.0f,  n.z(), u, 0.0f        });
			res._vertices.push_back({ v1.x(),  height / 2.0f, v1.z(),  n.x(),  0.0f,  n.z(), u, 2.0f / 3.0f });

			res._vertices.push_back({ v1.x(),  height / 2.0f, v1.z(),  0.0f,   1.0f,  0.0f,  u, 2.0f / 3.0f });
			res._vertices.push_back({ v2.x(),  height / 2.0f, v2.z(),  0.0f,   1.0f,  0.0f,  u, 1.0f        });

			res._vertices.push_back({ v2.x(),  height / 2.0f, v2.z(), -n.x(),  0.0f, -n.z(), u, 1.0f        });
			res._vertices.push_back({ v2.x(), -height / 2.0f, v2.z(), -n.x(),  0.0f, -n.z(), u, 1.0f / 3.0f });

			res._vertices.push_back({ v2.x(), -height / 2.0f, v2.z(),  0.0f,  -1.0f,  0.0f,  u, 1.0f / 3.0f });
			res._vertices.push_back({ v1.x(), -height / 2.0f, v1.z(),  0.0f,  -1.0f,  0.0f,  u, 0.0f        });

			GLuint sz = static_cast<GLuint>(res._vertices.size());

			// Add Face Indices
			res._triangles.push_back({sz - 16, sz - 15, sz - 7  });
			res._triangles.push_back({ sz - 16, sz - 7,  sz - 8 });

			res._triangles.push_back({sz - 14, sz - 13, sz - 5  });
			res._triangles.push_back({ sz - 14, sz - 5,  sz - 6 });

			res._triangles.push_back({ sz - 12, sz - 11, sz - 3 });
			res._triangles.push_back({ sz - 12, sz - 3,  sz - 4 });

			res._triangles.push_back({ sz - 10, sz - 9,  sz - 1 });
			res._triangles.push_back({ sz - 10, sz - 1,  sz - 2 });
		}

		GLuint sz = static_cast<GLuint>(res._vertices.size());

		// Add the Final Face
		Vector3 v1 = Vector3(res._vertices[sz - 8].v1, 0.0f, res._vertices[sz - 8].v3);
		Vector3 v2 = Vector3(res._vertices[sz - 4].v1, 0.0f, res._vertices[sz - 2].v3);
		Vector3 n = Vector3(-res._vertices[sz - 8].v3, 0.0f, res._vertices[sz - 8].v1).normalized();

		res._vertices.push_back({ v1.x(),  height / 2.0f, v1.z(), n.x(), 0.0f, n.z(), 1.0f, 1.0f });
		res._vertices.push_back({ v1.x(), -height / 2.0f, v1.z(), n.x(), 0.0f, n.z(), 1.0f, 0.0f });
		res._vertices.push_back({ v2.x(),  height / 2.0f, v2.z(), n.x(), 0.0f, n.z(), 0.5f, 1.0f });
		res._vertices.push_back({ v2.x(), -height / 2.0f, v2.z(), n.x(), 0.0f, n.z(), 0.5f, 0.0f });

		if (angle < 2.0f * PI)
		{
			res._triangles.push_back({ sz, sz + 1, sz + 2 });
			res._triangles.push_back({ sz + 1, sz + 2, sz + 3 });
		}

		return res;
	}

	Mesh Mesh::ball(size_t level)
	{
		assert(level >= 3);

		if (level % 2 == 1)
		{
			level++;
		}

		Mesh res;

		// Top and Bottom Vertex
		res._vertices =
		{
			{0.0f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f, 0.5f},
			{0.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f}
		};

		for (int i = 1; i <= level; i++)
		{
			for (int j = 0; j <= 2 * level; j++)
			{
				// Add the Vertex to the Mesh
				if (j < level * 2 && i < level)
				{
					float pitch_cos = std::cos(i * PI / level);
					float pitch_sin = std::sin(i * PI / level);
					float yaw_cos = std::cos(j * PI / level);
					float yaw_sin = std::sin(j * PI / level);

					float uv_factor;
					if (i <= (level + 1) / 2)
					{
						uv_factor = static_cast<float>(i) / static_cast<float>((level + 1) / 2);
					}
					else
					{
						uv_factor = 1.0f - static_cast<float>(i % (level / 2)) / static_cast<float>((level + 1) / 2);
					}

					Vector2 uv = uv_factor * 0.5f * Vector2(yaw_cos, yaw_sin) + Vector2(0.5f);
					Vector3 v = Vector3(pitch_sin * yaw_cos, pitch_cos, pitch_sin * yaw_sin) * 0.5f;
					Vector3 n = Vector3(pitch_sin * yaw_cos, pitch_cos, pitch_sin * yaw_sin);

					res._vertices.push_back({ v.x(), v.y(),  v.z(),  n.x(), n.y(),  n.z(), uv.x(), uv.y() });
				}

				GLuint sz = static_cast<GLuint>(res._vertices.size());
				GLuint prev = static_cast<GLuint>(sz - level * 2);
				GLuint prev_2 = static_cast<GLuint>(sz - level * 4);

				// Add the Face Triangles to the Mesh
				if (j > 0)
				{
					if (j < level * 2 && i == 1)
					{
						res._triangles.push_back({ 0, sz - 1, sz - 2 });
					}
					else if (j < level * 2 && i == level)
					{
						res._triangles.push_back({ 1, sz - j, sz - j - 1 });
					}
					else if (j < level * 2)
					{
						res._triangles.push_back({ prev - 1, prev - 2, sz - 1 });
						res._triangles.push_back({ prev - 2, sz - 1,   sz - 2 });
					}
					else if (i == 1)
					{
						res._triangles.push_back({ 0, sz - 1, prev });
					}
					else if (i == level)
					{
						res._triangles.push_back({ 1, sz - 1, prev });
					}
					else
					{
						res._triangles.push_back({ sz - 1, prev - 1, prev });
						res._triangles.push_back({ prev - 1, prev, prev_2 });
					}
				}
			}
		}

		return res;
	}

	Mesh Mesh::sprite(const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor)
	{
		Mesh res;

		res._vertices =
		{
			{ min.x(), min.y(), 0.0f, anchor.x(), anchor.y(), 0.0f, uv_min.x(), uv_min.y() },
			{ min.x(), max.y(), 0.0f, anchor.x(), anchor.y(), 0.0f, uv_min.x(), uv_max.y() },
			{ max.x(), min.y(), 0.0f, anchor.x(), anchor.y(), 0.0f, uv_max.x(), uv_min.y() },
			{ max.x(), max.y(), 0.0f, anchor.x(), anchor.y(), 0.0f, uv_max.x(), uv_max.y() }
		};

		res._triangles =
		{
			{ 0, 1, 2 },
			{ 1, 2, 3 }
		};

		return res;
	}
} // namespace my_engine