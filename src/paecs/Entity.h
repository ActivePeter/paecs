#pragma once

#include "Core.h"
#include "EntityManager.h"

namespace paecs
{

    class EntityManager;
    class Entity
    {

    private:
        //const
        static const uint32_t IndexMask = (1 << config::INDEX_BITS) - 1;
        static const uint32_t VersionMask = (1 << config::VERSION_BITS) - 1;

    public:
        //type
        using Id = uint32_t;
        using Version = uint8_t;

        //construct
        Entity(EntityManager &entityManager1, Id index = 0, Version version = 0) : entityManager(entityManager1)
        {
            id = (version << config::INDEX_BITS) | index;
        }

        // Comparison operators //////////////
        bool operator==(const Entity &e) const { return getIndex() == e.getIndex(); }
        bool operator!=(const Entity &e) const { return getIndex() != e.getIndex(); }
        bool operator<(const Entity &e) const { return getIndex() < e.getIndex(); }

        // gets //////////////////////////////////
        Id getIndex() const { return id & IndexMask; } //后续考虑换成union
        Version getVersion() const { return (id >> config::INDEX_BITS) & VersionMask; }

        // component ////////////////////////////
        template <typename T>
        void addComponent(T component);
        template <typename T, typename... Args>
        void addComponent(Args &&...args);
        template <typename T>
        void removeComponent();
        template <typename T>
        bool hasComponent() const;
        template <typename T>
        T &getComponent() const;

    private:
        EntityManager &entityManager;
        Id id;
        /* data */
    };
}