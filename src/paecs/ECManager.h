#pragma once

#include "Core.h"
#include "vector"
#include "deque"

// #include "ECManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "ComponentPool.h"

namespace paecs
{
    class Scene;
    class ECManager
    {
    public:
        ECManager(Scene &scene1) : scene(scene1) {} // {}
        Entity createEntity();

        //获取对应类型的component的Vector
        template <typename T>
        std::shared_ptr<ComponentVec<T>> getComponentVectorOfT();

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

        // vector of component pools, each pool contains all the data for a certain component type
        // vector index = component id, pool index = entity id
        std::vector<std::shared_ptr<AbstractComponentPool>> componentVectors;
    };
}