
#include "Core.h"

#include "ECManager.h"
#include "Entity.h"

namespace paecs
{
    Entity ECManager::createEntity()
    {
        Entity::Id index;

        if (freeIds.size() > config::MINIMUM_FREE_IDS) //可用id数量大于最小值
        {
            index = freeIds.front(); //从可用id中取出id
            freeIds.pop_front();     //去除已用
        }
        else //无可用id了
        {
            versions.push_back(0);                     //vesions增加一个0（暂时不知道version的含义
            index = (unsigned int)versions.size() - 1; //index 根据versions算出
            // assert(index < (1 << Entity::IndexBits));

            // if (index >= componentMasks.size()) //componentMask也暂时不知道什么意思
            // {
            //     // TODO: grow by doubling?
            //     componentMasks.resize(index + 1);
            // }
        }

        // assert(index < versions.size());
        Entity e(*this, index, versions[index]); //一个entity参数有index version 和this
        // e.ECManager = this;

        return e;
    }

    template <typename T>
    std::shared_ptr<ComponentPool<T>> ECManager::getComponentPoolOfT()
    {

        const auto componentId = Component<T>::getId();

        if (componentId >= componentPoolVec.size()) //若存储pool的vector不够，扩大存储pool的vector
        {
            componentPoolVec.resize(componentId + 1, nullptr);
        }

        if (!componentPoolVec[componentId]) //若不存在该component类型的pool 则新建
        {
            std::shared_ptr<ComponentPool<T>> newpool(new ComponentPool<T>());
            componentPoolVec[componentId] = newpool;
        }
        //通过对应id获取对应类型的抽象pool指针并转换为具体pool指针，并返回
        return std::static_pointer_cast<Pool<T>>(componentPoolVec[componentId]);
    }

    const ComponentMask &ECManager::getComponentMaskOfEntity(Entity &e) const
    {
        const auto index = e.getIndex();
        assert(index < componentMasks.size());
        return componentMasks[index];
    }
}

//     ECManager::ECManager(Scene &scene1)
//     {
//         // this->scene = scene1;
//         // scene(scene1);
//     }

// }
