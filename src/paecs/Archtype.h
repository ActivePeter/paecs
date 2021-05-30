#pragma once

#include "Core.h"
#include <memory>
#include "ComponentMask.h"
#include "Scene.h"
#include "Component.h"
#include "Entity.h"
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
    class ArchtypeManager;
    //class Archtype;
    //使用std::vector<std::shared_ptr<Archtype>>管理
    class Archtype
    { //某一类set的所有信息
    private:
        // static std::shared_ptr<Archtype<CompTypes>> singleCase;
        ComponentMask componentMask;
        ArchtypeManager &archtypeManager;
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
            componentsIds = componentsIds1;
            componentsOffsets = componentsOffsets1;
            // for (int i = 0; i < componentsIds1.size(); i++)
            // {
            //     compIds2offsetsMap[componentsIds1[i]] = componentsOffsets1[i];
            // }
            maxCnt = maxCnt1;
            index = index1;
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

        // Archtype包含的components的id序列
        // phmap::flat_hash_map<BaseComponent::Id, int> compIds2offsetsMap;
        std::vector<BaseComponent::Id> componentsIds;
        //每个Components对应的Offset;
        //每个archtype中component内容都不一样所以offset是不一样的
        std::vector<int> componentsOffsets;
        int maxCnt;
        // int offset;
        // SetDescription<CompTypes> setDesc;
        // std::list<std::shared_ptr<Chunk>> chunks; //空list
        std::list<Chunk> chunks;
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

        /** 
         * @brief 通过插件id拷贝对应数据到vector中，轻量反射
         * @param id       插件id
         * @param index    entity在chunk中的位置
         * @param vec      用于拷贝数据的vector引用
         */
        // void readComponentDataById(BaseComponent::Id id, uint32_t index, std::vector<uint8_t> &vec)
        // {
        //     auto &compDiscription = BaseComponent::getDiscriptionOfComponentById(id);
        //     vec.resize(compDiscription.componentSize); //将vector大小变为插件大小
        //     auto begin = &storage[archtypePtr->compIds2offsetsMap[id] + index * compDiscription.componentSize];
        //     auto end = &storage[archtypePtr->compIds2offsetsMap[id] + (index + 1) * compDiscription.componentSize];
        //     vec.assign(begin, end);
        // }
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
