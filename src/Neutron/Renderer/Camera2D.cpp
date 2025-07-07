//
// Created by Antareep Saha Roy on 07/07/25.
//
#include "Neutron/Renderer/Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Neutron {

    Camera2D::Camera2D(float left, float right, float bottom, float top)
        : m_Projection(glm::ortho(left, right, bottom, top)) {
        RecalculateView();
    }

    void Camera2D::SetPosition(const glm::vec3& position) {
        m_Position = position;
        RecalculateView();
    }

    const glm::vec3& Camera2D::GetPosition() const {
        return m_Position;
    }

    const glm::mat4& Camera2D::GetViewProjection() const {
        return m_ViewProjection;
    }

    void Camera2D::RecalculateView() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), -m_Position);
        m_View = transform;
        m_ViewProjection = m_Projection * m_View;
    }

}