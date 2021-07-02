#pragma once

#include "Core.h"
#include "Scene.h"
#include "EntityManager.h"
// #include "ECManager.h"
#include "Archtype.h"
#include <parallel_hashmap/phmap_utils.h>

namespace paecs
{
	struct Chunk;
	class EntityManager;
	class EntityController;
	////////////////////////////////////////////

	//每个entity的唯一标识
	struct EntityID
	{
		bool operator==(const EntityID &o) const
		{
			return index == o.index && generation == o.generation;
		}
		friend size_t hash_value(const EntityID &p)
		{
			return phmap::HashState().combine(0, p.index, p.generation);
		}
		uint32_t index;
		uint32_t generation; //销毁后创建+1，用于区分
	};

	// namespace std
	// {
	// 	// inject specialization of std::hash for Person into namespace std
	// 	// ----------------------------------------------------------------
	// 	template <>
	// 	struct hash<EntityID>
	// 	{
	// 		std::size_t operator()(EntityID const &p) const
	// 		{
	// 			return phmap::HashState().combine(0, p.index, p.generation);
	// 		}
	// 	};
	// }
	//存储entity的区块指针以及在区块中的index
	struct EntityDataPos
	{
		// public:
		// Chunk &chunkRef;
		//使用指针的原因   entity为空插件时不指向任何的chunk
		std::shared_ptr<Chunk> chunkPtr;
		uint32_t index;

		EntityDataPos() {}
		EntityDataPos(
			std::shared_ptr<Chunk> chunkPtr1,
			// Chunk &chunkRef1,
			uint32_t index1)
			: chunkPtr(chunkPtr1),
			  //   chunkRef(chunkRef1),
			  index(index1){
				  // chunkPtr = std::shared_ptr<Chunk>(&chunkRef1);
			  };
		uint8_t *getCompDataHeadPtr(int compOffset, size_t compSize);
	};

	// template <typename CompType>
	// // EntityController &EntityController::addEmptyComponent()
	// EntityController &addComponent2Entity(EntityController &ec)
	// {
	// }

	// //////////////////////////////////////////////////////////////////////
	// template <typename CompType>
	// // EntityController &EntityController::addEmptyComponent()
	// EntityController &addEmptyComponent2Entity(EntityController &ec)
	// {
	// 	auto id = ec.entityId;
	// 	ComponentMask cm; //存储最终合并的componentMask
	// 	//1，获取插件对应的mask    cm
	// 	// ComponentMaskFuncs::getComponentMaskOfComps<CompType>(cm);
	// 	ComponentMaskFuncs::ComponentMaskConstrctor<CompType>().getMask(cm);
	// 	//2.如果entity之前有插件
	// 	auto &chunkPtr = ec.entityDataPos.chunkPtr;
	// 	std::shared_ptr<Archtype> oldArchtypePtr = nullptr;

	// 	if (chunkPtr != nullptr)
	// 	{
	// 		//   2.1.将之前的mask和cm合并
	// 		//      之前的mask存在archtype中，
	// 		ComponentMaskFuncs::combineMaskB2A(cm, chunkPtr->archtypePtr->componentMask);
	// 		oldArchtypePtr = chunkPtr->archtypePtr;

	// 		//   2.2.将之前的数据内容从archtype的chunk中拷贝出来，
	// 		//       并在之前的archtype中删除
	// 	}

	// 	//3，通过cm调用findOrCreateArchtype
	// 	auto am = ec.entityManager.scene.archtypeManager;
	// 	auto &targetArchtype = am->findOrCreateArchtype<CompType>(cm, oldArchtypePtr);
	// 	// Archtype &targetArchtype = *archtypePtr; //am.createArchtypeWithComponentMask(cm);

	// 	//4，调用registMemForAnEntity
	// 	//   获取新的entity指向的entityDataPos
	// 	//   此时修改了原来的entityDataPos
	// 	auto oldEntityDataPos = ec.entityDataPos; //在覆盖前拷贝
	// 	targetArchtype.allocateMemForAnEntity(ec.entityDataPos);

	// 	auto comp = ec.entityDataPos.chunkPtr->getCompDataPtrOfIndex<CompType>(ec.entityDataPos.index);
	// 	memset(comp, 0, sizeof(CompType));
	// 	//5，将map中指向的entityDataPos修改掉
	// 	//    这个不用做了。因为当前EntityController里存的就是map里内容的引用

