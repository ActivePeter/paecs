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

        std::shared_ptr<std::vector<T>> componentVector = accommodateComponent<T>();

        if (entityId >= componentVector->getSize())
        {
            componentVector->resize(versions.size());
        }

        componentVector->set(entityId, component);
        componentMasks[entityId].set(componentId);
    }

    template <typename T, typename... Args>
    void Entity::addComponent(Args &&...args)
    {
        T component(std::forward<Args>(args)...);
        addComponent<T>(e, component);
    }

    template <typename T>
    void Entity::removeComponent()
    {
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