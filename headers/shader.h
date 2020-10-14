#ifndef OPENGL_5_AXIS_SHADER_H
#define OPENGL_5_AXIS_SHADER_H


#include<iostream>
#include<fstream>
#include<string>

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

class Shader {
private:
    //Member variables
    GLuint id{};
    const int versionMajor;
    const int versionMinor;

    //Private functions
    std::string loadShaderSource(char *fileName) const {
        std::string temp;
        std::string src;

        std::ifstream in_file;

        //Vertex
        in_file.open(fileName);

        if (in_file.is_open()) {
            while (std::getline(in_file, temp))
                src += temp + "\n";
        } else {
            std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << "\n";
        }

        in_file.close();

        std::string versionNr =
                std::to_string(this->versionMajor) +
                std::to_string(this->versionMinor) +
                "0";

        src.replace(src.find("#version"), 12, ("#version " + versionNr));

        return src;
    }

    GLuint loadShader(GLenum type, char *fileName) {
        char infoLog[512];
        GLint success;

        GLuint shader = glCreateShader(type);
        std::string str_src = this->loadShaderSource(fileName);
        const GLchar *src = str_src.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << "\n";
            std::cout << infoLog << "\n";
        }

        return shader;
    }

    void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
        char infoLog[512];
        GLint success;

        this->id = glCreateProgram();

        glAttachShader(this->id, vertexShader);

        if (geometryShader)
            glAttachShader(this->id, geometryShader);

        glAttachShader(this->id, fragmentShader);

        glLinkProgram(this->id);

        glGetProgramiv(this->id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->id, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
            std::cout << infoLog << "\n";
        }

        glUseProgram(0);
    }

public:

    //Constructors/Destructors
    Shader(const int versionMajor, const int versionMinor,
           char *vertexFile, char *fragmentFile, char *geometryFile = (char *) "")
            : versionMajor(versionMajor), versionMinor(versionMinor) {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

        if (geometryFile != "")
            geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

        fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

        this->linkProgram(vertexShader, geometryShader, fragmentShader);

        //End
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
    }

    ~Shader() {
        glDeleteProgram(this->id);
    }

    //Set uniform functions
    void use() const {
        glUseProgram(this->id);
    }

    static void unuse() {
        glUseProgram(0);
    }

    void set1i(GLint value, const GLchar *name) const {
        this->use();

        glUniform1i(glGetUniformLocation(this->id, name), value);

        Shader::unuse();
    }

    void set1f(GLfloat value, const GLchar *name) const {
        this->use();

        glUniform1f(glGetUniformLocation(this->id, name), value);

        Shader::unuse();
    }

    void setVec2f(glm::fvec2 value, const GLchar *name) const {
        this->use();

        glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        Shader::unuse();
    }

    void setVec3f(glm::fvec3 value, const GLchar *name) const {
        this->use();

        glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        Shader::unuse();
    }

    void setVec4f(glm::fvec4 value, const GLchar *name) const {
        this->use();

        glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        Shader::unuse();
    }

    void setMat3fv(glm::mat3 value, const GLchar *name, GLboolean transpose = GL_FALSE) const {
        this->use();

        glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

        Shader::unuse();
    }

    void setMat4fv(glm::mat4 value, const GLchar *name, GLboolean transpose = GL_FALSE) const {
        this->use();

        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

        Shader::unuse();
    }

};

#endif //OPENGL_5_AXIS_SHADER_H
