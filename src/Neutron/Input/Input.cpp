#include "Neutron/Input/Input.h"
#include <GLFW/glfw3.h>

namespace Neutron {

    void* Input::s_Window = nullptr;

    void Input::SetWindowContext(void* window) {
        s_Window = window;
    }

    bool Input::IsKeyPressed(int keycode) {
        if (!s_Window) return false;

        GLFWwindow* win = static_cast<GLFWwindow*>(s_Window);
        int state = glfwGetKey(win, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

}