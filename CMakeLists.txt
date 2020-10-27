cmake_minimum_required(VERSION 3.17)
project(opengl_5_axis)

set(CMAKE_CXX_STANDARD 20)

add_executable(opengl_5_axis main.cpp headers/game.h headers/include_libs.h headers/vertex.h headers/shader.h headers/primitives.h headers/objectLoader.h headers/model.h headers/mesh.h headers/material.h headers/camera.h game.cpp)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_include_directories(opengl_5_axis PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(opengl_5_axis PUBLIC glfw GLEW OpenGL::GL ${CMAKE_DL_LIBS})
