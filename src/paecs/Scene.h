#pragma once
// #include "ECManager.h"
// #include "SManager.h"
#include <memory>
#include <typeindex>

#include "parallel_hashmap/phmap.h"

#include "Core.h"
#include "System.h"
#include "Entity.h"
#include "Archtype.h"
#include "EntityManager.h"

namespace paecs
{
    // class ECManager;
    class Scene
    {
    private:
        phmap::flat_hash_map<std::type_index, std::shared_ptr<System>> systems;

        // std::unique_ptr<Entity> = nullptr;
        // std::unique_ptr<SManager> sManager = nullptr;
        /* data */

        ArchtypeManager archtypeManager = ArchtypeManager(*this);
        EntityManager entityManager = EntityManager(*this);

    public:
        Scene(/* args */);
        // ECManager &getEntityManager() const;
        // SManager &getSystemManager() const;

        template <typename SysClass>
        Scene &addSys();

        template <typename SysClass>
        bool hasSys();
        // EventManager &getEventManager() const;

        template <typename Func>
        void foreachComps(Func &&func);

        template <typename... Comps>
        inline EntityController createEntity();

        // std::unique_ptr<EventManager> eventManager = nullptr;
        // ~Scene();
        void loop();
    };

    std::unique_ptr<Scene> createScene();

}