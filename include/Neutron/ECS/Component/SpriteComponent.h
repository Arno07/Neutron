#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace Neutron {

    class Texture2D;

    struct SpriteComponent {
        glm::vec4 Color = glm::vec4(1.0f);
        std::shared_ptr<Texture2D> Texture;
        glm::vec2 Tiling = glm::vec2(1.0f);  // updated every frame
        glm::vec2 Offset = glm::vec2(0.0f);  // updated every frame
    };


}