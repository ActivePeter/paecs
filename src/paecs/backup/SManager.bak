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

        template <typename SysClass>
        void addSystem();

    private:
        Scene &scene;
        phmap::flat_hash_map<std::type_index, std::shared_ptr<System>> systems;
        // std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        /* data */
    };

}
