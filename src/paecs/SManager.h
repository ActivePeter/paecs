#pragma once

#include "parallel_hashmap/phmap.h"
#include <typeindex>

// #include "EntityManager.h"
#include "Core.h"
#include "Scene.h"
#include "System.h"
// using namespace phmap;

namespace paecs
{
    // classes ///////////////////////////////////////////////////////////////////////////////
    class Scene;
    class SManager
    {

    public:
        SManager(Scene &scene1) : scene(scene1) {} // {}

        template <typename T>
        void addSystem();

        template <typename T, typename... Args>
        void addSystem(Args &&...args);

        template <typename T>
        void removeSystem();

        template <typename T>
        T &getSystem();

        template <typename T>
        bool hasSystem() const;

        // adds an entity to each system that is interested of the entity
        void addToSystems(Entity e);

        // removes an entity from interested systems' entity lists
        void removeFromSystems(Entity e);

    private:
        Scene &scene;
        phmap::flat_hash_map<std::type_index, std::shared_ptr<System>> systems;
        // std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        /* data */
    };

}
