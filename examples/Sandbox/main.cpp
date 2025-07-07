#include <Neutron/Core/Window.h>
#include <Neutron/Renderer/Renderer.h>
#include <Neutron/Renderer/SpriteRenderer.h>
#include <Neutron/Renderer/Texture2D.h>
#include <Neutron/Renderer/Camera2D.h>

#include <Neutron/Input/Input.h>

#include <Neutron/ECS/EntityManager.h>
#include <Neutron/ECS/ComponentManager.h>
#include <Neutron/ECS/System.h>

#include <Neutron/ECS/Component/TransformComponent.h>
#include <Neutron/ECS/Component/VelocityComponent.h>
#include <Neutron/ECS/Component/SpriteComponent.h>
#include <Neutron/ECS/Systems/MovementSystem.h>

#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Create the window
    Neutron::Window window(1280, 720, "Neutron Engine");

    // Initialize rendering systems
    Neutron::Renderer::Init();
    Neutron::SpriteRenderer::Init();

    // ECS Managers
    Neutron::EntityManager entityManager;
    Neutron::ComponentManager componentManager;

    // Camera setup
    Neutron::Camera2D camera(-16.0f, 16.0f, -9.0f, 9.0f);
    camera.SetPosition(glm::vec3(0.0f));

    // Load texture
    auto crateTexture = std::make_shared<Neutron::Texture2D>("assets/textures/texture.jpg");

    // Create entities
    Neutron::Entity player = entityManager.CreateEntity();
    Neutron::Entity enemy  = entityManager.CreateEntity();

    std::cout << "Created Player Entity: " << player << std::endl;
    std::cout << "Created Enemy Entity: " << enemy << std::endl;

    // Add components to player
    componentManager.AddComponent(player, Neutron::TransformComponent{
        glm::vec3{5.0f, 2.0f, 0.0f},
        glm::vec3{0.0f},
        glm::vec3{1.0f}
    });

    componentManager.AddComponent(player, Neutron::VelocityComponent{
        glm::vec3{1.0f, 0.0f, 0.0f}
    });

    // ✅ Assign texture to SpriteComponent
    componentManager.AddComponent(player, Neutron::SpriteComponent{
        glm::vec4{1.0f, 0.0f, 0.0f, 1.0f},
        crateTexture
    });

    // Log initial position
    auto& startTransform = componentManager.GetComponent<Neutron::TransformComponent>(player);
    std::cout << "Player Position: " << startTransform.Position.x << ", "
              << startTransform.Position.y << ", "
              << startTransform.Position.z << std::endl;

    // Simulate 1 second of movement
    Neutron::MovementSystem movementSystem;
    for (int i = 0; i < 60; ++i) {
        movementSystem.Update(1.0f / 60.0f, entityManager, componentManager);
    }

    auto& endTransform = componentManager.GetComponent<Neutron::TransformComponent>(player);
    std::cout << "Player moved to: " << endTransform.Position.x << ", "
              << endTransform.Position.y << ", "
              << endTransform.Position.z << std::endl;

    // ======= Main Game Loop =======
    while (!window.ShouldClose()) {
        // Input example
        if (Neutron::Input::IsKeyPressed(GLFW_KEY_SPACE)) {
            std::cout << "Spacebar is being pressed!" << std::endl;
        }

        // Clear the screen
        Neutron::Renderer::SetClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        Neutron::Renderer::Clear();

        // Render all entities with Transform + Sprite
        if (componentManager.HasComponent<Neutron::TransformComponent>(player) &&
            componentManager.HasComponent<Neutron::SpriteComponent>(player)) {

            const auto& transform = componentManager.GetComponent<Neutron::TransformComponent>(player);
            const auto& sprite    = componentManager.GetComponent<Neutron::SpriteComponent>(player);

            Neutron::SpriteRenderer::DrawQuad(
                transform.Position,
                transform.Scale,
                sprite.Color,
                sprite.Texture,
                camera.GetViewProjection()
            );
        }

        window.OnUpdate();
    }

    // Shutdown systems
    Neutron::SpriteRenderer::Shutdown();
    Neutron::Renderer::Shutdown();

    return 0;
}