#pragma once

#include "Core.h"
#include "vector"
#include "deque"

// #include "EntityManager.h"
#include "Scene.h"
#include "Entity.h"

namespace paecs
{
    class Scene;
    class EntityManager
    {
    public:
        EntityManager(Scene &scene1) : scene(scene1) {} // {}
        Entity createEntity();

    private:
        Scene &scene;
        // vector of entities that are awaiting creation
        std::vector<Entity> createdEntities;

        // vector of entities that are awaiting destruction
        std::vector<Entity> destroyedEntities;

        // deque of free entity indices
        std::deque<Entity::Id> freeIds;

        // vector of versions (index = entity index)
        std::vector<Entity::Version> versions;
        /* data */
    };
}