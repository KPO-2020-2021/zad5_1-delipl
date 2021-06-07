#include "doctest.h"
#include "config.hpp"
#include "Matrixes.hpp"
TEST_CASE("1. Matrix default constructor"){
    CHECK_NOTHROW(Matrix<int, 3, 15> M());
    CHECK_NOTHROW(Matrix2x2 M);
    CHECK_NOTHROW(Matrix3x3 M);

    Matrix2x2 M;
    CHECK(M[0][0] == 0);
    CHECK(M[0][1] == 0);
    CHECK(M[1][0] == 0);
    CHECK(M[1][1] == 0);

    MatrixRot N;
    CHECK(N[0][0] == 1);
    CHECK(N[0][1] == 0);
    CHECK(N[0][2] == 0);

    CHECK(N[1][0] == 0);
    CHECK(N[1][1] == 1);
    CHECK(N[1][2] == 0);

    CHECK(N[2][0] == 0);
    CHECK(N[2][1] == 0);
    CHECK(N[2][2] == 1);

}
TEST_CASE("2. Matrix constructor") {
    Vector2 v({5, 3});
    Vector2 u({6, 4});
    CHECK_NOTHROW(Matrix2x2 M({v, u}));
}
TEST_CASE("3. Matrix cascade operator [n][m]") {
    Vector2 v({5, 3});
    Vector2 u({6, 4});
    Matrix2x2 M({v, u});
    CHECK(M[0][0] == 5);
    CHECK(M[0][1] == 3);
    CHECK(M[1][0] == 6);
    CHECK(M[1][1] == 4);
}
TEST_CASE("4. Matrix * Vector"){
    Matrix2x2 M({Vector2({5, 3}),
                Vector2({2, 1})});
    Vector2 v({0, 1});
    Vector2 u = M*v;
    CHECK(u[0] == 3);
    CHECK(u[1] == 1);


    Matrix3x3 N({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    Vector3 d({11, 12, 13});

    Vector3 z= N*d;    
    CHECK(z[0] == 74);
    CHECK(z[1] == 182);
    CHECK(z[2] == 290);
}
TEST_CASE("5. Matrix operator [] take row"){
    Matrix2x2 M({{5, 3},
                {2, 1}});
    CHECK(M[0] == Vector2({5, 3}));
    CHECK_THROWS(M[2]);
}
TEST_CASE("6. Matrix det"){
    Matrix2x2 R  = {    {2, 3},
                        {5, 1}};
    CHECK(R.Det() == -13); 
}
TEST_CASE("10. Matrix flip function"){
    Matrix<double, 3, 2>  R({{2.0, 3.0},
                             {5.0, 1.0},
                             {6.0, 3.0}});
    Matrix<double, 2 ,3> M({{2.0, 5.0, 6.0},
                            {3.0, 1.0, 3.0}});
    CHECK(M[0] == R.Flip()[0]); 
    CHECK(M[1] == R.Flip()[1]); 
}
TEST_CASE("10. Multiplar Matrix"){
    Matrix<double, 2, 3> M =  {{1,2,3},
                               {4,5,6}};

    Matrix<double,3,2> N = {{7, 8},
                            {9, 10},
                            {11, 12}};
    Matrix<double, 2, 2> W(M*N);
    CHECK(W[0][0] == 58);
    CHECK(W[0][1] == 64);
    CHECK(W[1][0] == 139);
    CHECK(W[1][1] == 154);

    MatrixRot K;
    Matrix3x3 L({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    CHECK(L == K*L);
}

TEST_CASE("11. Matrix operator="){
    Matrix2x2 D({   {2, 1}, {3,7}   });

    D = Matrix2x2();
    CHECK(D[0][0] == 0);
    CHECK(D[0][1] == 0);
    CHECK(D[1][0] == 0);
    CHECK(D[1][1] == 0);
}

TEST_CASE("12. Rotation test"){
    Vector3 v = {1, 0, 0};
    MatrixRot Mx(90, VectorX);
    MatrixRot My(90, VectorY);
    MatrixRot Mz(90, VectorZ);
    CHECK( (Mx * v - VectorX)[2] <= MIN_DIFF);
    CHECK( (Mz * v - VectorY)[2] <= MIN_DIFF);
    CHECK( (Mx * v - VectorX)[1] <= MIN_DIFF);
    CHECK( (Mz * v - VectorY)[1] <= MIN_DIFF);
    CHECK( (Mx * v - VectorX)[0] <= MIN_DIFF);
    CHECK( (Mz * v - VectorY)[0] <= MIN_DIFF);

    CHECK((Mx * Mz * v - VectorZ)[0] <= MIN_DIFF);
    CHECK((Mz * Mx * v - VectorY)[0] <= MIN_DIFF);
    CHECK((Mx * Mz * v - VectorZ)[1] <= MIN_DIFF);
    CHECK((Mz * Mx * v - VectorY)[1] <= MIN_DIFF);
    CHECK((Mx * Mz * v - VectorZ)[2] <= MIN_DIFF);
    CHECK((Mz * Mx * v - VectorY)[2] <= MIN_DIFF);
}

// TEST_CASE("TEST matrixt rot"){
//     MatrixRot M;
//     MatrixRot N(90, VectorX);
//     // std::cout << M << std::endl << N << std::endl << N * M;
// }

TEST_CASE("MatrixTransformation"){
    MatrixTransform M({0, 0, 0}, {0, 0, 0}, {1, 1, 1});
    CHECK(M[0][3] == 0);
    CHECK(M[1][3] == 0);
    CHECK(M[2][3] == 0);
    CHECK(M[3][3] == 1);
    Vector4 v = {1, 1, 1, 1};
    Vector4 w = {1, 1, 1, 1};
    CHECK(w == M * v);

    MatrixTransform N({50, 60, 70}, {0, 0, 0}, {1, 1, 1});

    CHECK(N[0][3] == 50);
    CHECK(N[1][3] == 60);
    CHECK(N[2][3] == 70);
    CHECK(N[3][3] == 1);
    Vector4 x = {51, 61, 71, 1};
    CHECK(x == N * v);

    MatrixTransform O({0, 0, 0}, {0, 0, 90}, {1, 1, 1});
    Vector4 y = {-1, 1, 1, 1};
    CHECK(y == O * v);

    MatrixTransform P({119, 89, 49}, {0, 0, 90}, {1, 1, 1});
    Vector4 z = {118, 90, 50, 1};

    CHECK(z == P * v);

    MatrixTransform R({0, 0, 0}, {0, 0, 0}, {0, 0, 0});
    CHECK(R * v == Vector4({0, 0, 0, 1}));

    MatrixTransform Q({0, 0, 0}, {0, 0, 0}, {2, 2, 2});
    CHECK( Q*v == Vector4({2, 2, 2, 1}));


    MatrixTransform S({0, 0, 0}, {0, 0, -90}, {1, 1, 1});


    Vector4 a = {1, -1, 1, 1};


    CHECK(a == S * v);
}