#pragma once

#include "Archtype.h"
#include "Scene.h"
#include "ArchtypeManager.h"

namespace paecs
{
    class Archtype;
    class Scene;
    class ArchtypeManager
    {
    public:
        template <typename NewComp>
        Archtype &findOrCreateArchtype(const ComponentMask &cm);
        std::vector<std::shared_ptr<Archtype>> findArchtypeContainingMask(const ComponentMask &cm);
        // std::vector<Archtype> findArchtypeContainingMask(const ComponentMask &cm);
        ArchtypeManager(Scene &scene1) : scene(scene1)
        {
        }

    private:
        Scene &scene;
        // phmap::flat_hash_map<ComponentMask, std::shared_ptr<Archtype>> archtypes;
        std::vector<ComponentMask> archtypeComponentMasks;

        //使用指针的原因是之后 获取一组archtype 可以直接创建同类型的vector
        //如果用的是直接数据，那读取出来还要取指针装入一个新的vector
        std::vector<std::shared_ptr<Archtype>> archtypes;
        // std::vector<Archtype> archtypes;

        // inline std::shared_ptr<Archtype> createArchtypeWithComponentMask(const ComponentMask &cm)
        // {
        //     return std::make_shared<Archtype>(cm);
        // }
    };
}
