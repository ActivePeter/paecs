#pragma once
#include "Core.h"
#include "Entity.h"
#include "Component.h"
#include "memory"

namespace paecs
{
    // component //////////////////////////////////////////////////////
    template <typename T>
    void Entity::addComponent(T component)
    {
        const auto componentId = Component<T>::getId();
        const auto entityId = this->getIndex();

        //根据类型获取到存储这一类型components的pool的指针
        auto componentPool = ecManager.getComponentPoolOfT<T>();

        //如果entityId比componentdVector的size大,那么扩大vector尺寸
        if (entityId >= componentPool->getSize())
        {
            componentPool->resize(versions.size());
        }

        componentPool->set(entityId, component);
        // componentMasks[entityId].set(componentId);
    }

    template <typename T>
    void Entity::removeComponent()
    {
        const auto componentId = Component<T>::getId();
        const auto entityId = e.getIndex();
        assert(entityId < componentMasks.size());
        componentMasks[entityId].set(componentId, false);
    }

    template <typename T>
    bool Entity::hasComponent() const
    {
    }

    template <typename T>
    T &Entity::getComponent() const
    {
    }
}