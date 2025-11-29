#include "./scene_object.hpp"

namespace my_engine
{
	// ======================== //
	// Base Scene Object  Class //
	// ======================== //

	SceneObject::SceneObject() : _position(Vector3()), _scale(Vector3(1.0f)), _rotation(Quaternion()) {}
	SceneObject::SceneObject(const Vector3& position, const Vector3& scale, const Quaternion& rotation) :
		_position(position), _scale(scale), _rotation(rotation) {}


	// Getters //
	Vector3 SceneObject::get_position() const
	{
		return _position;
	}

	Vector3 SceneObject::get_scale() const
	{
		return _scale;
	}

	Quaternion SceneObject::get_rotation() const
	{
		return _rotation;
	}

	Matrix4 SceneObject::get_transformation_matrix() const
	{
		return (Matrix4::translate_3d(_position) * _rotation.rotation_matrix() * Matrix4::scale_3d(_scale)).transpose();
	}

	bool SceneObject::destroy() const
	{
		return _destroy;
	}

	bool SceneObject::destroy_on_victory() const
	{
		return true;
	}


	// Setters //
	void SceneObject::set_position(const Vector3& position)
	{
		_position = position;
	}

	void SceneObject::set_scale(const Vector3& scale)
	{
		_scale = scale;
	}

	void SceneObject::set_rotation(const Quaternion& rotation)
	{
		_rotation = rotation;
	}
}