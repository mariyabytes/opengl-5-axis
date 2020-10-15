#ifndef OPENGL_5_AXIS_MESH_H
#define OPENGL_5_AXIS_MESH_H


#include<iostream>
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

#include "vertex.h"
#include "shader.h"
#include "primitives.h"


class Mesh {
private:
    Vertex *vertexArray;
    unsigned nrOfVertices;
    GLuint *indexArray;
    unsigned nrOfIndices;

    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};

    glm::vec3 position{};
    glm::vec3 origin{};
    glm::vec3 rotation{};
    glm::vec3 scale{};

    glm::mat4 ModelMatrix{};

    void initVAO() {
        //Create VAO
        glCreateVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        //GEN VBO AND BIND AND SEND DATA
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

        //GEN EBO AND BIND AND SEND DATA
        if (this->nrOfIndices > 0) {
            glGenBuffers(1, &this->EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
        }

        //SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
        //Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        //Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
        //Texcoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(2);
        //Normal
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);

        //BIND VAO 0
        glBindVertexArray(0);
    }

    void updateUniforms(Shader *shader) {
        shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
    }

    void updateModelMatrix() {
        this->ModelMatrix = glm::mat4(1.f);
        this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
        this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
        this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
        this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
        this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
        this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
    }

public:
    Mesh(
            Vertex *vertexArray,
            const unsigned &nrOfVertices,
            const GLuint *indexArray,
            const unsigned &nrOfIndices,
            glm::vec3 position = glm::vec3(0.f),
            glm::vec3 origin = glm::vec3(0.f),
            glm::vec3 rotation = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.f)) {
        this->position = position;
        this->origin = origin;
        this->rotation = rotation;
        this->scale = scale;

        this->nrOfVertices = nrOfVertices;
        this->nrOfIndices = nrOfIndices;

        this->vertexArray = new Vertex[this->nrOfVertices];
        for (size_t i = 0; i < nrOfVertices; i++) {
            this->vertexArray[i] = vertexArray[i];
        }

        this->indexArray = new GLuint[this->nrOfIndices];
        for (size_t i = 0; i < nrOfIndices; i++) {
            this->indexArray[i] = indexArray[i];
        }

        this->initVAO();
        this->updateModelMatrix();
    }

    explicit Mesh(
            Primitive *primitive,
            glm::vec3 position = glm::vec3(0.f),
            glm::vec3 origin = glm::vec3(0.f),
            glm::vec3 rotation = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.f)) {
        this->position = position;
        this->origin = origin;
        this->rotation = rotation;
        this->scale = scale;

        this->nrOfVertices = primitive->getNrOfVertices();
        this->nrOfIndices = primitive->getNrOfIndices();

        this->vertexArray = new Vertex[this->nrOfVertices];
        for (size_t i = 0; i < this->nrOfVertices; i++) {
            this->vertexArray[i] = primitive->getVertices()[i];
        }

        this->indexArray = new GLuint[this->nrOfIndices];
        for (size_t i = 0; i < this->nrOfIndices; i++) {
            this->indexArray[i] = primitive->getIndices()[i];
        }

        this->initVAO();
        this->updateModelMatrix();
    }

    Mesh(const Mesh &obj) {
        this->position = obj.position;
        this->origin = obj.origin;
        this->rotation = obj.rotation;
        this->scale = obj.scale;

        this->nrOfVertices = obj.nrOfVertices;
        this->nrOfIndices = obj.nrOfIndices;

        this->vertexArray = new Vertex[this->nrOfVertices];
        for (size_t i = 0; i < this->nrOfVertices; i++) {
            this->vertexArray[i] = obj.vertexArray[i];
        }

        this->indexArray = new GLuint[this->nrOfIndices];
        for (size_t i = 0; i < this->nrOfIndices; i++) {
            this->indexArray[i] = obj.indexArray[i];
        }

        this->initVAO();
        this->updateModelMatrix();
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);

        if (this->nrOfIndices > 0) {
            glDeleteBuffers(1, &this->EBO);
        }

        delete[] this->vertexArray;
        delete[] this->indexArray;
    }

    //Accessors

    //Modifiers
    void setPosition(const glm::vec3 pos) {
        this->position = pos;
    }

    void setOrigin(const glm::vec3 orig) {
        this->origin = orig;
    }

    void setRotation(const glm::vec3 rot) {
        this->rotation = rot;
    }

    void setScale(const glm::vec3 setScale) {
        this->scale = setScale;
    }

    //Functions

    void move(const glm::vec3 pos) {
        this->position += pos;
        this->setOrigin(this->position);
    }

    void rotate(const glm::vec3 rot) {
        this->rotation += rot;
    }

    void scaleUp(const glm::vec3 scal) {
        this->scale += scal;
    }

    void update() {

    }

    void render(Shader *shader) {
        //Update uniforms
        this->updateModelMatrix();
        this->updateUniforms(shader);

        shader->use();

        //Bind VAO
        glBindVertexArray(this->VAO);

        //RENDER
        if (this->nrOfIndices == 0)
            glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
        else
            glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, nullptr);

        //Cleanup
        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif //OPENGL_5_AXIS_MESH_H
