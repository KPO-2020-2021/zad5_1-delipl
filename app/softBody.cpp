bool DISPLAY = true;
#include "Scene.hpp"
#include <iostream>
int main(int argc, char const *argv[]) {
    /* code */
    Drone drone;
    while (true) {
        double x;
        char y;
        drone.Update();
        Scene::Clear();
        drone.Draw();
        std::cin >> y >> x;
        std::cout << "Rotate: " << x << " " << y << std::endl; 
        switch (y)
        {
        case 'a':
            drone.Left(x);
            break;
        case 'd':
            drone.Right(x);
            break;
        case 'w':
            drone.Forward(x);
            break;
        case 'c':
            drone.TookOff(x);
            break;

        default:
            break;
        }
        
    }
    return 0;
}

// #include <iostream>
// #include <limits>
// #include <chrono>
// #include <csignal>
// #include "config.hpp"
// #include "Menu.hpp"
// #include "Scene.hpp"


// void signalHandler( int signum ) {
//     std::cout << "Interrupt signal (" << signum << ") received.\n";
//     system("killall gnuplot & clear");
//     exit(signum);  
// }

// enum Draw{
//     goToDraw
// };
// typedef int LiczbaCalkowita;
// int main(int argc, const char** argv) { 
//     signal(SIGINT, signalHandler);


//     auto start = std::chrono::high_resolution_clock::now();

//     Scene scene;
//     Object cuboid("cube.dat", 16);
//     Object ground("ground.dat", 4);
//     scene.AddObject(&cuboid);
//     scene.AddObject(&ground);
    

//     std::cout << "Start animating..." << std::endl;
//     while(true){
//         auto measure = std::chrono::high_resolution_clock::now();
//         auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(measure - start);

//         try{
//             if(elapsed.count() >= (dt*1000)){
//                 start = std::chrono::high_resolution_clock::now();
//                 throw Draw::goToDraw;
//             }
//             /**
//              * @brief 
//              * 
//              */

//             if(ground.transform.localPosition[0] > 100){
            
                
//             }

//         }
//         catch(Draw){
//             scene.UpdatePoints();
//         }
//     }

//     return 0;
// }
