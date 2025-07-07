#pragma once
#include <Neutron/Renderer/Texture2D.h>  // At the top of main.cpp
#include <glm/glm.hpp>
#include <memory>

namespace Neutron {

    class Shader;

    class SpriteRenderer {
    public:
        static void Init();
        static void Shutdown();

        static void DrawQuad(const glm::vec3& position,
                     const glm::vec3& scale,
                     const glm::vec4& color,
                     const std::shared_ptr<Texture2D>& texture,
                     const glm::mat4& viewProjection);

    private:
        static unsigned int s_VAO, s_VBO;
        static std::unique_ptr<Shader> s_Shader;
        static glm::mat4 s_Projection;
    };

}