#ifndef OPENGL_5_AXIS_VERTEX_H
#define OPENGL_5_AXIS_VERTEX_H


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

#endif //OPENGL_5_AXIS_VERTEX_H
