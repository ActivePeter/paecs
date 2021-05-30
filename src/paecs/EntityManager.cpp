#include "EntityManager.h"
namespace paecs
{
    EntityController EntityManager::createEntity()
    {
        EntityID entityId = {0, 0};
        if (destroyedEntities.size() > 0)
        {
            entityId = destroyedEntities.back();
            destroyedEntities.pop_back();
            entityId.generation++;
        }
        else
        {
            entityId.index = nextEntityId;
            nextEntityId++;
        }
        // auto newEntityDataPtr = std::make_shared<EntityDataPos>(nullptr, 0);
        entityId2DataPos_Map[entityId] = EntityDataPos(nullptr, 0);
        return EntityController(*this, entityId, entityId2DataPos_Map[entityId]);
        //
        /**
         * 首先要理解清楚entity的作用，
         * 游戏中会出现删除entity的时候，而archtype的数据是连续的，怎么表示这个数据被删除
         * 
         * **/
        // Archetype *arch = nullptr;
        // //empty component list will use the hardcoded null archetype
        // if constexpr (sizeof...(Comps) != 0)
        // {
        //     static const Metatype *types[] = {adv::get_metatype<Comps>()...};
        //     constexpr size_t num = (sizeof(types) / sizeof(*types));

        //     adv::sort_metatypes(types, num);
        //     arch = adv::find_or_create_archetype(this, types, num);
        // }
        // else
        // {
        //     arch = get_empty_archetype();
        // }
        // auto entityId = adv::create_entity_with_archetype(arch);
        // return EntityController(*this, entityId);
    }

}