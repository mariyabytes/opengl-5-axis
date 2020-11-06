cmake_minimum_required(VERSION 3.18)
project(openGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(openGL main.cpp game.h headers/include_libs.h headers/vertex.h headers/shader.h headers/primitives.h headers/objectLoader.h headers/model.h headers/mesh.h headers/material.h headers/camera.h game.cpp game.cpp generater_functions.cpp headers/generater_functions.h)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_include_directories(openGL PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(openGL PUBLIC glfw GLEW OpenGL::GL ${CMAKE_DL_LIBS})
