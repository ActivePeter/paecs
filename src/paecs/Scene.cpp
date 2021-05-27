
#include "Core.h"
#include "Scene.h"
#include "memory"

namespace paecs
{
    Scene::Scene(/* args */)
    {
        // ecManager = std::make_unique<ECManager>(*this);
        // sManager = std::make_unique<SManager>(*this);
        // eventManager = std::make_unique<EventManager>(*this);
    }

    template <typename SysClass>
    Scene &Scene::addSys()
    {
        if (hasSys<SysClass>())
        {
            goto end;
        }

        std::shared_ptr<SysClass> system(new SysClass(*this));
        system->init();
        systems.insert(std::make_pair(std::type_index(typeid(SysClass)), system));
    end:
        return this;
    }

    template <typename SysClass>
    bool Scene::hasSys()
    {
    }

    template <typename Func>
    void Scene::foreachComps(Func &&func)
    {
        using paramTypes = decltype(adv::args(&Func::operator()));

        // Query query;
        // adv::unpack_querywith(paramTypes{}, query).build();

        // for_each<Func>(query, std::move(function));
    }

    void Scene::loop()
    { //遍历所有system
    }

    std::unique_ptr<Scene> createScene()
    {
        return std::make_unique<Scene>();
    }

    template <typename... Comps>
    inline EntityController Scene::createEntity()
    {
        return entityManager.createEntity();
    }
}