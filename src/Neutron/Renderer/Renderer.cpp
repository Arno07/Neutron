//
// Created by Antareep Saha Roy on 03/07/25.
//
#include "Neutron/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Neutron {

    void Renderer::Init() {
        // Placeholder (depth test, blending, etc. can go here)
    }

    void Renderer::Shutdown() {
        // Cleanup if needed
    }

    void Renderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

}