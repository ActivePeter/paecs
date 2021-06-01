#pragma once

#include "Core.h"
#include <memory>
#include "ComponentMask.h"
#include "Scene.h"
#include "Component.h"
#include "Entity.h"
#include "ArchtypeManager.h"
#include "parallel_hashmap/phmap.h"
#include "Archtype.h"

namespace paecs
{
	struct CompInfoInArchtype
	{
		//archtype中某个插件在chunk中的offset
		int compOffsetInOneChunk;
		//archtype中某个插件的描述信息引用
		ComponentDiscription &compDiscription;
		// size_t compSize;
		CompInfoInArchtype(int offset, ComponentDiscription &disc) : compOffsetInOneChunk(offset),
																	 compDiscription(disc) {}
	};
	class ArchtypeManager;
	struct Chunk;
	//class Archtype;
	//使用std::vector<std::shared_ptr<Archtype>>管理
	class Archtype : public std::enable_shared_from_this<Archtype>
	{ //某一类set的所有信息
	private:
		// static std::shared_ptr<Archtype<CompTypes>> singleCase;
		ComponentMask componentMask;
		ArchtypeManager &archtypeManager;
		// vector Component/
		int index;

	public:
		Archtype(ArchtypeManager &archtypeManager1, int index1,
				 const ComponentMask &componentMask1,
				 std::vector<BaseComponent::Id> componentsIds1,
				 std::vector<int> componentsOffsets1,
				 int maxCnt1)
			: archtypeManager(archtypeManager1)
		{
			componentMask = componentMask1;
			// componentsIds = componentsIds1;
			// componentsOffsets = componentsOffsets1;
			for (int i = 0; i < componentsIds1.size(); i++)
			{
				auto compInfo = CompInfoInArchtype(componentsOffsets1[i], BaseComponent::getDiscriptionOfComponentById(componentsIds1[i]));
				compIds2InfoMap[componentsIds1[i]] = compInfo;
				// compIds2offsetsMap[componentsIds1[i]] = componentsOffsets1[i];
			}
			maxCnt = maxCnt1;
			index = index1;
			// maxCnt =config::ChunkSize/(constexpr (sizeof...(Comps));
		}

		//用于通过插件id直接查找插件信息，也可用于遍历插件信息
		phmap::flat_hash_map<BaseComponent::Id, CompInfoInArchtype> compIds2InfoMap;

		template <typename Comp>
		CompInfoInArchtype &getCompInfo()
		{
			return compIds2InfoMap[Component<Comp>().getId];
		}
		// std::vector<BaseComponent::Id> componentsIds;
		//每个Components对应的Offset;
		//每个archtype中component内容都不一样所以offset是不一样的

		//描述单个chunk的最大Entity容量
		int maxCnt;

		//chunks要用智能指针，因为在别处使用时，需要拿chunks的智能指针
		//存储所有有数据的chunks，以备遍历 (空list
		std::list<std::shared_ptr<Chunk>> chunks;

		//存储删除entity数据后，又没满了的chunk，以备后续再次利用
		std::list<std::shared_ptr<Chunk>> back2NotFullChunks;

		// std::list<Chunk> chunks;
		//在创建entity时调用
		// void registMemForAnEntity(EntityDataPos &entityDataPos);
		void allocateMemForAnEntity(EntityDataPos &entityDataPos);
		void deallocateMemForAnEntity(EntityDataPos &entityDataPos);
	};

	// Archtype a;
	// void f(){
	//     a.chunks.push_front()
	// }

	//chunk应该还要存一个指向archtype的指针
	struct Chunk
	{ //chunk的数据结构
		uint32_t entityCnt;
		std::shared_ptr<Archtype> archtypePtr;
		uint8_t storage[config::ChunkSize];

		//构造
		Chunk(std::shared_ptr<Archtype> archtype)
		{
			entityCnt = 0;
			archtypePtr = archtype;
		}
		/**
		 * @brief 通过插件id拷贝对应数据到vector中，轻量反射
		 *
		 * @param oldDataPos       原来的数据在chunk storage中的指针
		 * @param id       插件id，需要这个id来获取在当前chunk中应该用的size和offset
		 * @param index    entity在chunk中的位置
		 */
		void cpyComponentDataFromOldDatapos2ChunkIndex_ifContainId(uint8_t *oldDataPos, BaseComponent::Id id, uint32_t index)
		{
			if (archtypePtr->compIds2InfoMap.contains(id))
			{
				// auto size = BaseComponent::getDiscriptionOfComponentById(id).componentSize;
				auto &compInfo = archtypePtr->compIds2InfoMap[id];
				auto &size = compInfo.compDiscription.componentSize;
				auto &offset = compInfo.compOffsetInOneChunk;
				// auto offset = .compOffsetInOneChunk;
				// auto size=
				memcpy(&storage[offset + index * size], oldDataPos, size);
				// storage[offset+]
			}
		}
		template <typename Comp>
		Comp &getCompDataOfIndex(int index)
		{
			CompInfoInArchtype &info = this->archtypePtr->getCompInfo<Comp>();

			return (Comp &)*(&(storage[info.compOffsetInOneChunk + info.compDiscription.componentSize * index]));
		}
	};

	// template <typename... CompTypes>
	// struct SetDescription
	// { //set的描述
	//     int maxCnt;
	//     static offset;
	// };

	// Archetype *find_or_create_archetype(ECSWorld *world, const Metatype **types, size_t count)
	// {
	//     const Metatype *temporalMetatypeArray[32];
	//     assert(count < 32);

	//     const Metatype **typelist;

	//     if (false)
	//     { //!is_sorted(types, count)) {
	//         for (int i = 0; i < count; i++)
	//         {
	//             temporalMetatypeArray[i] = types[i];
	//         }
	//         sort_metatypes(temporalMetatypeArray, count);
	//         typelist = temporalMetatypeArray;
	//     }
	//     else
	//     {
	//         typelist = types;
	//     }

	//     const uint64_t matcher = build_signature(typelist, count);

	//     //try in the hashmap
	//     auto iter = world->archetype_signature_map.find(matcher);
	//     if (iter != world->archetype_signature_map.end())
	//     {

	//         auto &archvec = iter->second; //world->archetype_signature_map[matcher];
	//         for (int i = 0; i < archvec.size(); i++)
	//         {

	//             auto componentList = archvec[i]->componentList;
	//             int ccount = componentList->components.size();
	//             if (ccount == count)
	//             {
	//                 for (int j = 0; j < ccount; j++)
	//                 {

	//                     if (componentList->components[j].type != typelist[j])
	//                     {
	//                         //mismatch, inmediately continue
	//                         goto contA;
	//                     }
	//                 }

	//                 //everything matched. Found. Return inmediately
	//                 return archvec[i];
	//             }

	//         contA:;
	//         }
	//     }

	//     //not found, create a new one

	//     Archetype *newArch = new Archetype();

	//     newArch->full_chunks = 0;
	//     newArch->componentList = build_component_list(typelist, count);
	//     newArch->componentHash = matcher;
	//     newArch->ownerWorld = world;
	//     world->archetypes.push_back(newArch);
	//     world->archetypeSignatures.push_back(matcher);
	//     world->archetype_signature_map[matcher].push_back(newArch);

	//     //we want archs to allways have 1 chunk at least, create initial
	//     create_chunk_for_archetype(newArch);
	//     return newArch;
	// }
} // namespace paecs
