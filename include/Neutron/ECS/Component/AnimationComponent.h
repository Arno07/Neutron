#pragma once
#include <glm/glm.hpp>

namespace Neutron {

    struct AnimationComponent {
        glm::ivec2 SheetSize = {4, 1};     // cols (frames per row), rows
        glm::ivec2 CurrentFrame = {0, 0};  // x = column, y = row
        float FrameDuration = 0.1f;
        int FrameCount = 4;
        bool Loop = true;

        float Timer = 0.0f;
    };
}