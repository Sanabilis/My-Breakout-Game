#include "light.hpp"

namespace my_engine
{
	// =========== //
	// Light Class //
	// =========== //
	
	// Constructors //
	Light::Light()
	{
		_x = 0.0f;
		_y = 1.0f;
		_z = 0.0f;
		_w = 0.0f;

		_c = 1.0f;
		_l = 0.0f;
		_q = 0.0f;
		_r = 0.0f;

		_color =
		{
			0.2f, 0.2f, 0.2f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};
	}

	Light::Light(const Light& light)
	{
		_x = light._x;
		_y = light._y;
		_z = light._z;
		_w = light._w;

		_c = light._c;
		_l = light._l;
		_q = light._q;
		_r = light._r;

		_color = light._color;
	}

	Light::Light(const Vector4& position, const Vector4& attenuation, const Vector4& ambient, const Vector4& diffuse, const Vector4& specular)
	{
		_x = position.x();
		_y = position.y();
		_z = position.z();
		_w = position.w();

		_c = attenuation.x();
		_l = attenuation.y();
		_q = attenuation.z();
		_r = attenuation.w();

		_color =
		{
			ambient.x(),  ambient.y(),  ambient.z(),  ambient.w(),
			diffuse.x(),  diffuse.y(),  diffuse.z(),  diffuse.w(),
			specular.x(), specular.y(), specular.z(), specular.w()
		};
	}


	// Getters //
	Vector3 Light::get_position() const
	{
		return Vector3(_x, _y, _z);
	}

	Vector4 Light::get_ambient() const
	{
		return Vector4(_color.ar, _color.ag, _color.ab, _color.aa);
	}

	Vector4 Light::get_diffuse() const
	{
		return Vector4(_color.dr, _color.dg, _color.db, _color.da);
	}

	Vector4 Light::get_specular() const
	{
		return Vector4(_color.sr, _color.sg, _color.sb, _color.sa);
	}

	float Light::get_constant() const
	{
		return _c;
	}

	float Light::get_linear() const
	{
		return _l;
	}

	float Light::get_quadratic() const
	{
		return _q;
	}

	float Light::get_radius() const
	{
		return _r;
	}

	bool Light::is_point() const
	{
		return _w != 0.0f;
	}


	// Setters //
	void Light::set_position(const Vector3& position)
	{
		_x = position.x();
		_y = position.y();
		_z = position.z();
	}

	void Light::set_ambient(const Vector4& color)
	{
		_color.ar = color.x();
		_color.ag = color.y();
		_color.ab = color.z();
		_color.aa = color.w();
	}

	void Light::set_diffuse(const Vector4& color)
	{
		_color.dr = color.x();
		_color.dg = color.y();
		_color.db = color.z();
		_color.da = color.w();
	}

	void Light::set_specular(const Vector4& color)
	{
		_color.sr = color.x();
		_color.sg = color.y();
		_color.sb = color.z();
		_color.sa = color.w();
	}

	void Light::set_constant(float color)
	{
		_c = color;
	}

	void Light::set_linear(float linear)
	{
		_l = linear;
	}

	void Light::set_quadratic(float quadratic)
	{
		_q = quadratic;
	}

	void Light::set_radius(float radius)
	{
		_r = radius;
	}

	void Light::set_point(bool is_point)
	{
		if (is_point)
		{
			_w = 1.0f;
		}
		else
		{
			_w = 0.0f;
		}
	}
} // namespace my_engine