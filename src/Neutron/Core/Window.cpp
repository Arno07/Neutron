#include "Neutron/Core/Window.h"
#include "Neutron/Input/Input.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

namespace Neutron {

    Window::Window(int width, int height, const char* title) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW!" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // OpenGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_Window) {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        Input::SetWindowContext(m_Window);

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::OnUpdate() const {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}