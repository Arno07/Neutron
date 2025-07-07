#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <cassert>
#include <bitset>
#include "Neutron/ECS/EntityManager.h"

namespace Neutron {

    // Internal interface for component storage
    class IComponentStorage {
    public:
        virtual ~IComponentStorage() = default;
        virtual void Remove(Entity entity) = 0;
        virtual bool Has(Entity entity) const = 0;
    };

    // Actual storage class for a specific component type
    template<typename T>
    class ComponentStorage : public IComponentStorage {
    public:
        void Add(Entity entity, const T& component) {
            m_Components[entity] = component;
        }

        void Remove(Entity entity) override {
            m_Components.erase(entity);
        }

        bool Has(Entity entity) const override {
            return m_Components.find(entity) != m_Components.end();
        }

        T& Get(Entity entity) {
            assert(Has(entity));
            return m_Components[entity];
        }

    private:
        std::unordered_map<Entity, T> m_Components;
    };

    // Manager that handles all component types
    class ComponentManager {
    public:
        template<typename T>
        void AddComponent(Entity entity, const T& component) {
            GetOrCreateStorage<T>()->Add(entity, component);
        }

        template<typename T>
        void RemoveComponent(Entity entity) {
            auto* storage = GetStorage<T>();
            if (storage) {
                storage->Remove(entity);
            }
        }

        template<typename T>
        bool HasComponent(Entity entity) const {
            auto* storage = GetStorage<T>();
            return storage ? storage->Has(entity) : false;
        }

        template<typename T>
        T& GetComponent(Entity entity) {
            return GetOrCreateStorage<T>()->Get(entity);
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> m_Storages;

        template<typename T>
        ComponentStorage<T>* GetStorage() const {
            auto it = m_Storages.find(typeid(T));
            if (it == m_Storages.end()) return nullptr;
            return static_cast<ComponentStorage<T>*>(it->second.get());
        }

        template<typename T>
        ComponentStorage<T>* GetOrCreateStorage() {
            auto it = m_Storages.find(typeid(T));
            if (it == m_Storages.end()) {
                m_Storages[typeid(T)] = std::make_unique<ComponentStorage<T>>();
            }
            return static_cast<ComponentStorage<T>*>(m_Storages[typeid(T)].get());
        }
    };

}