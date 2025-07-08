#pragma once

#include <Neutron/ECS/EntityManager.h>
#include <Neutron/ECS/ComponentManager.h>
#include <Neutron/ECS/Component/AnimationComponent.h>
#include <Neutron/ECS/Component/SpriteComponent.h>

namespace Neutron {

    class AnimationSystem {
    public:
        void Update(float deltaTime, EntityManager& entities, ComponentManager& components);
    };

}