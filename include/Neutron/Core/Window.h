#pragma once

struct GLFWwindow;

namespace Neutron {

    class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool ShouldClose() const;
        void OnUpdate() const;

        GLFWwindow* GetNativeWindow() const { return m_Window; }

    private:
        GLFWwindow* m_Window;
    };

}