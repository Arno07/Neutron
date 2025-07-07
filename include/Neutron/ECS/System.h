#pragma once

#include <vector>
#include <functional>
#include "Neutron/ECS/EntityManager.h"
#include "Neutron/ECS/ComponentManager.h"

namespace Neutron {

    class System {
    public:
        virtual void Update(float deltaTime,
                            EntityManager& entityManager,
                            ComponentManager& componentManager) = 0;

        virtual ~System() = default;
    };

}