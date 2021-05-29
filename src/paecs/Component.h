#pragma once

#include "Core.h"
#include <bitset>
#include <cstdint>
#include <cassert>
#include "ComponentMask.h"
#include "parallel_hashmap/phmap.h"

namespace paecs
{

    struct ComponentDiscription
    {
        size_t componentSize;
        ComponentDiscription(size_t componentSize1)
        {
            componentSize = componentSize1;
        }
        /* data */
    };

    /*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */

    // Used to be able to assign unique ids to each component type.
    class BaseComponent
    {
    public:
        using Id = uint16_t;
        static const Id MaxComponents = sizeof(uint64_t) * 8; //config::MAX_COMPONENTS;

        static uint8_t maskVecSize;

        static phmap::flat_hash_map<Id, ComponentDiscription> componentId2DiscriptionMap;
        // static uint16_t GetComponentsCnt()
        // {
        //     return nextId
        // }
        static ComponentDiscription &getDiscriptionOfComponentById(Id id)
        {
            return componentId2DiscriptionMap[id];
        }

    protected:
        static Id nextId; //静态全局量,每次递增
    };

    // Used to assign a unique id to a component type, we don't really have to make our components derive from this though.
    template <typename T>
    class Component : BaseComponent
    {
    public:
        //启动时就以及在堆内创建的变量，唯一表示一个component
        static ComponentMask componentMask;
        // Returns the unique id of Component<T>
        static Id getId()
        {
            static bool firstRun = false;
            static auto id = nextId++; //只有第一次调用会执行赋值,后续都是记忆之前的数据,
            if (!firstRun)
            {
                if (id == MaxComponents)
                {
                    BaseComponent::maskVecSize++;
                    //需要扩展ComponetMask的长度(本质是一个装着bitmask的vector)，因为archtype的map的key也是这个，所以要对key也进行扩长操作
                }
                auto &mask = Component<T>::getMask(); //获取某一类型的mask,如果mask长度改变。则会在这个函数中自动匹配
                mask[id / ComponentMaskCellSize].set(id % ComponentMaskCellSize);

                BaseComponent::componentId2DiscriptionMap[id] = ComponentDiscription(sizeof(T));
                // assert(id < MaxComponents);
            }
            firstRun = true;

            return id;
        }
        static ComponentMask &getMask()
        {
            //如果长度相等，那么直接返回，如果长度不等，则需要更新后返回
            if (Component<T>::componentMask.size() == BaseComponent::maskVecSize)
            {
                return Component<T>::componentMask;
            }
            else
            {
                Component<T>::componentMask.resize(BaseComponent::maskVecSize);
                return Component<T>::componentMask;
            }
        }
    };
    namespace ComponentIdFuncs
    {
        template <typename CompTypeFirst, typename... CompTypesAfter>
        void getIdsOfComponents(std::vector<BaseComponent::Id> &ids)
        {
            ids.push_back(Component<CompType>::getId());
            getIdsOfComponents<CompTypesAfter...>(std::vector<BaseComponent::Id> & ids);
        }
        template <typename CompType>
        void getIdsOfComponents(std::vector<BaseComponent::Id> &ids)
        {
            ids.push_back(Component<CompType>::getId());
        }
        // template <typename CompTypeFirst, typename... CompTypesAfter>
        // void getComponentMaskOfComps(ComponentMask &maskA)
        // {
        //     //获取的是引用，因为combine函数不改变参数二
        //     auto &maskB = Component<CompTypeFirst>::getMask();
        //     getComponentMaskOfComps<CompTypesAfter...>(maskA);
        //     //迭代到最底下的beforeMask时一个复制值，前面的Mask都是
        //     combineMasks(maskA, maskB);
        //     // return maskA;
        // }
        // template <typename CompType>
        // void getComponentMaskOfComps(ComponentMask &maskA)
        // {
        //     //返回的时引用，但是并不会被操作
        //     maskA = Component<CompType>::getMask();
        // }
    }

}
