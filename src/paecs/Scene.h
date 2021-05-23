#pragma once

#include "Core.h"

#include "EntityManager.h"
#include "SystemManager.h"

#include <memory>

namespace paecs
{
    class EntityManager;
    class Scene
    {
    private:
        /* data */
    public:
        Scene(/* args */);
        std::unique_ptr<EntityManager> entityManager = nullptr;
        std::unique_ptr<SystemManager> systemManager = nullptr;
        // std::unique_ptr<EventManager> eventManager = nullptr;
        // ~Scene();
    };

}