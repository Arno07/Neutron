#include "Neutron/Renderer/SpriteRenderer.h"
#include "Neutron/Renderer/Texture2D.h"
#include "Neutron/Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Neutron {

    unsigned int SpriteRenderer::s_VAO = 0;
    unsigned int SpriteRenderer::s_VBO = 0;
    std::unique_ptr<Shader> SpriteRenderer::s_Shader = nullptr;
    glm::mat4 SpriteRenderer::s_Projection;

    void SpriteRenderer::Init() {
        // Initialize an empty dynamic VBO (we'll update it per draw)
        glGenVertexArrays(1, &s_VAO);
        glGenBuffers(1, &s_VBO);

        glBindVertexArray(s_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, nullptr, GL_DYNAMIC_DRAW); // 4 vertices × 4 floats

        // position (2 floats) + texCoord (2 floats)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        // Load shader
        s_Shader = std::make_unique<Shader>(
            "assets/shaders/Simple2D.vert",
            "assets/shaders/Simple2D.frag"
        );

        // Setup orthographic projection (left, right, bottom, top)
        s_Projection = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f);
    }

    void SpriteRenderer::Shutdown() {
        glDeleteVertexArrays(1, &s_VAO);
        glDeleteBuffers(1, &s_VBO);
        s_Shader.reset();
    }

    void SpriteRenderer::DrawQuad(const glm::vec3& position,
                                   const glm::vec3& scale,
                                   const glm::vec4& color,
                                   const std::shared_ptr<Texture2D>& texture,
                                   const glm::vec2& tiling,
                                   const glm::vec2& offset,
                                   const glm::mat4& viewProjection) {
        // Calculate model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        model = glm::scale(model, scale);
        glm::mat4 mvp = viewProjection * model;

        // Dynamic quad vertex buffer with per-frame UVs
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        glm::vec2 uvBase[] = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };

        float vertices[16]; // 4 vertices × (2 pos + 2 uv)

        for (int i = 0; i < 4; ++i) {
            vertices[i * 4 + 0] = positions[i * 2 + 0];
            vertices[i * 4 + 1] = positions[i * 2 + 1];
            vertices[i * 4 + 2] = uvBase[i].x * tiling.x + offset.x;
            vertices[i * 4 + 3] = uvBase[i].y * tiling.y + offset.y;
        }

        // Upload new quad vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        // Use shader and set uniforms
        s_Shader->Use();
        s_Shader->SetMat4("u_MVP", mvp);
        s_Shader->SetVec4("u_Color", color);

        if (texture) {
            texture->Bind();
            glUniform1i(glGetUniformLocation(s_Shader->GetID(), "u_Texture"), 0);
            glUniform1i(glGetUniformLocation(s_Shader->GetID(), "u_UseTexture"), 1);
        } else {
            glUniform1i(glGetUniformLocation(s_Shader->GetID(), "u_UseTexture"), 0);
        }

        glBindVertexArray(s_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

}