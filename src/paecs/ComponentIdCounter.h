#pragma once

#include "Core.h"
#include <bitset>
#include <cstdint>
#include <cassert>
#include "ComponentMask.h"

namespace paecs
{
    /*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */

    // Used to be able to assign unique ids to each component type.
    class BaseComponentIdCounter
    {
    public:
        using Id = uint16_t;
        // static const Id MaxComponents = config::MAX_COMPONENTS;

        static uint8_t bitsetCnt;
        // static uint16_t GetComponentsCnt()
        // {
        //     return nextId
        // }

    protected:
        static Id nextId; //静态全局量,每次递增
    };

    // Used to assign a unique id to a component type, we don't really have to make our components derive from this though.
    template <typename T>
    class ComponentIdCounter : BaseComponent
    {
    public:
        //启动时就以及在堆内创建的变量，唯一表示一个component
        static ComponentMask componentMask;
        // Returns the unique id of Component<T>
        static Id getId()
        {
            static auto id = nextId++; //只有第一次调用会执行赋值,后续都是记忆之前的数据,
            if (id == MaxComponents)
            {
                BaseComponentIdCounter::bitsetCnt++;
                //需要扩展ComponetMask的长度(本质是一个装着bitmask的vector)，因为archtype的map的key也是这个，所以要对key也进行扩长操作
            }
            auto &mask = ComponentIdCounter<T>::getMask(); //获取某一类型的mask
            mask[id / ComponentMaskCellSize].set(id % ComponentMaskCellSize);
            // assert(id < MaxComponents);
            return id;
        }
        static ComponentMask &getMask()
        {
            //如果长度相等，那么直接返回，如果长度不等，则需要更新后返回
            if (ComponentIdCounter<T>::componentMask.size() == BaseComponentIdCounter::bitsetCnt)
            {
                return ComponentIdCounter<T>::componentMask;
            }
            else
            {
                ComponentIdCounter<T>::componentMask.resize(BaseComponentIdCounter::bitsetCnt);
                return ComponentIdCounter<T>::componentMask;
            }
        }
    };

}
