#include "EntityManager.h"
namespace paecs
{
	EntityController EntityManager::createEntity()
	{
		EntityID entityId = {0, 0};
		if (destroyedEntities.size() > 0)
		{
			//从销毁的entity中取出一个
			entityId = destroyedEntities.back();
			destroyedEntities.pop_back();
			//版本+1
			entityId.generation++;
		}
		else
		{
			entityId.index = nextEntityId;
			//nextEntityId每次使用自增1
			nextEntityId++;
		}
		// auto newEntityDataPosPtr = std::make_shared<EntityDataPos>(nullptr, 0);
		entityId2DataPos_Map[entityId] = EntityDataPos(nullptr, 0);
		return EntityController(*this, entityId, entityId2DataPos_Map[entityId]);
	}

	// /**
	//  * final entity will never be destroyed
	// */
	// EntityController EntityManager::createFinalEntity()
	// {
	// }

	bool EntityManager::deleteEntity(EntityID entityId)
	{
		if (entityId2DataPos_Map.contains(entityId))
		{
			return false;
		}
		//1.加入已经删除的entity中
		this->destroyedEntities.push_back(entityId);
		//2.将指向的数据内容deallocate
		auto &entityDataPos = entityId2DataPos_Map[entityId];
		entityDataPos.chunkPtr->archtypePtr->deallocateMemForAnEntity(
			entityDataPos);
		//3.从map中移除
		entityId2DataPos_Map.erase(entityId);
		return true;
	}

}