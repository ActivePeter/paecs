#pragma once
#include "Scene.h"
#include "parallel_hashmap/phmap.h"
namespace paecs
{
    class EntityManager
    {
        Scene &scene;

    public:
        EntityManager(Scene &scene1) : scene(scene1) {}
        EntityController createEntity();
        void deleteEntity(EntityID entityId);

    private:
        //规定：从头部加入,从尾部取出
        std::list<EntityID> destroyedEntities;
        int nextEntityId = 0;

        /**指向的内容需要包括这些信息
         * chunk指针，在chunk中的index,
         * 由此可以知道chunk中需要取出一部分信息用于包含archtype的指针，才能保留他的类型信息，
         **/
        phmap::flat_hash_map<EntityID, EntityDataPos> entityId2Data_Map;
    };
}
