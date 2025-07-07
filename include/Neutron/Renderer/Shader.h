#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Neutron {

    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Use() const;
        void SetMat4(const std::string& name, const glm::mat4& matrix) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;

        unsigned int GetID() const { return m_ID; }

    private:
        unsigned int m_ID;

        std::string LoadFromFile(const std::string& path);
        void CheckCompileErrors(unsigned int shader, const std::string& type);
    };

}