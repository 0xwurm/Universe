#include <iostream>
#include <chrono>
#include <thread>
#include "Graphics/general.h"
#include "Simulation/environment.h"

using namespace std::chrono_literals;


int main(){
    auto start = std::chrono::steady_clock::now();
    init_gl();
    GraphicsUnit graphics;

    Environment environment(0.006944);

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            Vector<2> position(i / 0.2f + 1, j / 0.5f + 1);
            Vector<2> velocity(2.0f, 1.0f);
//
            environment.add_particle(position, velocity, 0.5, 5);
        }
    }


    Vector<2> position1(5.5, 10.0);
    Vector<2> velocity1(-5.0, 3.0f);
    Vector<2> position2(14.5, 5.5);
    Vector<2> velocity2(5.0f, 3.0f);

    // environment.add_particle(position1, velocity1, 2.5, 5);
    // environment.add_particle(position2, velocity2, 2.5, 5);

    int frames = 0;

    // Main while loop
    while (!glfwWindowShouldClose(graphics.window))
    {
        environment.compute_frame();
        environment.render_frame(graphics);

        std::system("clear");
        std::cout << "System Energy:\t" << environment.overall_energy() << " Joules" << std::endl;
        std::cout << "System Impulse:\t" << environment.overall_impulse() << " Newton-seconds" << std::endl;

        frames++;
    }

    graphics.shader->destroy();

    glfwDestroyWindow(graphics.window);
    glfwTerminate();
    std::cout << "Avg. FPS: " << 1000 * frames / std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;

    return 0;
}





/*

int main(){
    auto start = std::chrono::steady_clock::now();
    Environment environment(0.1);

    Vector<2> position(50.0, 300.0);
    Vector<2> velocity(0.0, 0.0);
    Vector<2> position1(30.0, 30.0);
    Vector<2> velocity1(10.0, 75.0);
    environment.add_particle(position, velocity, 10, 5);
    environment.add_particle(position1, velocity1, 10, 5);

    double anchor[2] = {50, 100};
    double length[2] = {200, 50};
    // environment.add_object(anchor, length, 1000);
    double anchor1[2] = {0, 0};
    double length1[2] = {300, 20};
    // environment.add_object(anchor1, length1, 1000);

    int frames = 10000;

    for (int t = 0; t < frames; t++) {
        environment.do_frame();
        std::system("clear");
        std::cout   << "Time: " << t << "\n"
                    << environment;
        std::this_thread::sleep_for(100ms);
    }

    std::cout << "Avg. FPS: " << 1000 * frames / std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
}*/
