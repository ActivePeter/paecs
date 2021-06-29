#pragma once
#include "Scene.h"

namespace paecs
{
    template <typename SysGroup, typename FuncType>
    Scene &Scene::addSys2Group(SysGroup &sysGroup, FuncType *func)
    {
        //若group中不包含，则执行添加group

        //1.获取函数类型
        // using functype = decltype(func);

        //2.获取到含有函数参数类型的sys类型
        // using speSys = UpdateSystem<A>;
        using speSys = SystemAbout::Specializer<FuncType>::SpecializedUpdateSystemType;
        // speSys(*this, &func);

        auto a = speSys(*this, func);
        auto b = std::make_shared<speSys>(*this, func);
        auto sysId = std::type_index(typeid(FuncType));
        // auto baseSysPtr = std::dynamic_cast<BaseSystem>(std::make_shared<speSys>(*this, func));
        systems[sysId] = std::static_pointer_cast<BaseSystem>(b);
        // systems[std::type_index(typeid(int)] =baseSysPtr;
        // std::make_shared<speSys>(*this, func);

        return *this;
        //然后根据拿到的types创建system
        // SpeSys()
        //1.获取函数的参数类型组
        // using params = decltype(util::args(helloworld));
        //2.构造sys对象
        // UpdateSystem<params>
    }

    // template <typename FuncType>
    // Scene &Scene::addSysByFunc(FuncType *func)
    // {

    // }

}