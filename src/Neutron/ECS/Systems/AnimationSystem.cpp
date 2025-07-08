#include "Neutron/ECS/Systems/AnimationSystem.h"
#include <iostream>

namespace Neutron {

    void AnimationSystem::Update(float deltaTime, EntityManager& entityManager, ComponentManager& componentManager) {
        for (Entity entity : entityManager.GetAllEntities()) {
            if (!componentManager.HasComponent<AnimationComponent>(entity) ||
                !componentManager.HasComponent<SpriteComponent>(entity))
                continue;

            auto& anim = componentManager.GetComponent<AnimationComponent>(entity);
            auto& sprite = componentManager.GetComponent<SpriteComponent>(entity);

            anim.Timer += deltaTime;

            if (anim.Timer >= anim.FrameDuration) {
                anim.Timer = 0.0f;

                int frameIndex = anim.CurrentFrame.y * anim.SheetSize.x + anim.CurrentFrame.x;
                frameIndex++;

                if (frameIndex >= anim.FrameCount) {
                    if (anim.Loop)
                        frameIndex = 0;
                    else
                        frameIndex = anim.FrameCount - 1;
                }

                // Convert linear index back to 2D coordinates
                anim.CurrentFrame.x = frameIndex % anim.SheetSize.x;
                anim.CurrentFrame.y = frameIndex / anim.SheetSize.x;

                // Calculate frame size automatically
                glm::vec2 frameSize = {
                    1.0f / anim.SheetSize.x,
                    1.0f / anim.SheetSize.y
                };

                sprite.Tiling = frameSize;
                sprite.Offset = frameSize * glm::vec2(anim.CurrentFrame);

                std::cout << "[Animation] Entity " << entity
                          << " | Frame: (" << anim.CurrentFrame.x << "," << anim.CurrentFrame.y << ")"
                          << " | Offset: " << sprite.Offset.x << "," << sprite.Offset.y
                          << " | Tiling: " << sprite.Tiling.x << "," << sprite.Tiling.y
                          << std::endl;
            }
        }
    }

}