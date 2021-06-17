#include "doctest.h"
#include "config.hpp"
#include "Drone.hpp"
#include "Scene.hpp"

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

// TEST_CASE("2. Drone forward"){
//     Drone d;
//     d.Forward(100);
//     CHECK(d.localPosition == Vector3({100, 0, 0}));
// }