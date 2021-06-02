#include "doctest.h"
#include "Vectors.hpp"

TEST_CASE("1. Vector default constructor"){  
    CHECK_NOTHROW(Vector2 w);
    CHECK_NOTHROW(Vector3 w);
    CHECK_NOTHROW(Vector<float, 15> w);
    Vector3 w;
    CHECK(w[0] == 0.0);
    CHECK(w[1] == 0.0);
    CHECK(w[2] == 0.0);
}
TEST_CASE("2. Vector linitializer list constructor"){
    Vector2 u = {9, 4};
    CHECK(u[0] == 9);
    CHECK(u[1] == 4);
    Vector2 v({5.0, 6.0});
    CHECK(v[0] == 5.0);
    CHECK(v[1] == 6.0);
    CHECK_THROWS_AS(Vector3 u({5.0, 3, 6, 7}), std::out_of_range);
}
TEST_CASE("3. Vector 2 dim of Vector"){
    Vector2 v({5, 3});
    Vector2 u({9, 4});
    Vector<Vector2, 2> w({v, u});
    CHECK(w[0] == v);
    CHECK(w[1] == u);
}
TEST_CASE("3. Vector 2 dim constructor with tab"){
    Vector2 x({6, 9});
    CHECK_THROWS(x[2] == 6);
    CHECK_THROWS(x[-2] == 6);
}
TEST_CASE("4. Vector == and !=operator"){
    Vector3 v({5, -9, 3});
    Vector3 u(v);
    Vector3 x = {9, 3, 5};
    CHECK(v == u);
    CHECK(v != x);
}
TEST_CASE("5. Vector Length"){
    Vector2 u({4, 3});
    Vector<int, 4> v({8, -6, 5, 10});
    CHECK(u.Length() == 5);
    CHECK(v.Length() == 15);
}
TEST_CASE("6. Vector substraction and addition"){
    Vector2 u({4, 3});
    Vector2 z({6, -9});
    Vector2 v({10, -6});
    Vector2 x({-2, 12});
    CHECK(u + z == v);
    CHECK(u - z == x);
}
TEST_CASE("7. Vector multiplication and division")
{
    Vector2 u({4.0, -3.0});
    Vector2 x({-2.0, 1.5});
    Vector2 v({-8.0, 6.0});
    double z = -0.5;
    CHECK(u * z == x);
    CHECK(u / z == v);
}
TEST_CASE("8. Vector Dot product Vector by Vector") {
    Vector2 u({4.0, -3.0});
    Vector2 x({-2.0, 1.5});
    double z = -12.5;
    CHECK((u & x) == z);
}
// TEST_CASE("9. Vector CrossPrepare of 3x3"){
//     Vector3 v({4, 4, 0});
//     Vector3 u({6, 4, 0});
//     Vector3 x = v * u;
//     Vector3 w({0, 0, -8});
//     CHECK(x == w);

//     // Compilation Error
//     // Vector<double, 4> a({4, 4, 0, 5});
//     // Vector<double, 4> b({4, 4, 0, 5});
//     // a * b;

//     // Compilation Error
//     // Vector2 a({4, 4});
//     // Vector2 b({4, 4});
//     // a * b;
// }
TEST_CASE("10. Vector input"){
    std::istringstream cin("5 30 10");
    Vector3 v;
    CHECK_NOTHROW(cin >> v);
    std::istringstream cin2("5 30 10");
    cin2 >> v;
    CHECK(v[0] == 5);
    CHECK(v[1] == 30);
    CHECK(v[2] == 10);
}