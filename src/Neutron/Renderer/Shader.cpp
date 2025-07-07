#include "Neutron/Renderer/Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Neutron {

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexCode = LoadFromFile(vertexPath);
        std::string fragmentCode = LoadFromFile(fragmentPath);

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        glLinkProgram(m_ID);
        CheckCompileErrors(m_ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ID);
    }

    void Shader::Use() const {
        glUseProgram(m_ID);
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const {
        int loc = glGetUniformLocation(m_ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
        int loc = glGetUniformLocation(m_ID, name.c_str());
        glUniform4fv(loc, 1, &value[0]);
    }

    std::string Shader::LoadFromFile(const std::string& path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cerr << "[SHADER ERROR] " << type << ":\n" << infoLog << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cerr << "[PROGRAM LINK ERROR]:\n" << infoLog << std::endl;
            }
        }
    }

}