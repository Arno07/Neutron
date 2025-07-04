#include <Neutron/Core/Window.h>
#include <Neutron/Renderer/Renderer.h>
#include <Neutron/Input/Input.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    Neutron::Window window(1280, 720, "Neutron Engine");
    Neutron::Renderer::Init();

    while (!window.ShouldClose()) {
        if (Neutron::Input::IsKeyPressed(GLFW_KEY_SPACE)) {
            std::cout << "Spacebar is being pressed!" << std::endl;
        }

        Neutron::Renderer::SetClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        Neutron::Renderer::Clear();
        window.OnUpdate();
    }

    Neutron::Renderer::Shutdown();
    return 0;
}