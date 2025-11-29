#pragma once

#include "./scene_base_object.hpp"
#include "./../light/light.hpp"

namespace my_engine
{
	class LightBuffer;

	// ============================== //
	// Scene Object Class for Cameras //
	// ============================== //
	class SceneLightObject : public SceneObject
	{
	protected:
		friend class LightBuffer;

		LightBuffer* _buffer = nullptr;

		std::unique_ptr<Light> _light;
		size_t _index = 0;

	public:
		// Constructors //
		SceneLightObject();
		SceneLightObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation, const Light& light);

		// Getters //
		Light& get_light();
		const Light& get_light() const;
		LightBuffer& get_buffer();
		const LightBuffer& get_buffer() const;
		size_t get_index() const;
		Vector4 get_ambient() const;
		Vector4 get_diffuse() const;
		Vector4 get_specular() const;
		float get_constant() const;
		float get_linear() const;
		float get_quadratic() const;
		float get_radius() const;
		bool is_point() const;

		// Setters //
		void set_position(const Vector3& position) override;
		void set_ambient(const Vector4& color);
		void set_diffuse(const Vector4& color);
		void set_specular(const Vector4& color);
		void set_constant(float constant);
		void set_linear(float linear);
		void set_quadratic(float quadratic);
		void set_radius(float radius);
		void set_point(bool is_point);
		void set_buffer(LightBuffer* buffer);

		// Scene Methods //
		virtual void start() override;
		virtual void update(float delta) override;
		virtual void late_update(float delta) override;
		virtual void physics_update(float fixed_delta) override;
	};
}