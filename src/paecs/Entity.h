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
	class EntityController
	{
	private:
		EntityManager &entityManager;
		EntityID entityId;
		// std::shared_ptr<EntityDataPos> entityDataPos;
		EntityDataPos &entityDataPos;
		/* data */
	public:
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
		EntityController &addEmptyComponent();

		template <typename CompType>
		EntityController &removeComponent();
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