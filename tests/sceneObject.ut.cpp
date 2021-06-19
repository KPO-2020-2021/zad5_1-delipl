#include "config.hpp"
#include "SceneObject.hpp"
#include "Scene.hpp"
#include "doctest.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
extern bool DISPLAY;

TEST_CASE("1. Route constructor"){
    Vector3 start({0, 0, 0});
    Vector3 stop({10, 10, 0});
    CHECK_NOTHROW(Route route(start, stop, 50.0));
    CHECK_NOTHROW(new  Route (start, stop, 50.0));
}
TEST_CASE("2. Rotor constructor") {
    Vector3 localPosition({0, 0, 0});
    CHECK_NOTHROW(Rotor rotor(SpinDirection_t::Clockwise, localPosition, {1, 1, 1}, nullptr));
    Rotor rotor(SpinDirection_t::Clockwise, localPosition, {1,1,1}, nullptr);
    CHECK_NOTHROW(Rotor x(SpinDirection_t::Clockwise, localPosition, {1, 1, 1}, &rotor));
}

TEST_CASE("3. Rotor pin and local and global positions"){
    Cuboid cub({60, 30,10});
    if (DISPLAY) {
        std::cout << "Press Enter to rotate..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        for (int i = 0; i < 100; ++i){
            

            cub.Rotate(2, VectorZ);
            cub.UpdatePoints();
            cub.Draw();
            usleep(10000);
            Scene::Clear();
        }
        std::cout << "Rotate cub" << std::endl;
        std::cout << "Press Enter to continue..." << std::endl;

        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
    // SceneObject drone("cuboid.dat", {0, 0, 50}, {0.2, 0.2, 0.2});
    // Rotor rotor({0, 0, 30}, std::make_shared<Transform>(drone), SpinDirection_t::Clockwise);

    // CHECK(drone.localPosition == Vector3({0, 0, 50}));
    // CHECK(drone[0] == Vector3({0, -4, 50}));

    // drone.Translate({50, 0, 0});
    // drone.UpdatePoints();
    // rotor.UpdatePoints();

    // CHECK(rotor.localPosition == drone.localPosition + VectorZ * 30);
    // CHECK(rotor[0] == Vector3({50, 0, 79.5}));
    // CHECK(rotor[1] == Vector3({50.5, 0, 79.5}));
    // CHECK(rotor[2] == Vector3({50.5, 0, 80.5}));
    // CHECK(rotor[3] == Vector3({50, 0, 80.5}));

    // Rotor rotor2({0, 0, 0}, &rotor, SpinDirection_t::Clockwise);

    // SUBCASE("Spawn correctlly"){
    //     CHECK(rotor.localPosition == rotor2.localPosition);
    //     CHECK(rotor2[0] == Vector3({50, 0, 79.5}));
    //     CHECK(rotor2[1] == Vector3({50.5, 0, 79.5}));
    //     CHECK(rotor2[2] == Vector3({50.5, 0, 80.5}));
    //     CHECK(rotor2[3] == Vector3({50, 0, 80.5}));
    // }

    // drone.Translate({0, 0, -30});
    // drone.UpdatePoints();
    // rotor.UpdatePoints();

    // CHECK(rotor[0] == Vector3({50, 0, 49.5}));
    // CHECK(rotor[1] == Vector3({50.5, 0, 49.5}));
    // CHECK(rotor[2] == Vector3({50.5, 0, 50.5}));
    // CHECK(rotor[3] == Vector3({50, 0, 50.5}));

    // rotor2.UpdatePoints();

    // CHECK(rotor2[0] == Vector3({0, 0, 79.5}));
    // CHECK(rotor2[1] == Vector3({0.5, 0, 79.5}));
    // CHECK(rotor2[2] == Vector3({0.5, 0, 80.5}));
    // CHECK(rotor2[3] == Vector3({0, 0, 80.5}));


}

TEST_CASE("4. Cuboid dims"){
    Cuboid c({1, 1, 1});
    CHECK(c.dimentions == Vector3{1, 1, 1});
    Cuboid d({2, 2, 2});
    CHECK(d.dimentions == Vector3{2, 2, 2});
}