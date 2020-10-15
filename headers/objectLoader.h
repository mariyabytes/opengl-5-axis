#ifndef OPENGL_5_AXIS_OBJECTLOADER_H
#define OPENGL_5_AXIS_OBJECTLOADER_H


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex.h"

static std::vector<Vertex> loadObjFile(const char *filename) {
    std::vector<glm::fvec3> vertexPositions;
    std::vector<glm::fvec3> vertexNormals;
    std::vector<glm::fvec2> vertexTexCoords;

    // Faces
    std::vector<GLint> vertexPositionIndeces;
    std::vector<GLint> vertexNormalIndeces;
    std::vector<GLint> vertexTexCoordIndeces;

    // Vertex Array
    std::vector<Vertex> vertices;

    std::stringstream ss;
    std::ifstream inputFile(filename);
    std::string currentLine;
    std::string prefix;

    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_glint;

    if (!inputFile.is_open()) {
        std::cout << "Failed to load obj file : " << filename << std::endl;
        std::stringstream errorMsg;
        errorMsg << "ERROR::OBJLOADER::COULD_NOT_OPEN_FILE";
        std::cout << errorMsg.str();
        exit(0);
    }

    while (std::getline(inputFile, currentLine)) {

        ss.clear();
        ss.str(currentLine);

        // get the first letter of the line
        ss >> prefix;

        if (prefix == "#") {
        } else if (prefix == "o") {
        } else if (prefix == "use_mtl") {
        } else if (prefix == "v") // vertex position
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertexPositions.push_back(temp_vec3);
        } else if (prefix == "vt") // vertex position
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertexTexCoords.push_back(temp_vec2);
        } else if (prefix == "vn") // vertex position
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertexNormals.push_back(temp_vec3);
        } else if (prefix == "f") // face stuff
        {
            int counter = 0;
            while (ss >> temp_glint) {
                //Pushing indices into correct arrays
                switch (counter) {
                    case 0:
                        vertexPositionIndeces.push_back(temp_glint);
                        break;
                    case 1:
                        vertexTexCoordIndeces.push_back(temp_glint);
                        break;
                    case 2:
                        vertexNormalIndeces.push_back(temp_glint);
                        break;

                    default:
                        break;
                }

                //Handling characters
                if (ss.peek() == '/') {
                    ++counter;
                    ss.ignore(1, '/');
                } else if (ss.peek() == ' ') {
                    ++counter;
                    ss.ignore(1, ' ');
                }

                //Reset the counter
                if (counter > 2)
                    counter = 0;
            }
        } else {
        }
    }
    vertices.resize(vertexPositionIndeces.size(), Vertex());

    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].position = vertexPositions[vertexPositionIndeces[i] - 1];
        vertices[i].texcoord = vertexTexCoords[vertexTexCoordIndeces[i] - 1];
        vertices[i].normal = vertexNormals[vertexNormalIndeces[i] - 1];
        vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
    }
    std::cout << "Nr of vertices" << vertices.size() << std::endl;
    std::cout << "Object file \"" << filename << "\" loaded !" << std::endl;
    return vertices;
}

static void print(char *stuff) {
    std::cout << stuff << std::endl;
}

#endif //OPENGL_5_AXIS_OBJECTLOADER_H
