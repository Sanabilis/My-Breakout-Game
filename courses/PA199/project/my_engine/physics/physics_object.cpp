#include "./physics_object.hpp"

namespace my_engine
{
	// ========================= //
	// Base Physics Object Class //
	// ========================= //

	// Constructors //
	PhysicsObject::PhysicsObject() : _position(Vector3(0.0f)), _direction(Vector3(0.0f)), _velocity(0.0f), _bounce_factor(1.0f) {}
	PhysicsObject::PhysicsObject(const Vector3& position, const Vector3& direction, float velocity, float bounce_factor, bool y_ignore) :
		_position(position), _direction(direction.normalized()), _velocity(velocity), _bounce_factor(bounce_factor) {}


	// Getters //
	const PolarCoordinates& PhysicsObject::get_position() const
	{
		return _position;
	}

	Vector3 PhysicsObject::get_cartesian_position() const
	{
		return Vector3(_position.cartesian().x(), 0.0f, _position.cartesian().y());
	}

	const Vector3& PhysicsObject::get_direction() const
	{
		return _direction;
	}

	float PhysicsObject::get_velocity() const
	{
		return _velocity;
	}

	float PhysicsObject::get_bounce_factor() const
	{
		return _bounce_factor;
	}


	// Setters //
	void PhysicsObject::set_position(const Vector3& position)
	{
		_position = position;
	}

	void PhysicsObject::set_position(const PolarCoordinates& position)
	{
		_position = position;
	}

	void PhysicsObject::set_direction(const Vector3& direction)
	{
		_direction = Vector3(direction.x(), 0.0f, direction.z()).normalized();
	}

	void PhysicsObject::set_velocity(float velocity)
	{
		_velocity = velocity;
	}

	void PhysicsObject::set_bounce_factor(float bounce_factor)
	{
		_bounce_factor = bounce_factor;
	}


	// Movement Methods //
	void PhysicsObject::move(float delta)
	{
		_position = static_cast<Vector2>(_position.cartesian() + _direction.xz() * _velocity * delta);
	}

	void PhysicsObject::bounce(const Vector3& normal)
	{
		_direction -= 2.0f * _direction.dot(normal) * normal.normalized();
		_direction = _direction.normalized();
		_velocity *= _bounce_factor;
	}
} // namespace my_engine