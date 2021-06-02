#include "Component.h"
#include "parallel_hashmap/phmap.h"

namespace paecs
{
    template <typename T>
    BaseComponent::Id Component<T>::getId()
    {

        auto &singleton = Component<T>::getInstance();
        return singleton.id;
        // static bool firstRun = false;
        // static auto id = nextId++; //只有第一次调用会执行赋值,后续都是记忆之前的数据,
        // if (!firstRun)
        // {
        //     if (id == MaxComponents)
        //     {
        //         BaseComponent::maskVecSize++;
        //         //需要扩展ComponetMask的长度(本质是一个装着bitmask的vector)，因为archtype的map的key也是这个，所以要对key也进行扩长操作
        //     }
        //     auto &mask = Component<T>::getMask(); //获取某一类型的mask,如果mask长度改变。则会在这个函数中自动匹配
        //     mask[id / ComponentMaskCellSize].set(id % ComponentMaskCellSize);

        //     BaseComponent::componentId2DiscriptionMap[id] = ComponentDiscription(sizeof(T));
        //     // assert(id < MaxComponents);
        // }
        // firstRun = true;

        // return id;
    }

    template <typename T>
    ComponentMask &Component<T>::getMask()
    {

        auto &singleton = Component<T>::getInstance();
        //如果长度相等，那么直接返回，如果长度不等，则需要更新后返回
        if (singleton.cm.size() == BaseComponent::maskVecSize)
        {
            return singleton.cm;
        }
        else
        {
            singleton.cm.resize(BaseComponent::maskVecSize);
            return singleton.cm;
        }
    }

    template <typename T>
    Component<T> &Component<T>::getInstance()
    {

        if (!singleton)
        {
            singleton = new Component<T>();
        }
        return *singleton;
    }

    /*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */
    BaseComponent::Id BaseComponent::nextId = 0;
    uint8_t BaseComponent::maskVecSize = 1;

    static phmap::flat_hash_map<BaseComponent::Id, ComponentDiscription> componentId2DiscriptionMap;
}
