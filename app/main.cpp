#include <iostream>
#include <limits>

#include "Menu.hpp"
#include "Scene.hpp"
#include "config.hpp"

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

    scene.AddObject(Object("surface.dat", {-100, -100, 0}));

    for (double i = -80; i < 80; i += 20)
        for (double j = -80; j < 80; j += 20)
            scene.AddObject(Object("prism.dat", {j, i, 0}, {20, 20, 20}));

    Object *selectedObj = nullptr;

    std::size_t times = 1;

    /* -------------------------------------------------------------------------- */
    /*                              MENU CONSTRUCTOR                              */
    /* -------------------------------------------------------------------------- */
    bool finish = false;
    std::vector<MatrixRot> rotationSequece;
    Menu menu({{"Print informations about selected object: ",
                [&selectedObj]() mutable {
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");

                    std::cout
                        << selectedObj->SeflID() << " " << selectedObj->Name() << std::endl;
                    std::cout << "position: \n"
                              << selectedObj->position
                              << "\neuler angles: \n"
                              << selectedObj->eulerAngles
                              << "\nrotation Matrix: \n"
                              << selectedObj->rotation;
                }},
               {"Choose Figure to work with (index)",
                [&selectedObj, &scene]() {
                    std::cout << "Type index of object" << std::endl;
                    int x;
                    std::cin >> x;
                    try {
                        selectedObj = &scene[x];
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                        std::cerr << "Try again" << std::endl;
                    }
                }},
               {"Rotate - Choose axis, angle (print . to exit)",
                [&selectedObj, &rotationSequece, &times]() mutable {
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");

                    char axis = ' ';
                    double angle = 0;
                    try {
                        bool finish = false;
                        rotationSequece.clear();
                        while (!finish) {
                            std::cin >> axis;
                            if (!std::cin) throw std::logic_error("Wrong input!!!");

                            if (axis == '.') {
                                std::cout << "How many time rotate?" << std::endl;

                                std::cin >> times;
                                if (!std::cin)
                                    throw std::logic_error("Wrong input!!!");

                                for (std::size_t i = 0; i < times; ++i)
                                    for (auto &rot : rotationSequece)
                                        selectedObj->rotation = rot * selectedObj->rotation;

                                return;
                            }

                            std::cin >> angle;
                            if (!std::cin) throw std::logic_error("Wrong input!!!");

                            switch (axis) {
                                case 'X':
                                case 'x':
                                    rotationSequece.push_back(
                                        MatrixRot(angle, VectorX));
                                    selectedObj->eulerAngles[0] += angle;
                                    break;
                                case 'Y':
                                case 'y':
                                    rotationSequece.push_back(
                                        MatrixRot(angle, VectorY));
                                    selectedObj->eulerAngles[1] += angle;
                                    break;
                                case 'Z':
                                case 'z':
                                    rotationSequece.push_back(
                                        MatrixRot(angle, VectorZ));
                                    selectedObj->eulerAngles[2] += angle;
                                    break;
                                default:
                                    throw std::logic_error("Wrong axis");
                                    break;
                            }
                        }
                    } catch (std::logic_error &e) {
                        std::cin.clear();
                        std::cerr << e.what() << std::endl;
                    }
                }},
               {"Rotate again with the last sequence",
                [&rotationSequece, &times, &selectedObj]() {
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");

                    for (std::size_t i = 0; i < times; ++i)
                        for (auto &rot : rotationSequece) selectedObj->rotation = rot * selectedObj->rotation;
                }},
               {"Print rotaion Matrix",
                [&selectedObj]() { 
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << selectedObj->rotation << std::endl; }},
               {"Translate - vector x y z",
                [&selectedObj]() {
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    Vector3 x;
                    std::cin >> x;
                    selectedObj->position += x;
                }},
               {"Print cords of Figure",
                [&selectedObj]() {
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << *selectedObj << std::endl;
                }},
               {"Check lengths of Figure",
                [&selectedObj]() {
                    if (selectedObj == nullptr)
                        throw std::logic_error("Did not choosed the active object.");
                    std::cout << "Edge 1 a: " << ((*selectedObj)[1] - (*selectedObj)[2]).Length()
                              << "\t";
                    std::cout << "Edge 2 a: " << ((*selectedObj)[5] - (*selectedObj)[6]).Length()
                              << "\t";
                    std::cout << "Edge 3 a: " << ((*selectedObj)[9] - (*selectedObj)[10]).Length()
                              << "\t";
                    std::cout << "Edge 4 a: " << ((*selectedObj)[13] - (*selectedObj)[14]).Length()
                              << "\t";
                    std::cout << std::endl;

                    std::cout << "Diffrence between edges: "
                              << ((*selectedObj)[5] - (*selectedObj)[6]).Length() -
                                     ((*selectedObj)[9] - (*selectedObj)[10]).Length()
                              << "\t";
                    std::cout << "Diffrence between edges: "
                              << ((*selectedObj)[1] - (*selectedObj)[2]).Length() -
                                     ((*selectedObj)[13] - (*selectedObj)[14]).Length()
                              << "\t";
                    std::cout << std::endl;
                    std::cout << std::endl;

                    std::cout << "Edge 1 b: " << ((*selectedObj)[1] - (*selectedObj)[5]).Length()
                              << "\t";
                    std::cout << "Edge 2 b: " << ((*selectedObj)[9] - (*selectedObj)[13]).Length()
                              << "\t";
                    std::cout << "Edge 3 b: " << ((*selectedObj)[2] - (*selectedObj)[6]).Length()
                              << "\t";
                    std::cout << "Edge 4 b: " << ((*selectedObj)[10] - (*selectedObj)[14]).Length()
                              << "\t";
                    std::cout << std::endl;

                    std::cout << "Diffrence between edges: "
                              << ((*selectedObj)[1] - (*selectedObj)[5]).Length() -
                                     ((*selectedObj)[2] - (*selectedObj)[6]).Length()
                              << "\t";
                    std::cout << "Diffrence between edges: "
                              << ((*selectedObj)[9] - (*selectedObj)[13]).Length() -
                                     ((*selectedObj)[10] - (*selectedObj)[14]).Length()
                              << "\t";
                    std::cout << std::endl;
                    std::cout << std::endl;

                    std::cout << "Edge 1 c: " << ((*selectedObj)[5] - (*selectedObj)[9]).Length()
                              << "\t";
                    std::cout << "Edge 2 c: " << ((*selectedObj)[13] - (*selectedObj)[17]).Length()
                              << "\t";
                    std::cout << "Edge 3 c: " << ((*selectedObj)[6] - (*selectedObj)[10]).Length()
                              << "\t";
                    std::cout << "Edge 4 c: " << ((*selectedObj)[14] - (*selectedObj)[18]).Length()
                              << "\t";
                    std::cout << std::endl;

                    std::cout << "Diffrence between edges: "
                              << ((*selectedObj)[5] - (*selectedObj)[9]).Length() -
                                     ((*selectedObj)[6] - (*selectedObj)[10]).Length()
                              << "\t";
                    std::cout << "Diffrence between edges: "
                              << ((*selectedObj)[13] - (*selectedObj)[17]).Length() -
                                     ((*selectedObj)[14] - (*selectedObj)[18]).Length()
                              << "\t";
                    std::cout << std::endl;
                    std::cout << std::endl;
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