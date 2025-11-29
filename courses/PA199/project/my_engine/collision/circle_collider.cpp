#pragma once

#include "./circle_collider.hpp"
#include "./paddle_collider.hpp"

namespace my_engine
{
	// =============== //
	// Circle Collider //
	// =============== //
	
	// Constructors //
	CircleCollider::CircleCollider() : Collider(), _radius(0.5f) {}
	CircleCollider::CircleCollider(const PolarCoordinates* position, float radius) : Collider(position), _radius(radius) {}


	// Getters //
	float CircleCollider::get_radius() const
	{
		return _radius;
	}


	// Setters //
	void CircleCollider::set_radius(float radius)
	{
		_radius = radius;
	}


	// Collision Methods //
	Vector3 CircleCollider::collide(const CircleCollider& other) const
	{
		return Vector3(0.0f);
	}

	Vector3 CircleCollider::collide(const PaddleCollider& other) const
	{
		Vector2 position = _position->cartesian();
		float distance = _position->get_radius();
		float paddle_distance = other.get_position().get_radius();
		float paddle_thickness = other.get_thickness();
		float paddle_position_angle = other.get_position().get_angle();
		float paddle_angle = 0.5f * other.get_angle();

		if (distance + _radius >= paddle_distance - paddle_thickness / 2.0f && distance - _radius <= paddle_distance + paddle_thickness / 2.0f)
		{
			float difference = std::acos(position.normalized().dot(other.get_position().cartesian().normalized()));

			if (difference < paddle_angle)
			{
				if (distance < paddle_distance)
				{
					return -Vector3(position.x(), 0.0f, position.y()).normalized();
				}
				else
				{
					return Vector3(position.x(), 0.0f, position.y()).normalized();
				}
			}
			else
			{
				float sign;

				Vector2 paddle_pos = other.get_position().cartesian();

				if (-paddle_pos.x() * position.y() + paddle_pos.y() * position.x() <= 0)
				{

					sign = 1.0f;
				}
				else
				{
					sign = -1.0f;
				}

				PolarCoordinates paddle_position = other.get_position();
				paddle_position.set_angle(paddle_position.get_angle() + sign * paddle_angle);

				PolarCoordinates polar_a = paddle_position;
				PolarCoordinates polar_b = paddle_position;

				polar_a.set_radius(polar_a.get_radius() - 0.5f * paddle_thickness);
				polar_b.set_radius(polar_b.get_radius() + 0.5f * paddle_thickness);

				Vector2 a = polar_a.cartesian(), b = polar_b.cartesian();
				Vector2 ab = b - a, ba = a - b;
				Vector2 ac = position - a, bc = position - b;

				float dot_ac = ac.dot(ab.normalized()), dot_bc = bc.dot(ba.normalized());

				if (dot_ac <= 0.0f && ac.magnitude() <= _radius)
				{
					Vector2 normal = ac;
					return Vector3(normal.x(), 0.0f, normal.y()).normalized();
				}
				else if (dot_bc <= 0.0f && bc.magnitude() <= _radius)
				{
					Vector2 normal = bc;
					return Vector3(normal.x(), 0.0f, normal.y()).normalized();
				}
				else if (dot_bc > 0.0f && dot_ac > 0.0f)
				{
					Vector2 point = a + dot_ac * ab.normalized();
					float point_distance = (position - point).magnitude();

					if (point_distance <= _radius)
					{
						Vector2 normal = position - point;
						return Vector3(normal.x(), 0.0f, normal.y()).normalized();
					}
				}
			}
		}

		return Vector3(0.0f);
	}
};