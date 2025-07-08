//
// Created by Antareep Saha Roy on 04/07/25.
//
#include "Neutron/ECS/EntityManager.h"
#include <cassert>

namespace Neutron {

    EntityManager::EntityManager() { }

    Entity EntityManager::CreateEntity() {
        Entity entity = m_NextEntityID++;
        m_Entities.push_back(entity);    // Track it
        return entity;
    }

    void EntityManager::DestroyEntity(Entity entity) {
        m_ActiveEntities.erase(entity);
    }

    bool EntityManager::IsValid(Entity entity) const {
        return m_ActiveEntities.find(entity) != m_ActiveEntities.end();
    }

}