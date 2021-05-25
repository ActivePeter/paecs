#pragma once

#include "Core.h"
#include "Scene.h"
// #include "ECManager.h"

namespace paecs
{
    struct EntityID
    {
        uint32_t index;
        uint32_t generation;
    };

    class EntityController
    {
    private:
        Scene &scene;
        EntityID entityId;
        /* data */
    public:
        EntityController(Scene &scene1, EntityID entityId1) : scene(scene1),
                                                              entityId(entityId1) {}
        // template <typename CompType>
        // EntityController addComponent(CompType &comp);

        template <typename CompType>
        EntityController addEmptyComponent();
    };

    // // class ECManager;
    // class Entity
    // {

    // private:
    //     // //const
    //     // static const uint32_t IndexMask = (1 << config::INDEX_BITS) - 1;
    //     // static const uint32_t VersionMask = (1 << config::VERSION_BITS) - 1;

    // public:
    //     //type
    //     using Id = uint32_t;
    //     using Version = uint8_t;

    //     //construct
    //     // Entity(ECManager &ECManager1, Id index = 0, Version version = 0) : ecManager(ECManager1)
    //     // {
    //     //     id = (version << config::INDEX_BITS) | index;
    //     // }

    //     // Comparison operators //////////////
    //     // bool operator==(const Entity &e) const { return getIndex() == e.getIndex(); }
    //     // bool operator!=(const Entity &e) const { return getIndex() != e.getIndex(); }
    //     // bool operator<(const Entity &e) const { return getIndex() < e.getIndex(); }

    //     // // gets //////////////////////////////////
    //     // Id getIndex() const { return id & IndexMask; } //后续考虑换成union
    //     // Version getVersion() const { return (id >> config::INDEX_BITS) & VersionMask; }
    //     // const ComponentMask &getComponentMask() const;

    //     // component ////////////////////////////
    //     // template <typename T>
    //     // void addComponents(T component);

    //     // template <typename T>
    //     // Entity &addComponent(T component);

    //     // template <typename T, typename... Args>
    //     // Entity &addComponent(Args &&...args);
    //     // template <typename T>
    //     // void removeComponent();
    //     // template <typename T>
    //     // bool hasComponent() const;
    //     // template <typename T>
    //     // T &getComponent() const;
    //     template <typename C>
    //     inline void ECSWorld::add_component(EntityID id, C &comp)
    //     {
    //         adv::add_component_to_entity<C>(this, id, comp);
    //     }

    // private:
    //     // ECManager &ecManager;
    //     Id id;

    //     /* data */
    // };
}