	// 	//6.如果之前有数据，遍历之前的插件数据拷贝到现在的chunk中
	// 	if (oldEntityDataPos.chunkPtr)
	// 	{
	// 		auto oldArchtype = oldEntityDataPos.chunkPtr->archtypePtr;
	// 		for (const auto &oldComp : oldArchtype->compIds2InfoMap)
	// 		{
	// 			//从旧的chunk中读出
	// 			ec.entityDataPos.chunkPtr
	// 				->cpyComponentDataFromOldDatapos2ChunkIndex_ifContainId(
	// 					oldEntityDataPos.getCompDataHeadPtr(
	// 						oldComp.second.compOffsetInOneChunk,			//之前的offset
	// 						oldComp.second.compDiscription->componentSize), //插件的信息引用中包含size
	// 					oldComp.first,										//插件id
	// 					ec.entityDataPos.index								//entity在chunk中的index
	// 				);
	// 		}
	// 		//6.then  完成之后移除原来的数据
	// 		oldArchtype->deallocateMemForAnEntity(oldEntityDataPos);
	// 	}
	// 	return ec;
	// }

	template <typename CompType>
	// EntityController &EntityController::removeComponent()
	EntityController &removeEmptyComponentFromEntity(EntityController &ec)
	{
		/// <summary>
		/// 主要逻辑和addComponent是差不多的
		///
		/// </summary>
		/// <typeparam name="CompType"></typeparam>
		/// <returns></returns>
		auto id = ec.entityId;
		ComponentMask cm; //存储最终合并的componentMask
		//1，获取插件对应的mask    cm
		ComponentMaskFuncs::getComponentMaskOfComps<CompType>(cm);

		//2.如果entity之前有插件（有数据
		if (ec.entityDataPos.chunkPtr != nullptr)
		{
			//将原来的cm中移除当前插件cm
			bool subSucc = ComponentMaskFuncs::subtractMaskBFromAAndReturnInC(
				ec.entityDataPos.chunkPtr->archtypePtr->componentMask,
				cm,
				cm);
			if (!subSucc)
			{
				goto end;
			}
		}

		//3，通过cm调用findOrCreateArchtype
		auto &am = ec.entityManager.scene.archtypeManager;
		Archtype &targetArchtype = am.findOrCreateArchtype<CompType>(cm); //am.createArchtypeWithComponentMask(cm);

		//4，调用registMemForAnEntity
		//   获取新的entity指向的entityDataPos
		//   此时修改了原来的entityDataPos
		auto oldEntityDataPos = ec.entityDataPos; //在覆盖前拷贝

		//将新的数据位置存入entityDataPos引用
		targetArchtype.allocateMemForAnEntity(ec.entityDataPos);

		//5，将map中指向的entityDataPos修改掉
		//    这个不用做了。因为当前EntityController里存的就是map里内容的引用

		//6.如果之前有数据，遍历之前的插件数据拷贝到现在的chunk中
		if (oldEntityDataPos.chunkPtr != nullptr)
		{
			auto oldArchtype = oldEntityDataPos.chunkPtr->archtypePtr;
			for (const auto &oldComp : oldArchtype->compIds2InfoMap)
			{
				//从旧的chunk中读出
				ec.entityDataPos.chunkPtr
					->cpyComponentDataFromOldDatapos2ChunkIndex_ifContainId(
						&oldEntityDataPos.getCompDataHeadPtr(
							oldComp.second.compOffsetInOneChunk,		   //之前的offset
							oldComp.second.compDiscription.componentSize), //插件的信息引用中包含size
						oldComp.first,									   //插件id
						ec.entityDataPos.index							   //entity在chunk中的index
					);
			}
			//6.then  完成之后移除原来的数据
			oldArchtype->deallocateMemForAnEntity(oldEntityDataPos);
		}

	end:
		return ec;
	}
	//////////////////////////////////////////////////////////////////////
	class EntityController
	{
	private:
		/* data */
	public:
		// variable //////////////////////////////////
		EntityManager &entityManager;
		EntityID entityId;
		// std::shared_ptr<EntityDataPos> entityDataPos;
		EntityDataPos &entityDataPos;
		///////////////////////////////////
		EntityController(
			EntityManager &entityManager1,
			EntityID entityId1,
			// const std::shared_ptr<EntityDataPos> &entityDataPos1
			EntityDataPos &entityDataPos1) : entityManager(entityManager1),
											 entityId(entityId1),
											 entityDataPos(entityDataPos1)
		{
		}
		// template <typename CompType>
		// EntityController addComponent(CompType &comp);

		template <typename CompType>
		EntityController &addEmptyComponent()
		{
			// return addEmptyComponent2Entity<CompType>(*this);
			CompType comp;
			memset(&comp, 0, sizeof(CompType));
			return addComponent(comp);
		}

		template <typename CompType>
		EntityController &addComponent(const CompType &compdata);

		template <typename CompType>
		EntityController &removeComponent()
		{
			return removeEmptyComponentFromEntity<CompType>(*this);
		}
	};
}
#include "Entity.temp.h"