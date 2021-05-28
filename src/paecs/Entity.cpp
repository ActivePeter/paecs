#pragma once
#include "Core.h"
#include "Entity.h"
// #include "Component.h"
// #include "ComponentPool.h"
#include "memory"

namespace paecs
{
    // template <typename CompType>
    // EntityController EntityController::addComponent(CompType &comp)
    // {
    //     //未分析
    //     const Metatype *type = get_metatype<CompType>();

    //     // add_component_to_entity<CompType>(world, id);
    //     addEmptyComponent<CompType>();

    //     //optimize later
    //     if (!type->is_empty())
    //     {
    //         get_entity_component<CompType>(world, id) = comp;
    //     }
    // }

    template <typename CompType>
    EntityController EntityController::addEmptyComponent()
    {
        auto id = this->entityId;
        /**
         * 这里开始就是具体的archrtype查找或创建了，因为会添加插件
         * 一开始entity指向的chunk是空的，因为还没有插件，所以没有archtype信息
         * 如果有，就能获取到ComponentMask，然后再跟新加的Component对应的Component合并，
         * 如果没有就直接获取新新加的componentMask
         * 通过合并后的ComponentMask去查找或创建对应的Archtype
         * 查找到archtype后要做的是获取一个chunk并且标记新的位置用于存这个entity的数据，
        **/
        ComponentMask cm; //存储最终合并的componentMask
        ComponentMaskFuncs::getComponentMaskOfComps<CompType>(cm);
        auto &am = this->entityManager.scene.archtypeManager;

        if (this->entityDataPos->chunkPtr == nullptr)
        {
            goto _newArchtypeOperation;
        }
        else
        {
        }

    _newArchtypeOperation:

        auto &targetArchtype = am.createArchtypeWithComponentMask(cm);

        //未分析
        // const Metatype *temporalMetatypeArray[32];

        // const Metatype *type = get_metatype<CompType>();

        // Archetype *oldarch = get_entity_archetype(scene, id);
        // ChunkComponentList *oldlist = oldarch->componentList;
        // bool typeFound = false;
        // int lenght = oldlist->components.size();
        // for (int i = 0; i < oldlist->components.size(); i++)
        // {
        //     temporalMetatypeArray[i] = oldlist->components[i].type;

        //     //the pointers for metatypes are allways fully stable
        //     if (temporalMetatypeArray[i] == type)
        //     {
        //         typeFound = true;
        //     }
        // }

        // Archetype *newArch = oldarch;
        // if (!typeFound)
        // {

        //     temporalMetatypeArray[lenght] = type;
        //     sort_metatypes(temporalMetatypeArray, lenght + 1);
        //     lenght++;

        //     newArch = find_or_create_archetype(scene, temporalMetatypeArray, lenght);

        //     set_entity_archetype(newArch, id);
        // }
    }
}

// Entity Scene::createEntity()
// {
//     Archetype *arch = nullptr;
//     //empty component list will use the hardcoded null archetype
//     if constexpr (sizeof...(Comps) != 0)
//     {
//         static const Metatype *types[] = {adv::get_metatype<Comps>()...};
//         constexpr size_t num = (sizeof(types) / sizeof(*types));

//         adv::sort_metatypes(types, num);
//         arch = adv::find_or_create_archetype(this, types, num);
//     }
//     else
//     {
//         arch = get_empty_archetype();
//     }

//     return adv::create_entity_with_archetype(arch);
//     // Entity::Id index;

//     // if (freeIds.size() > config::MINIMUM_FREE_IDS) //可用id数量大于最小值
//     // {
//     //     index = freeIds.front(); //从可用id中取出id
//     //     freeIds.pop_front();     //去除已用
//     // }
//     // else //无可用id了
//     // {
//     //     versions.push_back(0);                     //vesions增加一个0（暂时不知道version的含义
//     //     index = (unsigned int)versions.size() - 1; //index 根据versions算出
//     //     // assert(index < (1 << Entity::IndexBits));

//     //     // if (index >= componentMasks.size()) //componentMask也暂时不知道什么意思
//     //     // {
//     //     //     // TODO: grow by doubling?
//     //     //     componentMasks.resize(index + 1);
//     //     // }
//     // }

//     // // assert(index < versions.size());
//     // Entity e(*this, index, versions[index]); //一个entity参数有index version 和this
//     // // e.ECManager = this;

//     return e;
// }
// // component //////////////////////////////////////////////////////
// const ComponentMask &Entity::getComponentMask() const
// {
// }

// template <typename T, typename... Args>
// Entity &Entity::addComponent(Args &&...args)
// {
//     T component(std::forward<Args>(args)...);
//     addComponent<T>(e, component);
// }

// // template <typename T>
// // Entity &Entity::addComponent(T component)
// // {
// //     const auto componentId = Component<T>::getId();
// //     const auto entityId = this->getIndex();

// //     //根据类型获取到存储这一类型components的pool的指针
// //     auto componentPool = ecManager.getComponentPoolOfT<T>();

// //     //如果entityId比componentdVector的size大,那么扩大vector尺寸
// //     if (entityId >= componentPool->getSize())
// //     {
// //         componentPool->resize(versions.size());
// //     }

// //     componentPool->set(entityId, component);
// //     // componentMasks[entityId].set(componentId);
// // }

// template <typename T>
// void Entity::removeComponent()
// {
//     const auto componentId = Component<T>::getId();
//     const auto entityId = e.getIndex();
//     assert(entityId < componentMasks.size());
//     // ComponentMask[entityId].t
//     componentMasks[entityId].set(componentId, false); //mask 用来标记component是否有效
// }

// template <typename T>
// bool Entity::hasComponent() const
// {
//     const auto componentId = Component<T>::getId();
//     const auto entityId = e.getIndex();
//     assert(entityId < componentMasks.size());
//     // componentMasks[entityId].;
//     //.(componentId, false);
//     return componentMasks[entityId].test(componentId);
// }

// //获取该entity对应类型的component
// template <typename T>
// T &Entity::getComponent() const
// {
//     const auto componentId = Component<T>::getId();
//     const auto entityId = e.getIndex();

//     assert(hasComponent<T>(e));
//     assert(componentId < componentPools.size());
//     // auto componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);
//     auto componentPool = ecManager.getComponentPoolOfT<T>();

//     assert(componentPool);
//     assert(entityId < componentPool->getSize());
//     return componentPool->get(entityId);
// }
// }