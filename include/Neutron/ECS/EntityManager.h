#pragma once

#include <cstdint>
#include <unordered_set>

namespace Neutron {

    using Entity = std::uint32_t;
    const Entity MAX_ENTITIES = 10000;

    class EntityManager {
    public:
        EntityManager();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        bool IsValid(Entity entity) const;
        const std::vector<Entity>& GetAllEntities() const { return m_Entities; }

    private:
        std::vector<Entity> m_Entities;  // Track created entities
        std::unordered_set<Entity> m_ActiveEntities;
        Entity m_NextEntityID = 0;
    };

}