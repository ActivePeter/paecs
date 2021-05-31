#include "Archtype.h"
#include "parallel_hashmap/phmap.h"
#include "Entity.h"

namespace paecs
{

	// template <typename... CompTypes>
	void Archtype::allocateMemForAnEntity(EntityDataPos& entityDataPos)
	{
		if (back2NotFullChunks.size() > 0)
		{
			back2NotFullChunks.back()->entityCnt++;
			entityDataPos.chunkPtr = chunks.back();
			entityDataPos.index = chunks.back()->entityCnt - 1;
			//如果未满的chunk list被装满了，就从list中移除
			if (back2NotFullChunks.back()->entityCnt == maxCnt)
			{
				back2NotFullChunks.pop_back();
			}
		}
		else
		{
			if (chunks.empty() || chunks.back()->entityCnt == maxCnt)
			{
				// }else{
				// }
				// if (chunks.back().entityCnt == maxCnt)
				// {
				// chunks.resize(chunks.size() + 1);
				chunks.push_back(std::make_shared<Chunk>(shared_from_this()));
			}
			chunks.back()->entityCnt++;
			//此处会增加一次对chunk智能指针的引用
			entityDataPos.chunkPtr = chunks.back();
			entityDataPos.index = chunks.back()->entityCnt - 1;
		}
	}

	//在池中取消entity数据的注册
	void Archtype::deallocateMemForAnEntity(EntityDataPos& entityDataPos)
	{
		std::shared_ptr<Chunk> chunkPtr = entityDataPos.chunkPtr;
		if (entityDataPos.index < chunkPtr->entityCnt - 1)
		{
			for (const auto& comp : this->compIds2InfoMap)
			{
				auto& compInfo = comp.second;
				auto& offset = compInfo.compOffsetInOneChunk;
				auto& size = compInfo.compDiscription.componentSize;

				//如果数据不是最后一个(即 index小于总数减1)
				//if (entityDataPos.index < chunkPtr->entityCnt - 1)
			   // {
				memcpy(&chunkPtr->storage[offset + size * entityDataPos.index],       //当前数据开头
					&chunkPtr->storage[offset + size * (entityDataPos.index + 1)], //当前数据下一个数据的开头
					size * (chunkPtr->entityCnt - entityDataPos.index - 1)         //当前数据后面的所有有效数据大小
				);
				// }
			}
		}
		//如果这个chunk本来已经满了。那么添加到未装满列表，后续添加优先遍历这个列表
		if (chunkPtr->entityCnt == maxCnt)
		{
			back2NotFullChunks.push_back(chunkPtr);
		}
		//全部拷贝完后。将长度减小
		chunkPtr->entityCnt--;
	}

}
