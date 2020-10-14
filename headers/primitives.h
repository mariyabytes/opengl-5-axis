#ifndef OPENGL_5_AXIS_PRIMITIVES_H
#define OPENGL_5_AXIS_PRIMITIVES_H


#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include"vertex.h"

class Primitive {
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

public:
    Primitive() {}

    virtual ~Primitive() {}

    //Functions
    void set(const Vertex *vertices,
             const unsigned nrOfVertices,
             const GLuint *indices,
             const unsigned nrOfIndices) {
        for (size_t i = 0; i < nrOfVertices; i++) {
            this->vertices.push_back(vertices[i]);
        }

        for (size_t i = 0; i < nrOfIndices; i++) {
            this->indices.push_back(indices[i]);
        }
    }

    inline Vertex *getVertices() { return this->vertices.data(); }

    inline GLuint *getIndices() { return this->indices.data(); }

    inline const unsigned getNrOfVertices() { return this->vertices.size(); }

    inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive {
public:
    Triangle()
            : Primitive() {
        Vertex vertices[] =
                {
                        //Position								//Color							//Texcoords					//Normals
                        glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.5f, 1.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] =
                {
                        0, 1, 2    //Triangle 1
                };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};

class Quad : public Primitive {
public:
    Quad()
            : Primitive() {
        Vertex vertices[] =
                {
                        //Position								//Color							//Texcoords					//Normals
                        glm::vec3(-75.0f, 75.0f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(-75.0f, -75.0f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(75.0f, -75.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(75.0f, 75.0f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f),
                        glm::vec3(0.f, 0.f, 1.f)
                };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] =
                {
                        0, 1, 2,    //Triangle 1
                        0, 2, 3        //Triangle 2
                };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};

class Pyramid : public Primitive {
public:
    Pyramid()
            : Primitive() {
        Vertex vertices[] =
                {
                        //Position								//Color							//Texcoords					//Normals
                        //Triangle front
                        glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.5f, 1.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),

                        //Triangle left
                        glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.5f, 1.f),
                        glm::vec3(-1.f, 0.f, 0.f),
                        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f),
                        glm::vec3(-1.f, 0.f, 0.f),
                        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(-1.f, 0.f, 0.f),

                        //Triangle back
                        glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.5f, 1.f),
                        glm::vec3(0.f, 0.f, -1.f),
                        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 0.f, -1.f),
                        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 0.f, -1.f),

                        //Triangles right
                        glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.5f, 1.f),
                        glm::vec3(1.f, 0.f, 0.f),
                        glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f),
                        glm::vec3(1.f, 0.f, 0.f),
                        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(1.f, 0.f, 0.f),
                };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        this->set(vertices, nrOfVertices, nullptr, 0);
    }
};

class Cube : public Primitive {
public:
    Cube()
            : Primitive() {
        Vertex vertices[] =
                {
                        //Position								//Color							//Texcoords					//Normals
                        glm::vec3(-0.5f, 0.5f, 20.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(-0.5f, -0.5f, 20.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(0.5f, -0.5f, 20.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f),
                        glm::vec3(0.5f, 0.5f, 20.5f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f),
                        glm::vec3(0.f, 0.f, 1.f),

                        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
                        glm::vec3(0.f, 0.f, -1.f),
                        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 0.f, -1.f),
                        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 0.f, -1.f),
                        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f),
                        glm::vec3(0.f, 0.f, -1.f),

                        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(0.f, 1.f),
                        glm::vec3(0.f, 1.f, 0.f), // 3
                        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 0.f),
                        glm::vec3(0.f, 1.f, 0.f), // 1
                        glm::vec3(-0.5f, -0.5f, 20.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 0.f),
                        glm::vec3(0.f, 1.f, 0.f), // 2
                        glm::vec3(0.5f, -0.5f, 20.5f), glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 1.f),
                        glm::vec3(0.f, 1.f, 0.f), // 4

                };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

        GLuint indices[] =
                {
                        0, 1, 2,
                        0, 2, 3,

                        7, 6, 1,
                        7, 1, 0,

                        4, 5, 6,
                        4, 6, 7,

                        3, 2, 5,
                        3, 5, 4,

                        9, 10, 11,
                        9, 11, 8
                };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

        this->set(vertices, nrOfVertices, indices, nrOfIndices);
    }
};

#endif //OPENGL_5_AXIS_PRIMITIVES_H
