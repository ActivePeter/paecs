#pragma once
#include "Entity.h"
namespace paecs
{
    template <typename CompType>
    EntityController &EntityController::addComponent(const CompType &compdata)
    {
        auto id = this->entityId;
        ComponentMask cm; //存储最终合并的componentMask
        //1，获取插件对应的mask    cm
        // ComponentMaskFuncs::getComponentMaskOfComps<CompType>(cm);
        ComponentMaskFuncs::ComponentMaskConstrctor<CompType>().getMask(cm);
        //2.如果entity之前有插件
        auto &chunkPtr = this->entityDataPos.chunkPtr;
        std::shared_ptr<Archtype> oldArchtypePtr = nullptr;

        if (chunkPtr != nullptr)
        {
            //   2.1.将之前的mask和cm合并
            //      之前的mask存在archtype中，
            ComponentMaskFuncs::combineMaskB2A(cm, chunkPtr->archtypePtr->componentMask);
            oldArchtypePtr = chunkPtr->archtypePtr;

            //   2.2.将之前的数据内容从archtype的chunk中拷贝出来，
            //       并在之前的archtype中删除
        }

        //3，通过cm调用findOrCreateArchtype
        auto am = this->entityManager.scene.archtypeManager;
        auto &targetArchtype = am->findOrCreateArchtype<CompType>(cm, oldArchtypePtr);
        // Archtype &targetArchtype = *archtypePtr; //am.createArchtypeWithComponentMask(cm);

        //4，调用registMemForAnEntity
        //   获取新的entity指向的entityDataPos
        //   此时修改了原来的entityDataPos
        auto oldEntityDataPos = this->entityDataPos; //在覆盖前拷贝
        targetArchtype.allocateMemForAnEntity(this->entityDataPos);

        auto comp = this->entityDataPos.chunkPtr->getCompDataPtrOfIndex<CompType>(this->entityDataPos.index);
        // memset(comp, 0, sizeof(CompType));
        memcpy(comp, &compdata, sizeof(CompType));
        //5，将map中指向的entityDataPos修改掉
        //    这个不用做了。因为当前EntityController里存的就是map里内容的引用

        //6.如果之前有数据，遍历之前的插件数据拷贝到现在的chunk中
        if (oldEntityDataPos.chunkPtr)
        {
            auto oldArchtype = oldEntityDataPos.chunkPtr->archtypePtr;
            for (const auto &oldComp : oldArchtype->compIds2InfoMap)
            {
                //从旧的chunk中读出
                this->entityDataPos.chunkPtr
                    ->cpyComponentDataFromOldDatapos2ChunkIndex_ifContainId(
                        oldEntityDataPos.getCompDataHeadPtr(
                            oldComp.second.compOffsetInOneChunk,            //之前的offset
                            oldComp.second.compDiscription->componentSize), //插件的信息引用中包含size
                        oldComp.first,                                      //插件id
                        this->entityDataPos.index                           //entity在chunk中的index
                    );
            }
            //6.then  完成之后移除原来的数据
            oldArchtype->deallocateMemForAnEntity(oldEntityDataPos);
        }
        return *this;
    }
}