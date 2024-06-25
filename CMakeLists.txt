cmake_minimum_required(VERSION 3.27)
project(Universe)

set(CMAKE_CXX_STANDARD 23)

include_directories(SYSTEM /usr/include/glad /usr/include/KHR)

add_executable(Universe
        /usr/include/glad/glad.c
        src/main.cpp
        src/Simulation/particle.h
        src/Simulation/environment.h
        src/Physics/classical.h
        src/Math/arithmetics.h
        src/Simulation/wall.h
        src/Math/vector.h
        src/Graphics/Shader/shader.h
        src/Graphics/Buffer/VBO.h
        src/Graphics/Buffer/EBO.h
        src/Graphics/Buffer/VAO.h
        src/Math/trig.h
        src/Graphics/general.h)

target_link_libraries(Universe glfw)
