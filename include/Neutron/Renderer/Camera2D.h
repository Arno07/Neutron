#pragma once

#include <glm/glm.hpp>

namespace Neutron {

    class Camera2D {
    public:
        Camera2D(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& position);
        const glm::vec3& GetPosition() const;

        const glm::mat4& GetViewProjection() const;

    private:
        void RecalculateView();

    private:
        glm::mat4 m_Projection;
        glm::mat4 m_View;
        glm::mat4 m_ViewProjection;

        glm::vec3 m_Position = glm::vec3(0.0f);
    };

}