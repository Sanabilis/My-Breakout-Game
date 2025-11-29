#include "./scene_model_object.hpp"
#include "./../buffers/model_buffer.hpp"

namespace my_engine
{
	// ====================== //
	// Scene Class for Models //
	// ====================== //

	// Constructors //
	SceneModelObject::SceneModelObject() : SceneObject()
	{
		_mesh = Mesh();
		_material =
		{
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			8.0f, 0.5f, 1.0f
		};

		_diffuse_texture = 0;
		_normal_texture = 0;
		_buffer = nullptr;
	}

	SceneModelObject::SceneModelObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation,
		const Mesh& mesh, const Material& material, GLuint texture) : SceneObject(position, scale, rotation)
	{
		_mesh = Mesh(mesh);
		_material = material;
		_diffuse_texture = texture;
		_normal_texture = 0;
		_buffer = nullptr;
	}


	// Getters //
	Mesh& SceneModelObject::get_mesh()
	{
		return _mesh;
	}

	const Mesh& SceneModelObject::get_mesh() const
	{
		return _mesh;
	}

	Material& SceneModelObject::get_material()
	{
		return _material;
	}

	const Material& SceneModelObject::get_material() const
	{
		return _material;
	}

	GLuint& SceneModelObject::get_diffuse_texture()
	{
		return _diffuse_texture;
	}

	GLuint SceneModelObject::get_diffuse_texture() const
	{
		return _diffuse_texture;
	}

	GLuint& SceneModelObject::get_normal_texture()
	{
		return _normal_texture;
	}

	GLuint SceneModelObject::get_normal_texture() const
	{
		return _normal_texture;
	}

	ModelBuffer& SceneModelObject::get_buffer()
	{
		return *_buffer;
	}

	const ModelBuffer& SceneModelObject::get_buffer() const
	{
		return *_buffer;
	}

	bool SceneModelObject::use_alpha() const
	{
		return false;
	}


	// Setters //
	void SceneModelObject::set_mesh(const Mesh& mesh)
	{
		_mesh = Mesh(mesh);

		_buffer->update_vertex_buffer();
		_buffer->update_index_buffer();
	}
	
	void SceneModelObject::set_material(const Material& material)
	{
		_material = material;

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_ambient(const Vector4& color)
	{
		_material.ar = color.x();
		_material.ag = color.y();
		_material.ab = color.z();
		_material.aa = color.w();

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_diffuse(const Vector4& color)
	{
		_material.dr = color.x();
		_material.dg = color.y();
		_material.db = color.z();
		_material.da = color.w();

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_specular(const Vector4& color)
	{
		_material.sr = color.x();
		_material.sg = color.y();
		_material.sb = color.z();
		_material.sa = color.w();

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_shininess(float s)
	{
		_material.shininess = s;

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_roughness(float r)
	{
		_material.roughness = r;

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_alpha(float a)
	{
		_material.alpha = a;

		_buffer->update_material_buffer();
	}

	void SceneModelObject::set_diffuse_texture(GLuint texture)
	{
		_diffuse_texture = texture;
	}

	void SceneModelObject::set_normal_texture(GLuint texture)
	{
		_normal_texture = texture;
	}

	void SceneModelObject::set_buffer(ModelBuffer* buffer)
	{
		if (buffer->get_model() == nullptr)
		{
			_buffer = buffer;
			_buffer->set_model(this);
			_buffer->init_buffers();
		}
	}


	// Scene Methods //
	void SceneModelObject::start() {}
	void SceneModelObject::update(float delta) {}
	void SceneModelObject::late_update(float delta) {}
	void SceneModelObject::physics_update(float delta) {}
}