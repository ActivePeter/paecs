#pragma once
#include "Scene.h"
#include "parallel_hashmap/phmap.h"
#include "Entity.h"
#include "list"
#include "unordered_map"

namespace paecs
{
	class Scene;
	struct EntityID;
	struct EntityDataPos;
	class EntityController;

	class EntityManager
	{

	public:
		EntityManager(Scene &scene1) : scene(scene1) {}

		//创建entity
		EntityController createEntity();
		EntityController createFinalEntity();

		//删除entity
		bool deleteEntity(EntityID entityId);

		Scene &scene;

	private:
		//规定：从头部加入,从尾部取出
		std::list<EntityID> destroyedEntities;
		int nextEntityId = 0;

		/**指向的内容需要包括这些信息
		 * chunk指针，在chunk中的index,
		 * 由此可以知道chunk中需要取出一部分信息用于包含archtype的指针，才能保留他的类型信息，
		 **/
		//    当这句话放屁                                 使用指针的原因：entity为空插件时不指向任何的chunk，此时为空指针
		// phmap::flat_hash_map<EntityID, std::shared_ptr<EntityDataPos>> entityId2DataPos_Map;
		// std::unordered_map<EntityID, EntityDataPos> entityId2DataPos_Map;
		phmap::flat_hash_map<EntityID, EntityDataPos> entityId2DataPos_Map;
	};
}
