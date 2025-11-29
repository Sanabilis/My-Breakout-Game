#include "./../libraries/my_engine_math/my_engine_math.hpp"
#include "./../my_engine/my_engine.hpp"

#include <gtest/gtest.h>



// ============ //
// Vector Tests //
// ============ //

// Constructors Tests //
TEST(test_suite, vector_constructors_test)
{
    // Vector2
    EXPECT_EQ(my_engine::Vector2(), my_engine::Vector2(0.f));
    EXPECT_EQ(my_engine::Vector2(), my_engine::Vector2::ZERO);
    EXPECT_EQ(my_engine::Vector2(), my_engine::Vector2(0.f, 0.f));
    EXPECT_EQ(my_engine::Vector2(1.5f), my_engine::Vector2(1.5f, 1.5f));

    // Vector3
    EXPECT_EQ(my_engine::Vector3(), my_engine::Vector3(0.f));
    EXPECT_EQ(my_engine::Vector3(), my_engine::Vector3::ZERO);
    EXPECT_EQ(my_engine::Vector3(), my_engine::Vector3(0.f, 0.f, 0.f));
    EXPECT_EQ(my_engine::Vector3(1.5f), my_engine::Vector3(1.5f, 1.5f, 1.5f));
    EXPECT_EQ(my_engine::Vector3(my_engine::Vector2(1.5f, 3.f), 4.5f), my_engine::Vector3(1.5f, 3.f, 4.5f));

    // Vector4
    EXPECT_EQ(my_engine::Vector4(), my_engine::Vector4(0.f));
    EXPECT_EQ(my_engine::Vector4(), my_engine::Vector4::ZERO);
    EXPECT_EQ(my_engine::Vector4(), my_engine::Vector4(0.f, 0.f, 0.f, 0.f));
    EXPECT_EQ(my_engine::Vector4(1.5f), my_engine::Vector4(1.5f, 1.5f, 1.5f, 1.5f));
    EXPECT_EQ(my_engine::Vector4(my_engine::Vector3(1.5f, 3.f, 4.5f), 6.f), my_engine::Vector4(1.5f, 3.f, 4.5f, 6.f));
}

