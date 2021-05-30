#pragma once

// #include "Event.h"
#include "Entity.h"
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
// #include "Component.h"
#include "Component.h"

namespace paecs
{

    class SystemManager;
    class World;

    // The system processes entities that it's interested in each frame. Derive from this one!
    class System
    {
    public:
        System(Scene &scene1) : scene(scene1) {}
        virtual ~System() {}
        virtual void init();
        // what component types the system requires of entities (we can use this method in the constructor for example)
        template <typename FirsrCompType, typename... RestCompTypes>
        void requireComponent();

        // returns a list of entities that the system should process each frame
        // std::vector<Entity> getEntities() { return entities; }

        // // adds an entity of interest
        // void addEntity(Entity e);

        // // if the entity is not alive anymore (during processing), the entity should be removed
        // void removeEntity(Entity e);

        const ComponentMask &getComponentMask() const { return componentMask; }

    protected:
        Scene &getScene() const;

    private:
        template <typename CompType>
        void requireComponent();
        // which components an entity must have in order for the system to process the entity
        ComponentMask componentMask;

        // vector of all entities that the system is interested in
        // std::vector<Entity> entities;

        Scene &scene;
        friend class SystemManager;
    };

    // template <typename T>
    // void System::requireComponent()
    // {
    //     const auto componentId = Component<T>::getId();
    //     componentMask.set(componentId);
    // }

}
