#pragma once
#include "Core.h"
#include "Entity.h"

namespace paecs
{
    template <typename T>
    void Entity::addComponent(T component)
    {
        const auto componentId = Component<T>::getId();
        const auto entityId = e.getIndex();
        std::shared_ptr<Pool<T>> componentPool = accommodateComponent<T>();

        if (entityId >= componentPool->getSize())
        {
            componentPool->resize(versions.size());
        }

        componentPool->set(entityId, component);
        componentMasks[entityId].set(componentId);
    }

}