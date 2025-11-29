#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace my_engine
{
	// ===================== //
	// Vertex Data Structure //
	// ===================== //
	struct Vertex
	{
		// Structure to Store Data about the Vertex
		float v1, v2, v3; // Vertex Position
		float n1, n2, n3; // Vertex Normal
		float u, v;		  // Vertex Texture Coordinates

		// Constructor //
		// Vertex(const Mesh& m, size_t index);
	};



	// ===================== //
	// Vertex Data Structure //
	// ===================== //
	struct Triangle
	{
		GLuint p1, p2, p3;
	};



	// ======================= //
	// Material Data Structure //
	// ======================= //
	struct Material
	{
		// Color //
		float ar = 0.8f, ag = 0.8f, ab = 0.8f, aa = 1.0f; // Ambient
		float dr = 0.8f, dg = 0.8f, db = 0.8f, da = 1.0f; // Diffuse
		float sr = 1.0f, sg = 1.0f, sb = 1.0f, sa = 1.0f; // Specular

		// Surface Properties //
		float shininess = 8.0f;
		float roughness = 0.25f;
		float alpha = 1.0f;

		static Material DEFAULT_MATERIAL;
	};



	// ========== //
	// Mesh Class //
	// ========== //
	class Mesh
	{
	private:
		std::vector<Vertex> _vertices;
		std::vector<Triangle> _triangles;

	public:
		// Constructors //
		Mesh();
		Mesh(const Mesh& m);

		// Getters //
		const std::vector<Vertex>& get_vertices() const;
		const std::vector<Triangle>& get_triangles() const;
		const Vertex& get_vertex(size_t index) const;
		const Triangle& get_triangle(size_t index) const;
		Vertex& get_vertex(size_t index);
		Triangle& get_triangle(size_t index);

		// Assignment Operator //
		Mesh& operator=(const Mesh& m);

		// Number of Vertices / Triangles //
		size_t vertices_count() const;
		size_t triangles_count() const;

		// Static Methods to Generate Mesh //
		static Mesh cube();
		static Mesh plane(size_t level);
		static Mesh paddle(size_t level, float angle, float width, float height);
		static Mesh ball(size_t level);
		static Mesh sprite(const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor);
	};
} // namespace my_engine