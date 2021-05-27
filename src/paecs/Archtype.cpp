#include "Archtype.h"
#include "parallel_hashmap/phmap.h"

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
    Archtype &ArchtypeManager::findOrCreateArchtypeMatchMask(const ComponentMask &cm)
    {
        if (archtypes.contains(cm))
        {
            return *archtypes[cm];
        }
        else
        {
            auto newArchtype = std::make_shared<Archtype>(cm);
            archtypes[cm] = (newArchtype);
            return *newArchtype;
        }
        //计算chunk最大容量
        // auto maxCnt =config::ChunkSize/(constexpr (sizeof...(Comps));
    }
    std::vector<std::shared_ptr<Archtype>> 
    ArchtypeManager::findArchtypeContainingMask(const ComponentMask &cm){

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
