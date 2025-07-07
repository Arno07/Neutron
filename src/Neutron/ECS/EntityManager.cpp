//
// Created by Antareep Saha Roy on 04/07/25.
//
#include "Neutron/ECS/EntityManager.h"
#include <cassert>

namespace Neutron {

    EntityManager::EntityManager() { }

    Entity EntityManager::CreateEntity() {
        assert(m_NextEntityID < MAX_ENTITIES && "Too many entities!");
        Entity id = m_NextEntityID++;
        m_ActiveEntities.insert(id);
        return id;
    }

    void EntityManager::DestroyEntity(Entity entity) {
        m_ActiveEntities.erase(entity);
    }

    bool EntityManager::IsValid(Entity entity) const {
        return m_ActiveEntities.find(entity) != m_ActiveEntities.end();
    }

}