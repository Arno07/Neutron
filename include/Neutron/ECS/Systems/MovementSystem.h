#pragma once

#include "Neutron/ECS/System.h"
#include "Neutron/ECS/Component/TransformComponent.h"
#include "Neutron/ECS/Component/VelocityComponent.h"

namespace Neutron {

    class MovementSystem : public System {
    public:
        void Update(float deltaTime,
                    EntityManager& entityManager,
                    ComponentManager& componentManager) override {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                if (!entityManager.IsValid(entity)) continue;

                if (componentManager.HasComponent<TransformComponent>(entity) &&
                    componentManager.HasComponent<VelocityComponent>(entity)) {

                    auto& transform = componentManager.GetComponent<TransformComponent>(entity);
                    auto& velocity  = componentManager.GetComponent<VelocityComponent>(entity);

                    transform.Position += velocity.Velocity * deltaTime;
                    }
            }
        }
    };

}