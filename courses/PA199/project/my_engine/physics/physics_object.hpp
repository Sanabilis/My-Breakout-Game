#pragma once

#include "./../../libraries/my_engine_math/my_engine_math.hpp"

namespace my_engine
{
	// ========================= //
	// Base Physics Object Class //
	// ========================= //
	class PhysicsObject
	{
	public:
		static float outer_radius;
		static float inner_radius;

	protected:
		PolarCoordinates _position;
		Vector3 _direction;

		float _velocity;
		float _bounce_factor;

	public:
		// Constructors //
		PhysicsObject();
		PhysicsObject(const Vector3& position, const Vector3& direction, float velocity, float bounce_factor, bool y_ignore);

		// Getters //
		const PolarCoordinates& get_position() const;
		Vector3 get_cartesian_position() const;
		const Vector3& get_direction() const;
		float get_velocity() const;
		float get_bounce_factor() const;

		// Setters //
		void set_position(const PolarCoordinates& position);
		void set_position(const Vector3& position);
		void set_direction(const Vector3& direction);
		void set_velocity(float velocity);
		void set_bounce_factor(float bounce_factor);

		// Movement Methods //
		virtual void move(float delta);
		virtual void bounce(const Vector3& normal);

		// Ordinary Differential Equations Solvers //
		template <size_t size, typename F_y>
		static std::pair<Vector<size>, Vector<size>> euler_forward(std::pair<Vector<size>, Vector<size>> y, F_y f, float t, float d_t);

		template <size_t size, typename F_y>
		static std::pair<Vector<size>, Vector<size>> midpoint(std::pair<Vector<size>, Vector<size>> y, F_y f, float t, float d_t);
	};

	// Ordinary Differential Equations Solvers //
	template <size_t size, typename F_y>
	std::pair<Vector<size>, Vector<size>> PhysicsObject::euler_forward(std::pair<Vector<size>, Vector<size>> y, F_y f, float t, float d_t)
	{
		std::pair<Vector<size>, Vector<size>> y_0 = f(y, t);

		return { y.first + d_t * y_0.first, y.second + d_t * y_0.second };
	}

	template <size_t size, typename F_y>
	std::pair<Vector<size>, Vector<size>> PhysicsObject::midpoint(std::pair<Vector<size>, Vector<size>> y, F_y f, float t, float d_t)
	{
		std::pair<Vector<size>, Vector<size>> y_0 = f(y, t);
		std::pair<Vector<size>, Vector<size>> y_1 = f({ y.first + 0.5f * d_t * y_0.first, y.second + 0.5f * d_t * y_0.second }, t + d_t);

		return { y.first + d_t * y_1.first, y.second + d_t * y_1.second };
	}
} // namespace my_engine