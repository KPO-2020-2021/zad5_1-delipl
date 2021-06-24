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
TEST_CASE("6. Drow route"){
    Drone drone;
    if (DISPLAY) {
        std::cout <<std::endl << "Draw drone route put vector..." << std::endl;
        drone.Update();
        double x;
        std::cin >> x;
        drone.Draw();
        drone.Forward(x);
        drone.Update();
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::ClearGNUPlot();
    }
}

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
        Scene::ClearGNUPlot();
    }
}


TEST_CASE("3. Print Drone at point") {
    Drone drone({30, 50, 65});

    if (DISPLAY) {
        drone.Draw();

        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
        Scene::ClearGNUPlot();
    }
}


TEST_CASE("4. Drone forward and tookoff") {
    Drone drone;

    drone.Forward(60);
    while (!drone.Translated())
        drone.UpdatePoints();
    CHECK(drone.position == Vector3({60, 0, 0}));
    
    drone.Left(60);
    while (!drone.Rotated())
        drone.UpdatePoints();
    CHECK(drone.position == Vector3({60, 0, 0}));
    CHECK(drone.anglesRPY == Vector3({0, 0, 60}));

    drone.Forward(60);
    while (!drone.Translated())
        drone.UpdatePoints();
    CHECK(drone.position == Vector3{90, 51.9615242271, 0});
}
TEST_CASE ("5. Fly to:"){
    // Drone drone;
    // drone.FlyTo({100, 0, 100}, 100);
    // drone.moves.front()();
    // drone.moves.pop();
    // while (!drone.Translated())
    //     drone.Update();
    // CHECK(drone.position == Vector3({0, 0, 100}));

    // drone.moves.front()();
    // drone.moves.pop();
    // while (!drone.Rotated())
    //     drone.Update();
    // CHECK(drone.position == Vector3({0, 0, 100}));

    // drone.moves.front()();
    // drone.moves.pop();
    // while (!drone.Translated()){
    //     drone.Update();
    //     std::cout << drone.position << std::endl;
    // }
    // CHECK(drone.position == Vector3({100, 0, 100}));

    // drone.moves.front()();
    // drone.moves.pop();
    // while (!drone.Translated())
    //     drone.Update();
    // CHECK(drone.position == Vector3({100, 0, 0}));
}

    // TEST_CASE("2. Drone forward"){
    //     Drone d;
    //     d.Forward(100);
    //     CHECK(d.position == Vector3({100, 0, 0}));
    // }