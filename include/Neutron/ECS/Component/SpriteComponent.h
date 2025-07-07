#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace Neutron {

    class Texture2D;

    struct SpriteComponent {
        glm::vec4 Color = glm::vec4(1.0f); // Used if texture is null
        std::shared_ptr<Texture2D> Texture = nullptr;
    };

}