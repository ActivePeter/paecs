#pragma once

#include "SManager.h"

namespace paecs
{

    //
    template <typename T>
    void SManager::addSystem()
    {
        if (hasSystem<T>())
        {
            return;
        }

        std::shared_ptr<T> system(new T);
        system->world = &world;
        systems.insert(std::make_pair(std::type_index(typeid(T)), system));
    }

    template <typename T, typename... Args>
    void SManager::addSystem(Args &&...args)
    {
        if (hasSystem<T>())
        {
            return;
        }

        std::shared_ptr<T> system(new T(std::forward<Args>(args)...));
        system->world = &world;
        systems.insert(std::make_pair(std::type_index(typeid(T)), system));
    }

    template <typename T>
    void SManager::removeSystem()
    {
        if (!hasSystem<T>())
        {
            return;
        }

        auto it = systems.find(std::type_index(typeid(T)));
        systems.erase(it);
    }

    template <typename T>
    T &SManager::getSystem()
    {
        if (!hasSystem<T>())
        {
            throw std::runtime_error(std::string("Failed to get system: ") + typeid(T).name());
        }

        auto it = systems.find(std::type_index(typeid(T)));
        return *(std::static_pointer_cast<T>(it->second));
    }

    template <typename T>
    bool SManager::hasSystem() const
    {
        return systems.find(std::type_index(typeid(T))) != systems.end();
    }

    void SManager::addToSystems(Entity e)
    {
        const auto &entityComponentMask = scene.getEntityManager().getComponentMaskOfEntity(e);

        for (auto &it : systems)
        {
            auto &system = it.second;
            const auto &systemComponentMask = system->getComponentMask();
            auto interest = (entityComponentMask & systemComponentMask) == systemComponentMask;

            if (interest)
            {
                system->addEntity(e);
            }
        }
    }

    void SManager::removeFromSystems(Entity e)
    {
        for (auto &it : systems)
        {
            auto &system = it.second;
            system->removeEntity(e);
        }
    }
}
