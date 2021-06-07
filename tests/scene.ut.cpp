#include "Scene.hpp"

#include <limits>

#include "doctest.h"
extern bool DISPLAY;

TEST_CASE("1. Scene constructor") {
    CHECK_NOTHROW(Scene scene);
}

TEST_CASE("2. Draw Rectangle") {
    Scene scene;
    Object rect("prostokat.dat");

    CHECK_NOTHROW(scene.AddObject(rect));

    if (DISPLAY) {
        scene.Update();
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    }
}

// TEST_CASE("3 Pointners to objects") {
//     Scene scene;
//     scene.AddObject(Object("line.dat"));

//     Object *obj = &scene[0];

//     CHECK(obj == &scene[0]);
//     if (DISPLAY) {
//         scene.Update();
//         std::cout << "Press Enter to continue..." << std::endl;
//         std::cin.ignore(std::numeric_limits<int>().max(), '\n');
//     }

//     obj->Rotate(90, VectorZ);

//     if (DISPLAY) {
//         scene.Update();
//         CHECK(scene[0][0] == Vector3({0, 100, 0}));
//         std::cout << "Press Enter to continue..." << std::endl;
//         std::cin.ignore(std::numeric_limits<int>().max(), '\n');
//     }
//     scene.Update();
//     CHECK(scene[0][0] == Vector3({0, 100, 0}));

//     CHECK_THROWS(obj = &scene[9]);

//     scene.AddObject(Object("line.dat"));
//     obj = &scene[1];
//     obj->rotation = MatrixRot(90, VectorZ) * obj->rotation;
//     if (DISPLAY) {
//         scene.Update();
//         std::cout << "Press Enter to continue..." << std::endl;
//         std::cin.ignore(std::numeric_limits<int>().max(), '\n');
//     }
//     scene.Update();
//     CHECK(scene[1][0] == Vector3({0, 100, 0}));
// }
// 
// TEST_CASE("11. Lambda test") {
//     Object *obj;
//     Scene scene;
//     scene.AddObject(Object("line.dat"));
//     obj = &scene[0];
//     if (DISPLAY) {
//         scene.Update();
//         std::cout << "Press Enter to continue..." << std::endl;
//         std::cin.ignore(std::numeric_limits<int>().max(), '\n');
//     }
//     auto lambda = [&obj]() {
//         obj->rotation = MatrixRot(90, VectorZ) * obj->rotation;
//     };

//     CHECK(scene[0][0] == Vector3({100, 0, 0}));
//     if (DISPLAY) {
//         scene.Update();
//         std::cout << "Press Enter to continue..." << std::endl;
//         std::cin.ignore(std::numeric_limits<int>().max(), '\n');
//     }
//     lambda();
//     scene.Update();
//     CHECK(scene[0][0] == Vector3({0, 100, 0}));
// }