#pragma once

namespace Neutron {

    class Input {
    public:
        static void SetWindowContext(void* window); // store GLFWwindow
        static bool IsKeyPressed(int keycode);       // e.g. GLFW_KEY_W

    private:
        static void* s_Window;
    };

}