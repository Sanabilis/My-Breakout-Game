#pragma once

#include "./scene_base_object.hpp"
#include "./../mesh/mesh.hpp"

namespace my_engine
{
	class ModelBuffer;

	// ====================== //
	// Scene Class for Models //
	// ====================== //
	class SceneModelObject : public SceneObject
	{
	protected:
		ModelBuffer* _buffer = nullptr;

		Mesh _mesh;
		Material _material;
		GLuint _diffuse_texture;
		GLuint _normal_texture;

	public:
		// Constructors //
		SceneModelObject();
		SceneModelObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
						 const Mesh& mesh, const Material& material, GLuint texture);

		// Getters //
		Mesh& get_mesh();
		const Mesh& get_mesh() const;
		Material& get_material();
		const Material& get_material() const;
		GLuint& get_diffuse_texture();
		GLuint get_diffuse_texture() const;
		GLuint& get_normal_texture();
		GLuint get_normal_texture() const;
		ModelBuffer& get_buffer();
		const ModelBuffer& get_buffer() const;
		virtual bool use_alpha() const;

		// Setters //
		void set_mesh(const Mesh& mesh);
		void set_material(const Material& material);
		void set_ambient(const Vector4& ambient);
		void set_diffuse(const Vector4& diffuse);
		void set_specular(const Vector4& specular);
		void set_roughness(float roughness);
		void set_shininess(float shininess);
		void set_alpha(float alpha);
		virtual void set_diffuse_texture(GLuint texture);
		virtual void set_normal_texture(GLuint texture);
		void set_buffer(ModelBuffer* buffer);

		// Scene Methods //
		virtual void start() override;
		virtual void update(float delta) override;
		virtual void late_update(float delta) override;
		virtual void physics_update(float fixed_delta) override;
	};
}