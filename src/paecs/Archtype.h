#pragma once
#include "Core.h"
#include <memory>
#include "ComponentMask.h"
#include "Scene.h"

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
    class Archtype
    { //某一类set的所有信息
    private:
        // static std::shared_ptr<Archtype<CompTypes>> singleCase;
        ComponentMask componentMask;

    public:
        Archtype(const ComponentMask &componentMask1)
        {
            componentMask = componentMask1;
            // maxCnt =config::ChunkSize/(constexpr (sizeof...(Comps));
        }
        // static std::shared_ptr<Archtype<CompTypes>> getSingleCase()
        // {
        //     if (singleCase == nullptr)
        //     {
        //         std::make_shared<Archtype<CompTypes>>();
        //     }
        //     return singleCase;
        // }

        int maxCnt;
        int offset;
        // SetDescription<CompTypes> setDesc;
        std::list<Chunk> chunks; //空list
    };
    struct Chunk
    { //chunk的数据结构
        uint8_t storage[config::ChunkSize];
    };

    class ArchtypeManager
    {
    public:
        // template <typename... CompTypes>
        Archtype &findOrCreateArchtypeMatchMask(const ComponentMask &cm);
        std::vector<std::shared_ptr<Archtype>> findArchtypeContainingMask(const ComponentMask &cm);

        ArchtypeManager(Scene &scene1) : scene(scene1)
        {
        }

    private:
        Scene &scene;
        // phmap::flat_hash_map<ComponentMask, std::shared_ptr<Archtype>> archtypes;
        vector<ComponentMask> archtypeComponentMasks;
        vector<std::shared_ptr<Archtype>> archtypes;
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
