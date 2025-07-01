#include <Neutron/Core/Window.h>

int main() {
    Neutron::Window window(1280, 720, "Neutron Engine Window");

    while (!window.ShouldClose()) {
        window.OnUpdate();
    }

    return 0;
}