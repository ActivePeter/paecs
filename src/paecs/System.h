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

    class World;

    // template <typename... Comps>
    // class UpdateSystem : public System;
    namespace SystemAbout
    {
        template <class FuncType>
        struct Specializer
        {
        };
        template <class RetType, class... ArgsType>
        struct Specializer<RetType(ArgsType...)>
        {
            using SpecializedUpdateSystemType = UpdateSystem<ArgsType...>;
        };
    }
    // The system processes entities that it's interested in each frame. Derive from this one!
    class System
    {
    public:
        System(Scene &scene1) : scene(scene1) {}
        virtual ~System() {}
        virtual void init();
        virtual void update();
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

        //存储需要执行的函数指针
        void (*sysFunc)(...);
        // vector of all entities that the system is interested in
        // std::vector<Entity> entities;

        Scene &scene;
    };

    /**
     * 
     * 参考一下decs
     * 
     * **/
    // 		template<typename... Args, typename Func>
    // 		void entity_chunk_iterate(DataChunk* chnk, Func&& function) {
    // 			auto tup = std::make_tuple(get_chunk_array<Args>(chnk)...);
    // #ifndef NDEBUG
    // 			(assert(std::get<decltype(get_chunk_array<Args>(chnk))>(tup).chunkOwner == chnk), ...);
    // #endif

    // 			for (int i = chnk->header.last - 1; i >= 0; i--) {
    // 				function(std::get<decltype(get_chunk_array<Args>(chnk))>(tup)[i]...);
    // 			}
    // 		}

    //在addsystem的时候创建这样的实例
    template <typename... Comps>
    class UpdateSystem : public System
    {
    public:
        void update()
        {
            sysFunc(entityId, getCompData<Comps>()...);
        }
    };
    // template <typename T>
    // void System::requireComponent()
    // {
    //     const auto componentId = Component<T>::getId();
    //     componentMask.set(componentId);
    // }

}
