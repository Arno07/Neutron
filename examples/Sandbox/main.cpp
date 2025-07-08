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
#include <Neutron/ECS/Component/AnimationComponent.h>
#include <Neutron/ECS/Systems/MovementSystem.h>
#include <Neutron/ECS/Systems/AnimationSystem.h>

#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Window
    Neutron::Window window(1280, 720, "Neutron Engine");

    // Init renderers
    Neutron::Renderer::Init();
    Neutron::SpriteRenderer::Init();

    // ECS
    Neutron::EntityManager entityManager;
    Neutron::ComponentManager componentManager;

    Neutron::Camera2D camera(-16.0f, 16.0f, -9.0f, 9.0f);
    camera.SetPosition(glm::vec3(0.0f));

    auto texture = std::make_shared<Neutron::Texture2D>("assets/textures/AlienRun.png");

    // Entities
    Neutron::Entity player = entityManager.CreateEntity();
    Neutron::Entity enemy = entityManager.CreateEntity();

    componentManager.AddComponent(player, Neutron::TransformComponent{
    glm::vec3{5.0f, 2.0f, 0.0f},  // position
    glm::vec3{0.0f},              // rotation
    glm::vec3{2.0f, 2.0f, 1.0f} // scale in world units
});

    componentManager.AddComponent(player, Neutron::VelocityComponent{
        glm::vec3{1.0f, 0.0f, 0.0f}
    });

    componentManager.AddComponent(player, Neutron::SpriteComponent{
    glm::vec4(1.0f),
    texture
});

    componentManager.AddComponent(player, Neutron::AnimationComponent{
        glm::ivec2(17, 1),  // 4 columns, 2 rows
        glm::ivec2(0, 0),  // start at (0,0)
        0.15f,             // 0.15 seconds/frame
        17,                 // total number of frames
        true               // loop
    });

    componentManager.AddComponent(player, Neutron::AnimationComponent{
        glm::vec2(0.25f, 1.0f),     // FrameSize
        glm::ivec2(0, 0),           // Start frame
        0.1f,                       // Frame duration (faster for testing)
        4,                          // Frame count
        true                        // Looping
    });

    // Systems
    Neutron::MovementSystem movementSystem;
    Neutron::AnimationSystem animationSystem;

    // Timing
    float lastTime = glfwGetTime();


    // === MAIN LOOP ===
    while (!window.ShouldClose()) {


        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        std::cout << "deltaTime: " << deltaTime << std::endl;

        // === Input ===
        if (Neutron::Input::IsKeyPressed(GLFW_KEY_SPACE)) {
            std::cout << "[Input] Spacebar is pressed!\n";
        }

        // === Update ECS ===
        movementSystem.Update(deltaTime, entityManager, componentManager);
        animationSystem.Update(deltaTime, entityManager, componentManager);

        // === Render ===
        Neutron::Renderer::SetClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        Neutron::Renderer::Clear();

        // Draw animated player
        if (componentManager.HasComponent<Neutron::TransformComponent>(player) &&
            componentManager.HasComponent<Neutron::SpriteComponent>(player)) {

            const auto& transform = componentManager.GetComponent<Neutron::TransformComponent>(player);
            const auto& sprite = componentManager.GetComponent<Neutron::SpriteComponent>(player);

            // 🧪 Debug log
            std::cout << "[Render] Offset X: " << sprite.Offset.x << " | Frame UV tile: " << sprite.Tiling.x << std::endl;

            Neutron::SpriteRenderer::DrawQuad(
                transform.Position,
                transform.Scale,
                sprite.Color,
                sprite.Texture,
                sprite.Tiling,
                sprite.Offset,
                camera.GetViewProjection()
            );
        }

        window.OnUpdate();
    }

    // Shutdown
    Neutron::SpriteRenderer::Shutdown();
    Neutron::Renderer::Shutdown();

    return 0;
}