
#include "Core.h"
#include "Scene.h"
#include "memory"
#include "System.h"

namespace paecs
{
    Scene::Scene(/* args */)
    {
        // ecManager = std::make_unique<ECManager>(*this);
        // sManager = std::make_unique<SManager>(*this);
        // eventManager = std::make_unique<EventManager>(*this);
    }

    /////////////////////////////////////////////////////
    // system
    /////////////////////////////////////////////////////
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
        return *this;
    }

    template <typename SysClass>
    bool Scene::hasSys()
    {
    }

    //testing
    void helloworld(int a, bool b)
    {
    }
    template <typename FuncType>
    Scene &Scene::addSysByFunc(FuncType func)
    {
        //1.获取函数类型
        using functype = decltype(helloworld);

        //2.获取到含有函数参数类型的sys类型
        using speSys = SystemAbout::Specializer<functype>::SpecializedUpdateSystemType;

        //然后根据拿到的types创建system

        //1.获取函数的参数类型组
        // using params = decltype(util::args(helloworld));
        //2.构造sys对象
        // UpdateSystem<params>
    }
    void Scene::loop()
    { //遍历所有system
    }

    /////////////////////////////////////////////////////
    // comp
    /////////////////////////////////////////////////////
    template <typename Func>
    void Scene::foreachComps(Func &&func)
    {
        using paramTypes = decltype(adv::args(&Func::operator()));

        // Query query;
        // adv::unpack_querywith(paramTypes{}, query).build();

        // for_each<Func>(query, std::move(function));
    }

    std::unique_ptr<Scene> createScene()
    {
        return std::make_unique<Scene>();
    }

    /////////////////////////////////////////////////////
    // entity
    /////////////////////////////////////////////////////
    template <typename... Comps>
    inline EntityController Scene::createEntity()
    {
        return entityManager.createEntity();
    }

    inline bool Scene::deleteEntity(EntityID id)
    {
        return this->entityManager.deleteEntity(id);
    }
}