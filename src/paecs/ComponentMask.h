#pragma once

#include "vector"
#include "bitset"

#include "Core.h"
#include "Component.h"
// Used to keep track of which components an entity has and also which entities a system is interested in.

namespace paecs
{
	class BaseComponent;
	// using ComponentMaskCell = std::bitset<config::MAX_COMPONENTS>;
	// using ComponentMask = std::vector<ComponentMaskCell>; //<total size>
	// using ComponentMask = std::vector<std::bitset<config::MAX_COMPONENTS>>; //<total size>
	using ComponentMask = std::vector<uint64_t>; //暂时没感觉到用bitset的优点，所以就先不用了
	// const uint32_t ComponentMaskCellSize = config::MAX_COMPONENTS;
	//对componentMask的操作有：改变长度，与操作
	namespace ComponentMaskFuncs
	{
		void getEmptyMask(ComponentMask &cm);

		bool MaskAContainsMaskB(const ComponentMask &maskA, const ComponentMask &maskB);

		//传入引用。这样修改的永远是maskA，减少内存的复制
		// template <typename CompTypeFirst, typename... CompTypesAfter>
		// void getComponentMaskOfComps(ComponentMask &maskA);

		// template <typename CompType>
		// void getComponentMaskOfComps(ComponentMask &maskA);
		// template <typename CompType>
		// ComponentMask getComponentMaskOfComps()
		// {
		//     return Component<CompType>::getId() / ;
		// }

		//从MaskB中减掉A，并返回是否减成功(如果不包含就减不成功
		bool subtractMaskBFromAAndReturnInC(const ComponentMask &maskA, const ComponentMask &maskB, ComponentMask &maskC);
		void combineMaskB2A(ComponentMask &maskA, const ComponentMask &maskB);
		// ComponentMask expandMask(ComponentMask cm,uint8_t bitsetCnt){
		//     cm.resize()
		// }

		//template funcs
		// template <typename CompTypeFirst, typename... CompTypesAfter>
		// void getComponentMaskOfComps(ComponentMask &maskA);

		template <typename... CompTypes>
		struct ComponentMaskConstrctor
		{
		};

		//偏特化
		template <typename CompTypeFirst, typename... CompTypesAfter>
		struct ComponentMaskConstrctor<CompTypeFirst, CompTypesAfter...>
		{
			void getMask(ComponentMask &maskA)
			{
				ComponentMaskConstrctor<CompTypeFirst>().getMask(maskA);
				ComponentMaskConstrctor<CompTypesAfter...>().getMask(maskA);
			}
		};

		//递归结束
		template <typename CompTypeEnd>
		struct ComponentMaskConstrctor<CompTypeEnd>
		{
			void getMask(ComponentMask &maskA)
			{
				maskA = Component<CompTypeEnd>::getMask();
			}
		};

		// template <typename CompTypeFirst, typename... CompTypesAfter>
		// void getComponentMaskOfComps(ComponentMask &maskA)
		// {
		// 	//获取的是引用，因为combine函数不改变参数二
		// 	auto &maskB = Component<CompTypeFirst>::getMask();
		// 	getComponentMaskOfComps<CompTypesAfter...>(maskA);
		// 	//迭代到最底下的beforeMask时一个复制值，前面的Mask都是
		// 	combineMasks(maskA, maskB);
		// 	// return maskA;
		// }
		// template <typename CompType>
		// void getComponentMaskOfComps(ComponentMask &maskA)
		// {
		// 	//返回的时引用，但是并不会被操作
		// 	maskA = Component<CompType>::getMask();
		// }
		// template <typename CompType>
		// void getComponentMaskOfComps(ComponentMask &maskA)
		// {
		// 	//返回的时引用，但是并不会被操作
		// 	maskA = Component<CompType>::getMask();
		// }
	}
}
