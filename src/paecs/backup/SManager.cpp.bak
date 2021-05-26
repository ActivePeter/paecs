#pragma once

#include "SManager.h"

namespace paecs
{

    //
    template <typename SysClass>
    void SManager::addSystem()
    {
        std::shared_ptr<T> system(new T);
        system->world = &world;
        systems.insert(std::make_pair(std::type_index(typeid(T)), system));
        // if (hasSystem<Sys>())
        // {
        //     return;
        // }

        // std::shared_ptr<Sys> system(new Sys);
        // system->world = &world;
        // systems.insert(std::make_pair(std::type_index(typeid(Sys)), system));
    }

}
