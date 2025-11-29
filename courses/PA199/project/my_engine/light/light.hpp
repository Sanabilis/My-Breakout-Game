#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

namespace my_engine
{
	// ==================== //
	// Color Data Structure //
	// ==================== //
	struct Color
	{
		float ar = 0.8f, ag = 0.8f, ab = 0.8f, aa = 1.0f; // Ambient
		float dr = 0.4f, dg = 0.4f, db = 0.4f, da = 1.0f; // Diffuse
		float sr = 1.0f, sg = 1.0f, sb = 1.0f, sa = 1.0f; // Specular
	};



	// =========== //
	// Light Class //
	// =========== //
	class Light
	{
	private:
		// Light Position, Attenuation and Color //
		float _x, _y, _z, _w;
		float _c, _l, _q, _r;
		Color _color;

	public:
		// Constructors //
		Light();
		Light(const Light& light);
		Light(const Vector4& position, const Vector4& attenuation, const Vector4& ambient, const Vector4& diffuse, const Vector4& specular);

		// Getters //
		Vector3 get_position() const;
		Vector4 get_ambient() const;
		Vector4 get_diffuse() const;
		Vector4 get_specular() const;
		float get_constant() const;
		float get_linear() const;
		float get_quadratic() const;
		float get_radius() const;
		bool is_point() const;

		// Setters //
		void set_position(const Vector3& position);
		void set_ambient(const Vector4& color);
		void set_diffuse(const Vector4& color);
		void set_specular(const Vector4& color);
		void set_constant(float constant);
		void set_linear(float linear);
		void set_quadratic(float quadratic);
		void set_radius(float radius);
		void set_point(bool is_point);
	};
} // namespace my_engine