// Arithmetic Operators Tests //
TEST(test_suite, vector_arithmetic_test)
{
    // Vector2
    EXPECT_EQ(my_engine::Vector2(2.f, 2.f) + my_engine::Vector2(1.f, -1.f), my_engine::Vector2(3.f, 1.f));
    EXPECT_EQ(my_engine::Vector2(2.f, 2.f) - my_engine::Vector2(1.f, -1.f), my_engine::Vector2(1.f, 3.f));
    EXPECT_EQ(my_engine::Vector2(2.f, 2.f) + -my_engine::Vector2(1.f, -1.f), my_engine::Vector2(1.f, 3.f));
    EXPECT_EQ(my_engine::Vector2(2.f, 2.f) + 2.f * my_engine::Vector2(1.f, -1.f), my_engine::Vector2(4.f, 0.f));
    EXPECT_EQ(my_engine::Vector2(2.f, 2.f) + my_engine::Vector2(1.f, -1.f) * 2.f, my_engine::Vector2(4.f, 0.f));
    EXPECT_EQ(my_engine::Vector2(2.f, 2.f) + my_engine::Vector2(1.f, -1.f) / 2.f, my_engine::Vector2(2.5f, 1.5f));

    // Vector3
    EXPECT_EQ(my_engine::Vector3(2.f, 2.f, 2.f) + my_engine::Vector3(1.f, -1.f, 2.f), my_engine::Vector3(3.f, 1.f, 4.f));
    EXPECT_EQ(my_engine::Vector3(2.f, 2.f, 2.f) - my_engine::Vector3(1.f, -1.f, 2.f), my_engine::Vector3(1.f, 3.f, 0.f));
    EXPECT_EQ(my_engine::Vector3(2.f, 2.f, 2.f) + -my_engine::Vector3(1.f, -1.f, 2.f), my_engine::Vector3(1.f, 3.f, 0.f));
    EXPECT_EQ(my_engine::Vector3(2.f, 2.f, 2.f) + 2.f * my_engine::Vector3(1.f, -1.f, 2.f), my_engine::Vector3(4.f, 0.f, 6.f));
    EXPECT_EQ(my_engine::Vector3(2.f, 2.f, 2.f) + my_engine::Vector3(1.f, -1.f, 2.f) * 2.f, my_engine::Vector3(4.f, 0.f, 6.f));
    EXPECT_EQ(my_engine::Vector3(2.f, 2.f, 2.f) + my_engine::Vector3(1.f, -1.f, 2.f) / 2.f, my_engine::Vector3(2.5f, 1.5f, 3.f));

    // Vector4
    EXPECT_EQ(my_engine::Vector4(2.f, 2.f, 2.f, 2.f) + my_engine::Vector4(1.f, -1.f, 2.f, -2.f), my_engine::Vector4(3.f, 1.f, 4.f, 0.f));
    EXPECT_EQ(my_engine::Vector4(2.f, 2.f, 2.f, 2.f) - my_engine::Vector4(1.f, -1.f, 2.f, -2.f), my_engine::Vector4(1.f, 3.f, 0.f, 4.f));
    EXPECT_EQ(my_engine::Vector4(2.f, 2.f, 2.f, 2.f) + -my_engine::Vector4(1.f, -1.f, 2.f, -2.f), my_engine::Vector4(1.f, 3.f, 0.f, 4.f));
    EXPECT_EQ(my_engine::Vector4(2.f, 2.f, 2.f, 2.f) + 2.f * my_engine::Vector4(1.f, -1.f, 2.f, -2.f), my_engine::Vector4(4.f, 0.f, 6.f, -2.f));
    EXPECT_EQ(my_engine::Vector4(2.f, 2.f, 2.f, 2.f) + my_engine::Vector4(1.f, -1.f, 2.f, -2.f) * 2.f, my_engine::Vector4(4.f, 0.f, 6.f, -2.f));
    EXPECT_EQ(my_engine::Vector4(2.f, 2.f, 2.f, 2.f) + my_engine::Vector4(1.f, -1.f, 2.f, -2.f) / 2.f, my_engine::Vector4(2.5f, 1.5f, 3.f, 1.f));
}

// Vector Operations Tests //
TEST(test_suite, vector_operations_test)
{
    // Dot Product
    EXPECT_FLOAT_EQ(my_engine::Vector3(2.f).dot(my_engine::Vector3(1.f, 1.f, 1.f)), 6.f);
    EXPECT_FLOAT_EQ(my_engine::Vector3(2.f).dot(my_engine::Vector3(2.f)), std::pow(my_engine::Vector3(2.f).magnitude(), 2));
    EXPECT_FLOAT_EQ(my_engine::Vector3(1.f).dot(my_engine::Vector3(1.f)) / std::pow(my_engine::Vector3(1.f).magnitude(), 2), 1.f);

    // Cross Product
    EXPECT_FLOAT_EQ(my_engine::Vector3(1.f).dot(my_engine::Vector3(1.f).cross(my_engine::Vector3(1.5f, 0.f, -1.f))), 0.f);
    EXPECT_FLOAT_EQ(my_engine::Vector3(1.5f, 0.f, -1.f).dot(my_engine::Vector3(1.f).cross(my_engine::Vector3(1.5f, 0.f, -1.f))), 0.f);
    EXPECT_EQ(my_engine::Vector3(1.f).cross(my_engine::Vector3(1.5f, 0.f, -1.f)), -my_engine::Vector3(1.5f, 0.f, -1.f).cross(my_engine::Vector3(1.f)));

    // Vector Magnitude + Normalization
    EXPECT_FLOAT_EQ(my_engine::Vector3(1.f).magnitude(), std::sqrt(3.f));
    EXPECT_FLOAT_EQ(my_engine::Vector3(1.f, 5.f, -2.f).normalized().magnitude(), 1.f);
    EXPECT_FLOAT_EQ(my_engine::Vector3(1.f, 5.f, -2.f).magnitude(), my_engine::Vector3(-1.f, -5.f, 2.f).magnitude());
}



// ============ //
// Matrix Tests //
// ============ //

