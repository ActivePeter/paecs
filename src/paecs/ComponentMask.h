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
		bool MaskAContainsMaskB(const ComponentMask &maskA, const ComponentMask &maskB)
		{
			auto maskASize = maskA.size();
			if (maskASize != maskB.size())
			{
				return false;
			}
			else
			{
				// bool result=true;
				for (int i = 0; i < maskASize; i++)
				{
					auto &cellA = maskA[i];
					auto &cellB = maskB[i];

					if ((cellA & cellB) != cellB) //。。。。与操作要括起来
					{
						return false;
					}
				}
				return true;
			}
			// for(int i=ComponentMask;i<1)
		}
		void getEmptyMask(ComponentMask &cm);

		//传入引用。这样修改的永远是maskA，减少内存的复制
		template <typename CompTypeFirst, typename... CompTypesAfter>
		void getComponentMaskOfComps(ComponentMask &maskA)
		{
			//获取的是引用，因为combine函数不改变参数二
			auto &maskB = Component<CompTypeFirst>::getMask();
			getComponentMaskOfComps<CompTypesAfter...>(maskA);
			//迭代到最底下的beforeMask时一个复制值，前面的Mask都是
			combineMasks(maskA, maskB);
			// return maskA;
		}
		template <typename CompType>
		void getComponentMaskOfComps(ComponentMask &maskA)
		{
			//返回的时引用，但是并不会被操作
			maskA = Component<CompType>::getMask();
		}
		// template <typename CompType>
		// ComponentMask getComponentMaskOfComps()
		// {
		//     return Component<CompType>::getId() / ;
		// }

		//从MaskB中减掉A，并返回是否减成功(如果不包含就减不成功
		bool subtractMaskBFromAAndReturnInC(const ComponentMask &maskA, const ComponentMask &maskB, ComponentMask &maskC)
		{
			if (MaskAContainsMaskB(maskA, maskB))
			{
				//使用异或运算 相同则结果为0，不同则结果为1
				//如 011110
				//   001100
				//-> 010010  //前提是A包含B
				for (int i = 0; i < maskA.size(); i++)
				{
					maskC[i] = maskA[i] ^ maskB[i];
				}

				return true;
			}

			return false;
		}

		void combineMaskB2A(ComponentMask &maskA, const ComponentMask &maskB)
		{

			for (int i = 0; i < maskA.size(); i++)
			{
				maskA[i] = maskA[i] | maskB[i];
			}
			// return maskA;
		}
		// ComponentMask expandMask(ComponentMask cm,uint8_t bitsetCnt){
		//     cm.resize()
		// }
	}
}
