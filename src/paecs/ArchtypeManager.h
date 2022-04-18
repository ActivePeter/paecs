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
		Archtype& findOrCreateArchtype(const ComponentMask& cm, std::shared_ptr<Archtype> oldArchtype)
		{
			//find 是根据mask来找，但是创建需要更完整的信息
			//int foundIndex = -1;
			for (size_t i = 0; i < archtypeComponentMasks.size(); i++)
			{
				if (archtypeComponentMasks[i] == cm)
				{
					//foundIndex = i;
					return *archtypes[i];
					// break;
				}
			}
			//if (foundIndex == -1)
			{
				//没有找到，创建archtype

				////////////////////////////////////////
				// 必要数据准备
				//先获取插件的id
				std::vector<BaseComponent::Id> ids; //对应要新加的组件的id们
				std::vector<size_t> sizeOfComps;
				size_t sizeSum = 0;
				std::vector<int> offsets;
				if (oldArchtype != nullptr)
				{
					for (const auto& compInfo : oldArchtype->compIds2InfoMap)
					{
						ids.push_back(compInfo.first);
						sizeOfComps.push_back(compInfo.second.compDiscription->componentSize);
						sizeSum += compInfo.second.compDiscription->componentSize;
					}
				}
				ids.push_back(Component<NewComp>::getId());
				sizeOfComps.push_back(sizeof(NewComp));
				sizeSum += sizeof(NewComp);
				// ComponentIdFuncs::getIdsOfComponents<NewComp>(ids);
				// auto componentsCnt = ids.size();
				// std::vector<int> offsets(componentsCnt);

				//maxCnt 是可容纳entity的最大数量  区块size/(旧插件size+新插件size)
				int maxCnt = config::ChunkSize / sizeSum;
				offsets.resize(ids.size());
				//第一个offset就是0
				for (size_t i = 1; i < ids.size(); i++)
				{
					offsets[i] = offsets[i - 1] + sizeOfComps[i - 1] * maxCnt;
					// (BaseComponent::getDiscriptionOfComponentById(ids[i - 1])
					//                   .componentSize) *
					//              maxCnt;
				}
				//添加顺序跟masks的顺序保持一致

				///////////////////////////////////////////////////
				// 创建 archtype
				size_t newSize = archtypeComponentMasks.size() + 1;
				archtypeComponentMasks.resize(newSize);
				archtypeComponentMasks[newSize - 1] = cm;
				archtypes.resize(newSize);
				archtypes[newSize - 1] = std::make_shared<Archtype>(*this, newSize - 1, cm, ids, offsets, maxCnt); //createArchtypeWithComponentMask(cm);
				// archtypes[newSize-1]->
				// archtypes[newSize]->maxCnt=config::ChunkSize/(constexpr (sizeof...(Comps));
				return *archtypes[newSize - 1];
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
		std::vector<std::shared_ptr<Archtype>> findArchtypeContainingMask(const ComponentMask& cm);
		// std::vector<Archtype> findArchtypeContainingMask(const ComponentMask &cm);
		ArchtypeManager(Scene& scene1) : scene(scene1) {}

	private:
		Scene& scene;
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