// !! NEEDS ADITIONAL TESTING !! //
TEST(test_suite, matrix_tests)
{
    my_engine::Matrix3 m1({ my_engine::Vector3(1.f, 2.f, 1.f), my_engine::Vector3(1.f), my_engine::Vector3(-1.f, 4.f, 7.f) });
    EXPECT_EQ(m1.transpose().transpose(), m1);
    EXPECT_EQ(m1.inverse() * m1, my_engine::Matrix3::IDENTITY);
    EXPECT_EQ(m1.inverse() * m1 * my_engine::Vector3(1.f, 7.f, -2.f), my_engine::Vector3(1.f, 7.f, -2.f));
}



// ============== //
// Rotation Tests //
// ============== //

// Vector Rotation Tests //
TEST(test_suite, rotation_tests)
{
    my_engine::AxisAngle ax_a(my_engine::PI / 2.f, my_engine::Vector3::UP);
    my_engine::Quaternion q = ax_a.quaternion();

    my_engine::Vector4 v1 = q.rotation_matrix() * my_engine::Vector4(1.f, 0.f, 0.f, 0.f);
    my_engine::Vector3 v2 = v1.xyz();

    // Rotation
    EXPECT_EQ(ax_a.rotate(my_engine::Vector3(1.f, 0.f, 0.f)), q.rotate(my_engine::Vector3(1.f, 0.f, 0.f)));
    EXPECT_EQ(ax_a.rotate(my_engine::Vector3(1.f, 0.f, 0.f)), v2);
    EXPECT_EQ(ax_a.rotate(my_engine::Vector3(1.f, 0.f, 0.f)), my_engine::Vector3(0.f, 0.f, -1.f));
    EXPECT_EQ(ax_a.rotate(my_engine::Vector3(0.f, 1.f, 0.f)), my_engine::Vector3(0.f, 1.f, 0.f));
    EXPECT_EQ(q.rotate(my_engine::Vector3(0.f, 1.f, 0.f)), my_engine::Vector3(0.f, 1.f, 0.f));

    // Interpolation
    my_engine::Quaternion q1(my_engine::PI / 2.f, my_engine::Vector3(std::sqrt(2.f) / 2.f, 0.f, std::sqrt(2.f) / 2.f));
    my_engine::Quaternion q2(my_engine::PI / 2.f, my_engine::Vector3(-std::sqrt(2.f) / 2.f, 0.f, std::sqrt(2.f) / 2.f));
}


// Quaternion Interpolation Tests //
TEST(test_suite, interpolation_test)
{
    my_engine::Quaternion q1(my_engine::PI / 2.f, my_engine::Vector3(std::sqrt(2.f) / 2.f, 0.f, std::sqrt(2.f) / 2.f));
    my_engine::Quaternion q2(my_engine::PI / 2.f, my_engine::Vector3(-std::sqrt(2.f) / 2.f, 0.f, std::sqrt(2.f) / 2.f));

    // Lerp
    EXPECT_EQ(q1.lerp(q2, 0.f), q1);
    EXPECT_EQ(q1.lerp(q2, 1.f), q2);
    EXPECT_EQ(q1.lerp(q2, 0.f), q2.lerp(q1, 1.f));
    EXPECT_EQ(q1.lerp(q2, 0.25f), q2.lerp(q1, 0.75f));
    EXPECT_EQ(q1.lerp(q2, 0.5f), q2.lerp(q1, 0.5f));
    EXPECT_EQ(q1.lerp(q2, 0.75f), q2.lerp(q1, 0.25f));
    EXPECT_EQ(q1.lerp(q2, 1.f), q2.lerp(q1, 0.f));

    // Slerp
    EXPECT_EQ(q1.slerp(q2, 0.f), q1);
    EXPECT_EQ(q1.slerp(q2, 1.f), q2);
    EXPECT_EQ(q1.slerp(q2, 0.f), q2.slerp(q1, 1.f));
    EXPECT_EQ(q1.slerp(q2, 0.25f), q2.slerp(q1, 0.75f));
    EXPECT_EQ(q1.slerp(q2, 0.5f), q2.slerp(q1, 0.5f));
    EXPECT_EQ(q1.slerp(q2, 0.75f), q2.slerp(q1, 0.25f));
    EXPECT_EQ(q1.slerp(q2, 1.f), q2.slerp(q1, 0.f));

    // Lerp and Slerp "Equivalence"
    EXPECT_EQ(q1.lerp(q2, 0.5f).normalized(), q1.slerp(q2, 0.5f));
}



