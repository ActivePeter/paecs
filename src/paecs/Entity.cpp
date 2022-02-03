#pragma once
#include "Entity.h"
#include "Core.h"

// #include "Component.h"
// #include "ComponentPool.h"
#include "memory"
#include "Archtype.h"
#include "ArchtypeManager.h"
#include "ComponentMask.h"

namespace paecs
{
	uint8_t* EntityDataPos::getCompDataHeadPtr(int compOffset, size_t compSize)
	{

		return &(chunkPtr->storage[compOffset + index * compSize]);
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
// //     const auto entityId = ec.getIndex();

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