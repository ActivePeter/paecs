//#include "Archtype.h"
#include "parallel_hashmap/phmap.h"
#include "ArchtypeManager.h"

namespace paecs
{
    // 参考 decs
    // static const Metatype* types[] = { adv::get_metatype<Comps>()... };
    // template<typename T>
    // 		static const Metatype* get_metatype() {
    // 			static const Metatype* mt = []() {
    // 				constexpr size_t name_hash = Metatype::build_hash<T>().name_hash;

    // 				auto type = metatype_cache.find(name_hash);
    // 				if (type == metatype_cache.end()) {
    // 					constexpr Metatype newtype = Metatype::build<T>();
    // 					metatype_cache[name_hash] = newtype;
    // 				}
    // 				return &metatype_cache[name_hash];
    // 			}();
    // 			return mt;
    // 		}

    // template <typename... CompTypes>
    //void Archtype::registMemForAnEntity(EntityDataPos& entityDataPos)
    //{
    //    if (chunks.empty() || chunks.back().entityCnt == maxCnt)
    //    {
    //        // }else{
    //        // }
    //        // if (chunks.back().entityCnt == maxCnt)
    //        // {
    //        chunks.resize(chunks.size() + 1);
    //    }
    //    chunks.back().entityCnt++;
    //    entityDataPos.chunkPtr = std::shared_ptr<Chunk>(&chunks.back());
    //    entityDataPos.index = chunks.back().entityCnt - 1;
    //    // entityDataPos.
    //    // return EntityDataPos(chunks.back(), chunks.back().entityCnt - 1);
    //    // auto componentCnt = componentsIds.size();
    //    // for (int i = 0; i < componentCnt; i++)
    //    // {
    //    // }
    //}

    //
    //生成entity时需要做的操作
    template <typename NewComp>
    Archtype &ArchtypeManager::findOrCreateArchtype(const ComponentMask &cm)
    {
        //find 是根据mask来找，但是创建需要更完整的信息
        int foundIndex = -1;
        for (int i = 0; i < archtypeComponentMasks.size(); i++)
        {
            if (archtypeComponentMasks[i] == cm)
            {
                foundIndex = i;
                return *archtypes[i];
                // break;
            }
        }
        if (foundIndex == -1)
        {
            //没有找到，创建archtype
            size_t newSize = archtypeComponentMasks.size() + 1;
            archtypeComponentMasks.resize(newSize);
            archtypeComponentMasks[newSize - 1] = cm;
            archtypes.resize(newSize);

            std::vector<BaseComponent::Id> ids; //对应要新加的组件的id们
            ComponentIdFuncs::getIdsOfComponents<NewComp>(ids);
            auto componentsCnt = ids.size();
            std::vector<int> offsets(componentsCnt);
            int maxCnt = config::ChunkSize / (constexpr(sizeof...(Comps)));
            //第一个offset就是0
            for (int i = 1; i < componentsCnt; i++)
            {
                offsets[i] = (BaseComponent::getDiscriptionOfComponentById(ids[i - 1])
                                  .componentSize) *
                             maxCnt;
            }
            //添加顺序跟masks的顺序保持一致
            archtypes[newSize - 1] = std::make_shared<Archtype>(*this, newSize - 1, cm, ids, offsets, maxCnt); //createArchtypeWithComponentMask(cm);
            // archtypes[newSize-1]->
            // archtypes[newSize]->maxCnt=config::ChunkSize/(constexpr (sizeof...(Comps));
            return *archtypes[newSize];
        }
        // else
        // {
        //     //找到了Archtype

        // }
        // if (archtypeComponentMasks.)
        // if (archtypes.contains(cm))
        // {
        //     return *archtypes[cm];
        // }
        // else
        // {
        //     auto newArchtype = std::make_shared<Archtype>(cm);
        //     archtypes[cm] = (newArchtype);
        //     return *newArchtype;
        // }
        //计算chunk最大容量
        // auto maxCnt =config::ChunkSize/(constexpr (sizeof...(Comps));
    }

    //在遍历的时候用
    std::vector<std::shared_ptr<Archtype>>
    // std::vector<Archtype>
    ArchtypeManager::findArchtypeContainingMask(const ComponentMask &cm)
    {
        std::vector<std::shared_ptr<Archtype>> foundedList;
        auto archtypeCnt = archtypeComponentMasks.size();
        for (int i = 0; i < archtypeCnt; i++)
        {
            if (ComponentMaskFuncs::MaskAContainsMaskB(archtypeComponentMasks[i], cm))
            {
                foundedList.push_back(archtypes[i]);
            }
        }
        return foundedList;
    }
    /**
    * 在decs中
    * 通过vector来存储archtype的标识（用于查找匹配
    * 通过另一个vector来存储archtype的指针（与前者下标对应，
    *
    * 我准备直接使用map存储标识<key>（ComponentMask 以及指针<item>
    *
    **/
    // inline Archetype* find_or_create_archetype(ECSWorld* world, const Metatype** types, size_t count) {
    // 		const Metatype* temporalMetatypeArray[32];
    // 		assert(count < 32);

    // 		const Metatype** typelist;

    // 		if (false) {//!is_sorted(types, count)) {
    // 			for (int i = 0; i < count; i++) {
    // 				temporalMetatypeArray[i] = types[i];

    // 			}
    // 			sort_metatypes(temporalMetatypeArray, count);
    // 			typelist = temporalMetatypeArray;
    // 		}
    // 		else {
    // 			typelist = types;
    // 		}

    // 		const uint64_t matcher = build_signature(typelist, count);

    // 		//try in the hashmap
    // 		auto iter = world->archetype_signature_map.find(matcher);
    // 		if (iter != world->archetype_signature_map.end()) {

    // 			auto& archvec = iter->second;//world->archetype_signature_map[matcher];
    // 			for (int i = 0; i < archvec.size(); i++) {

    // 				auto componentList = archvec[i]->componentList;
    // 				int ccount = componentList->components.size();
    // 				if (ccount == count) {
    // 					for (int j = 0; j < ccount; j++) {

    // 						if (componentList->components[j].type != typelist[j])
    // 						{
    // 							//mismatch, inmediately continue
    // 							goto contA;
    // 						}
    // 					}

    // 					//everything matched. Found. Return inmediately
    // 					return archvec[i];
    // 				}

    // 			contA:;
    // 			}
    // 		}

    // 		//not found, create a new one

    // 		Archetype* newArch = new Archetype();

    // 		newArch->full_chunks = 0;
    // 		newArch->componentList = build_component_list(typelist, count);
    // 		newArch->componentHash = matcher;
    // 		newArch->ownerWorld = world;
    // 		world->archetypes.push_back(newArch);
    // 		world->archetypeSignatures.push_back(matcher);
    // 		world->archetype_signature_map[matcher].push_back(newArch);

    // 		//we want archs to allways have 1 chunk at least, create initial
    // 		create_chunk_for_archetype(newArch);
    // 		return newArch;
    // 	}
}