// ======================= //
// Polar Coordinates Tests //
// ======================= //

TEST(test_suite, polar_coordinates_tests)
{
    my_engine::PolarCoordinates pc1(std::sqrt(2.0f), my_engine::PI / 4.0f);
    my_engine::PolarCoordinates pc2(std::sqrt(2.0f),  2.0f * my_engine::PI + my_engine::PI / 4.0f);
    my_engine::PolarCoordinates pc3(std::sqrt(2.0f), -2.0f * my_engine::PI + my_engine::PI / 4.0f);
    my_engine::PolarCoordinates pc4(my_engine::Vector2(1.0f, 1.0f));
    my_engine::PolarCoordinates pc5(my_engine::Vector3(1.0f, 5.0f, 1.0f));
    my_engine::PolarCoordinates pc6(my_engine::Vector2(1.0f, -1.0f));

    // Radius //
    EXPECT_FLOAT_EQ(pc1.get_radius(), pc2.get_radius());
    EXPECT_FLOAT_EQ(pc1.get_radius(), pc3.get_radius());
    EXPECT_FLOAT_EQ(pc1.get_radius(), pc4.get_radius());
    EXPECT_FLOAT_EQ(pc1.get_radius(), pc5.get_radius());
    EXPECT_FLOAT_EQ(pc1.get_radius(), pc6.get_radius());

    // Angle //
    EXPECT_FLOAT_EQ(pc1.get_angle(), pc2.get_angle());
    EXPECT_FLOAT_EQ(pc1.get_angle(), pc3.get_angle());
    EXPECT_FLOAT_EQ(pc1.get_angle(), pc4.get_angle());
    EXPECT_FLOAT_EQ(pc1.get_angle(), pc5.get_angle());
    EXPECT_FLOAT_EQ(2.0f * my_engine::PI - pc1.get_angle(), pc6.get_angle());

    // Cartesian Coordinates //
    EXPECT_EQ(pc4.cartesian(), my_engine::Vector2(1.0f,  1.0f));
    EXPECT_EQ(pc6.cartesian(), my_engine::Vector2(1.0f, -1.0f));
}


std::pair<my_engine::Vector3, my_engine::Vector3> func(std::pair<my_engine::Vector3, my_engine::Vector3> pair, float t)
{
    return { pair.second, -my_engine::Vector3(0.0f, 9.8f, 0.0f) };
}


// ================ //
// ODE Solver Tests //
// ================ //

TEST(test_suite, ode_solver_tests)
{
    std::pair<my_engine::Vector<3>, my_engine::Vector<3>> y_euler(my_engine::Vector<3>(0.0f), my_engine::Vector<3>({ 1.0f, 1.0f, 0.0f }));
    std::pair<my_engine::Vector<3>, my_engine::Vector<3>> y_midpoint(my_engine::Vector<3>(0.0f), my_engine::Vector<3>({ 1.0f, 1.0f, 0.0f }));

    float d_t = 0.1f;
    float t = 0.0f;

    while (t <= 2.0f)
    {
        y_euler = my_engine::PhysicsObject::euler_forward(y_euler, func, t, d_t);
        y_midpoint = my_engine::PhysicsObject::midpoint(y_midpoint, func, t, d_t);

        t += d_t;
    }

    std::cout << std::endl << "Time: " << t << ", Delta: " << d_t << std::endl << "Position Forward Euler: ";
    y_euler.first.print();
    std::cout << std::endl << "Velocity Forward Euler: ";
    y_euler.second.print();

    std::cout << std::endl << "Position Midpoint: ";
    y_midpoint.first.print();
    std::cout << std::endl << "Velocity Midpoint: ";
    y_midpoint.second.print();
    std::cout << std::endl << std::endl;
}