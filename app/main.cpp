#include <iostream>
#include <limits>

#include "Menu.hpp"
#include "Scene.hpp"
#include "config.hpp"
bool DISPLAY = true;
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

    std::shared_ptr<Drone> drone;

    std::shared_ptr<Terrain> floor = std::make_shared<Terrain>();
    scene.Add(std::move (floor));

    /* -------------------------------------------------------------------------- */
    /*                              MENU CONSTRUCTOR                              */
    /* -------------------------------------------------------------------------- */
    bool finish = false;
    std::vector<MatrixRot> rotationSequece;
    Menu menu({{"Print informations about selected object: ",
                [&drone]() mutable {
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
                [ &scene]() {
                    std::cout << "Where spawn drone Vector3: \n";
                    Vector3 pos;
                    std::cin >> pos;
                    std::shared_ptr<Drone> tmp = std::make_shared<Drone>(pos);
                    scene.Add(std::move(tmp));
                }},

               {"Exit", [&finish]() { finish = true; }}});

    /* -------------------------------------------------------------------------- */
    /*                                  MAIN LOOP                                 */
    /* -------------------------------------------------------------------------- */
    while (!finish) {
        scene.Update();

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
            return -1;
        }
    }
    return 0;
}