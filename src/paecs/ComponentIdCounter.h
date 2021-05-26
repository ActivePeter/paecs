#pragma once

#include "Core.h"
#include <bitset>
#include <cstdint>
#include <cassert>

namespace paecs
{
    /*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */

    // Used to be able to assign unique ids to each component type.
    struct BaseComponentIdCounter
    {
        using Id = uint8_t;
        // static const Id MaxComponents = config::MAX_COMPONENTS;

    protected:
        static Id nextId; //静态全局量,每次递增
    };

    // Used to assign a unique id to a component type, we don't really have to make our components derive from this though.
    template <typename T>
    struct ComponentIdCounter : BaseComponent
    {
        // Returns the unique id of Component<T>
        static Id getId()
        {
            static auto id = nextId++; //只有第一次调用会执行赋值,后续都是记忆之前的数据,
            // if(id==MaxComponents)
            // assert(id < MaxComponents);
            return id;
        }
    };

    // Used to keep track of which components an entity has and also which entities a system is interested in.
    using ComponentMask = std::bitset<config::MAX_COMPONENTS>; //<total size>
}
