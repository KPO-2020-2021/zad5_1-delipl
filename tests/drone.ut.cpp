#include "doctest.h"
#include "config.hpp"
#include "Drone.hpp"
#include "Scene.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

extern bool DISPLAY;
TEST_CASE("1. Drone Constructor") {
    CHECK_NOTHROW(Drone());
}
TEST_CASE("2. Print Drone"){
    Drone drone;
    
    if (DISPLAY) {
        std::cout <<std::endl << "Draw drone..." << std::endl;
        drone.Draw();
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
}


TEST_CASE("3. Print Drone at point") {
    Drone drone({30, 50, 65});

    if (DISPLAY) {
        drone.Draw();

        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
}

TEST_CASE("4. Move Drone") {
    Drone drone({30, 50, 65});
    drone.Translate({-30, -50, -65});
    drone.Update();
    CHECK(drone.localPosition == Vector3());
    if (DISPLAY) {
        drone.Draw();

        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
}

TEST_CASE("4. Drone forward and tookoff") {
    Drone drone({30, 50, 65});

    drone.Forward(60);
    drone.Update();
    CHECK(drone.localPosition == Vector3({30, 110, 65}));
    if (DISPLAY) {
        drone.Draw();

        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
    drone.TookOff(50);
    drone.Update();
    CHECK(drone.localPosition == Vector3({30, 110, 115}));
    if (DISPLAY) {
        drone.Draw();

        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
}
TEST_CASE("5. Drone rotate") {
    Drone drone;
    if (DISPLAY) {
        drone.Draw();
        std::cout << "Rotate Drone" << std::endl;
        std::cout << "Press Enter to continue..." << std::endl;

        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
    drone.Left(90);
    drone.Update();
    if (DISPLAY) {
        drone.Draw();

        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::Clear();
    }
}
    // TEST_CASE("2. Drone forward"){
    //     Drone d;
    //     d.Forward(100);
    //     CHECK(d.localPosition == Vector3({100, 0, 0}));
    // }