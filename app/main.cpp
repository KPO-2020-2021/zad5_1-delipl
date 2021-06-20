#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <limits>
#include <thread>



#include "Menu.hpp"
#include "Scene.hpp"
#include "config.hpp"



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
                    std::cout << "localPosition: \n"
                              << drone->localPosition
                              << "\neuler angles: \n"
                              << drone->eulerAngles
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
               {"Fly to position", [&drone]()
                {
                    if (drone == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << "Type finish position and height of flight." << std::endl;
                    Vector3 pos;
                    double height;
                    std::cin >> pos >> height;
                    drone->MakeRoute(drone->localPosition, pos, height);
                    drone->FlyTo(pos, height);
                }},
               {"Roatate left", [&drone]()
                {
                    double x;
                    std::cin >> x;
                    drone->Left(x);
                }},
               {"TookOff 0", [&drone]()
                {
                    double x;
                    std::cin >> x;
                    drone->TookOff(x);
                }},

               {"Exit", [&finish]()
                {
                    finish = true;
                    std::terminate();
                }}});

    std::shared_ptr<Drone> tmp = std::make_shared<Drone>();
    scene.Add(std::move(tmp));
    drone = std::dynamic_pointer_cast<Drone>(scene[1]);

    /* -------------------------------------------------------------------------- */
    /*                                  MAIN LOOP                                 */
    /* -------------------------------------------------------------------------- */
    std::thread menuig([&menu, &drone, &finish]() {
        while (!finish) {
            std::cout << "=======================" << menu;
            try {
                std::cin >> menu;
                std::cout << "=======================" << std::endl;
            } catch (std::logic_error &e) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>().max(), '\n');
                std::cerr << std::endl
                          << std::endl
                          << "!!![ERROR]!!!" << std::endl;
                std::cerr << e.what() << std::endl
                          << std::endl;

            } catch (...) {
                std::cerr << "Fatal error, cautch ununderstable throw!!!" << std::endl;
                exit(-1);
            }
        }
    });

    displaying.join();
    menuig.join();

    return 0;
}