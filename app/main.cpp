#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <limits>
#include <thread>



#include "config.hpp"
#include "Terrain.hpp"
#include "Drone.hpp"

#include "Menu.hpp"
#include "Scene.hpp"



bool DISPLAY = true;

enum Draw{
    goToDraw
};


int main() {
    /* -------------------------------------------------------------------------- */
    /*                              INIT INFORMATIONS                             */
    /* -------------------------------------------------------------------------- */

    std::cout << "Project Rotation 3D based on C++ Boiler Plate by Jakub Delicat v"
              << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
              << "."
              << PROJECT_VERSION_MINOR /* istotne zmiany */
              << "."
              << PROJECT_VERSION_PATCH /* naprawianie bugów */
              << "."
              << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
              << std::endl;
    std::system("cat ./LICENSE");
    std::system("pwd");
    std::cout << "Press enter to start..." << std::endl
              << std::endl
              << std::endl;
    std::cin.ignore(std::numeric_limits<int>().max(), '\n');

    /* -------------------------------------------------------------------------- */
    /*                              CREATING FIGURES                              */
    /* -------------------------------------------------------------------------- */

    Scene scene;
    std::thread displaying([&scene]() {
        auto start = std::chrono::high_resolution_clock::now();
        while(true){
            auto measure = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(measure - start);
            try{
                if(elapsed.count() >= (100)){
                    start = std::chrono::high_resolution_clock::now();
                    throw Draw::goToDraw;
                }

            }
            catch(Draw){
                scene.Update();
            }
        }
    });
        

    std::shared_ptr<Drone> drone;

    std::shared_ptr<Terrain> floor = std::make_shared<Terrain>();
    scene.Add(std::move (floor));

    /* -------------------------------------------------------------------------- */
    /*                              MENU CONSTRUCTOR                              */
    /* -------------------------------------------------------------------------- */
    bool finish = false;
    std::vector<MatrixRot> rotationSequece;
    Menu menu({{"Print informations about selected object: ",
                [&drone]() mutable
                {
                    if (drone == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << drone->SeflID() << " " << drone->Name() << std::endl;
                    std::cout << "position: \n"
                              << drone->position
                              << "\neuler anglesRPY: \n"
                              << drone->anglesRPY
                              << "\nrotation Matrix: \n"
                              << drone->localRotation;
                }},
               {"Add Drone: ",
                [&scene]()
                {
                    std::cout << "Where spawn drone Vector3: \n";
                    Vector3 pos;
                    std::cin >> pos;
                    std::shared_ptr<Drone> tmp = std::make_shared<Drone>(pos);
                    scene.Add(std::move(tmp));
                }},
               {"Choose active drone: ", [&drone, &scene]()
                {
                    std::cout << "There are " << scene.CountObjects() << " on scene. Type number. 1 - n" << std::endl;
                    std::size_t k =1;
                    std::size_t n = 0;
                    std::cin >> k;
                    for (std::size_t i = 0; i < scene.CountObjects(); ++i)
                    {
                        auto localPtr = std::dynamic_pointer_cast<Drone>(scene[i]);
                        if (localPtr != nullptr)
                        {
                            ++n;
                            if(n == k)
                            {
                                drone = localPtr;
                            }
                        }
                    }
                }},
               {"Move drone", [&drone]()
                {
                    if (drone == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << "Type height, angle and length of move." << std::endl;
                    Vector3 pos;
                    std::cin >> pos;
                    if(pos[0] != 0)
                        drone->moves.push([pos, drone]()
                                        { drone->TookOff(pos[0] ); });
                    if (pos[1] != 0)
                        drone->moves.push([pos, drone]()
                                          { drone->Right(pos[1]); });
                    if (pos[2] != 0)
                        drone->moves.push([pos, drone]()
                                          { drone->Forward(pos[2]); });
                    if (pos[0] != 0)
                        drone->moves.push([pos, drone]()
                                          { drone->TookOff(pos[0] * -1); });


                    drone->MakeRoute(pos[0], pos[1], pos[2]);
                }},

               {"Exit", [&finish, &scene]()
                {
                    finish = true;
                    throw std::logic_error("Exit");
                    
                }}});

    std::shared_ptr<Drone> tmp = std::make_shared<Drone>();
    scene.Add(std::move(tmp));
    drone = std::dynamic_pointer_cast<Drone>(scene[1]);

    /* -------------------------------------------------------------------------- */
    /*                                  MAIN LOOP                                 */
    /* -------------------------------------------------------------------------- */
    std::thread menuig([&menu, &drone, &finish, &scene]() {
        while (!finish) {
            std::cout << "=======================" << menu;
            try {
                std::cin >> menu;
                std::cout << "=======================" << std::endl; 
            } catch (std::logic_error &e) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>().max(), '\n');
                if(std::string(e.what()) == "Exit"){
                    scene.~Scene();
                    exit(0);
                }
                std::cerr << std::endl
                          << std::endl
                          << "!!![ERROR]!!!" << std::endl;
                std::cerr << e.what() << std::endl
                          << std::endl;
                
            }
            catch (...) {
                std::cerr << "Fatal error, cautch ununderstable throw!!!" << std::endl;
                scene.~Scene();
                exit(-1);
            }
        }
    });

    displaying.join();
    menuig.join();

    return 0;
}