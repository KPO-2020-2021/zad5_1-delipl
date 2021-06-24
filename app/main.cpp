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
    bool finish = false;
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
    std::thread displaying([&scene, &finish]() {
        auto start = std::chrono::high_resolution_clock::now();
        while(!finish){
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
                // std::cout << "\n\nCounting Vectors..." << std::endl;

                // std::cout << "===========================================" << std::endl;
                // std::cout << std::setw(35) << "Number of Vectors on Scene: " << std::setw(10) << Vector3::HowManyObjects() << std::endl;
                // std::cout << std::setw(35) << "Number of Vectors from start: " << std::setw(10) << Vector3::AllHowManyObjects() << std::endl;
                // std::cout << "===========================================" << std::endl
                //           << std::endl
                //           << std::endl;
            }
        }
    });
        

    std::shared_ptr<Drone> drone;

    std::shared_ptr<Terrain> floor = std::make_shared<Terrain>();
    scene.Add(std::move (floor));

    /* -------------------------------------------------------------------------- */
    /*                              MENU CONSTRUCTOR                              */
    /* -------------------------------------------------------------------------- */
    
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
                              << drone->orientation;
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
                    // std::cout << "There are " << scene.CountObjects() << " on scene. Type number. 1 - n" << std::endl;
                    int d = 1;
                    for (std::size_t i = 0; i < scene.CountObjects(); ++i)
                    {
                        auto localPtr = std::dynamic_pointer_cast<Drone>(scene[i]);
                        if (localPtr != nullptr)
                        {
                            if (localPtr == drone)
                                std::cout << "* ";
                            else
                                std::cout << "  ";
                            std::cout << d++ << " Drone is on position:  " << localPtr->position << std::endl;
                        }
                    }
                    std::cout << "Type number of Drone" << std::endl;
                    std::size_t k = 1;
                    std::cin >> k;
                    drone->ChangeColor(1);
                    drone = std::dynamic_pointer_cast<Drone>(scene.SelectDrone(k));
                    drone->ChangeColor(2);
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
                                        { drone->GoVerdical(pos[0] ); });
                    if (pos[1] != 0)
                        drone->moves.push([pos, drone]()
                                          { drone->Right(pos[1]); });
                    if (pos[2] != 0)
                        drone->moves.push([pos, drone]()
                                          { drone->Forward(pos[2]); });
                    if (pos[0] != 0)
                        drone->moves.push([pos, drone]()
                                          { drone->GoVerdical(pos[0] * -1); });


                    drone->MakeRoute(pos[0], pos[1], pos[2]);
                }},
               {"Recognize flight", [&drone]()
                {
                    if (drone == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << "Type height, angle and length of move." << std::endl;
                    drone->moves.push([&drone]()
                                    { drone->GoVerdical(150); });
                    for (int i = 0; i < 30; ++i){
                        drone->moves.push([drone]()
                                          {
                                              drone->Right(360 / 20);
                                              drone->Forward(10);
                                          });

                    }
                        drone->moves.push([ drone]()
                                          { drone->GoVerdical(150 * -1); });

                    // drone->MakeRoute(pos[0], pos[1], pos[2]);
                }},
               {"Exit", [&finish, &scene]()
                {
                    finish = true;
                    throw std::logic_error("Exit");
                }}});

    scene.Add(std::move(std::make_shared<Drone>(Vector3({200, 200, 0}))));
    scene.Add(std::move(std::make_shared<Drone>(Vector3({200, -200, 0}))));
    drone =  std::dynamic_pointer_cast<Drone>(scene.SelectDrone(1));
    drone->ChangeColor(2);

    /* -------------------------------------------------------------------------- */
    /*                                  MAIN LOOP                                 */
    /* -------------------------------------------------------------------------- */
    std::thread menuig([&menu, &drone, &finish, &scene]() {
        while (!finish) {
            std::cout << "\n\nCounting Vectors..." << std::endl;

            std::cout << "===========================================" << std::endl;
            std::cout << std::setw(35) << "Number of Vectors on Scene: " << std::setw(10) << Vector3::HowManyObjects() << std::endl;
            std::cout << std::setw(35) << "Number of Vectors from start: " << std::setw(10) << Vector3::AllHowManyObjects() << std::endl;
            std::cout << "===========================================" << std::endl
                      << std::endl
                      << std::endl;
            std::cout << menu;
            try {
               
               

                std::cin >> menu;
            } catch (std::logic_error &e) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>().max(), '\n');
                if(std::string(e.what()) == "Exit"){
                    scene.~Scene();

                    finish = true;
                }else{
                    std::cerr << std::endl
                              << std::endl
                              << "!!![ERROR]!!!" << std::endl;
                    std::cerr << e.what() << std::endl
                              << std::endl;
                }
                
                
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
    std::cout << "===========================================" << std::endl;
    std::cout << std::setw(35) << "Number of Vectors on Scene: " << std::setw(10) << Vector3::HowManyObjects() << std::endl;
    std::cout << std::setw(35) << "Number of Vectors from start: " << std::setw(10) << Vector3::AllHowManyObjects() << std::endl;
    std::cout << "===========================================" << std::endl;

    return 0;
}