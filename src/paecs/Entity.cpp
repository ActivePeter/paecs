#pragma once
#include "Core.h"
#include "Entity.h"
// #include "Component.h"
// #include "ComponentPool.h"
#include "memory"
#include "Archtype.h"
#include "ArchtypeManager.h"

namespace paecs
{
    template <typename CompType>
    EntityController EntityController::addEmptyComponent()
    {
        auto id = this->entityId;
        ComponentMask cm; //存储最终合并的componentMask
        //1，获取插件对应的mask    cm
        ComponentMaskFuncs::getComponentMaskOfComps<CompType>(cm);

        //2.如果entity之前有插件
        // auto &chunkPtr = this->entityDataPos.chunkPtr;
        if (this->entityDataPos.chunkPtr != nullptr)
        {
            //   2.1.将之前的mask和cm合并
            //      之前的mask存在archtype中，
            ComponentMaskFuncs::combineMaskB2A(cm, chunkPtr->archtypePtr->componentMask);

            //   2.2.将之前的数据内容从archtype的chunk中拷贝出来，
            //       并在之前的archtype中删除
        }

        //3，通过cm调用findOrCreateArchtype
        auto &am = this->entityManager.scene.archtypeManager;
        Archtype &targetArchtype = am.findOrCreateArchtype<CompType>(cm); //am.createArchtypeWithComponentMask(cm);

        //4，调用registMemForAnEntity
        //   获取新的entity指向的entityDataPos
        //   此时修改了原来的entityDataPos
        auto oldEntityDataPos = this->entityDataPos; //在覆盖前拷贝
        targetArchtype.allocateMemForAnEntity(this->entityDataPos);

        //5，将map中指向的entityDataPos修改掉
        //    这个不用做了。因为当前EntityController里存的就是map里内容的引用

        //6.如果之前有数据，遍历之前的插件数据拷贝到现在的chunk中
        if (oldEntityDataPos.chunkPtr != nullptr)
        {
            auto oldArchtype = oldEntityDataPos.chunkPtr->archtypePtr;
            for (const auto &oldComp : oldArchtype->compIds2InfoMap)
            {
                //从旧的chunk中读出
                this->entityDataPos.chunkPtr
                    ->cpyComponentDataFromOldDatapos2ChunkIndex(
                        &oldEntityDataPos.getCompDataHeadPtr(
                            oldComp.second.compOffsetInOneChunk,           //之前的offset
                            oldComp.second.compDiscription.componentSize), //插件的信息引用中包含size
                        oldComp.first,                                     //插件id
                        this->entityDataPos.index                          //entity在chunk中的index
                    );
            }
            //6.then  完成之后移除原来的数据
            oldArchtype->deallocateMemForAnEntity(oldEntityDataPos);
        }
    }

    template <typename CompType>
    EntityController EntityController::removeComponent()
    {
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