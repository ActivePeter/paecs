
#include "Core.h"

#include "EntityManager.h"
#include "Entity.h"

namespace paecs
{
    Entity EntityManager::createEntity()
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
        // e.entityManager = this;

        return e;
    }
}

//     EntityManager::EntityManager(Scene &scene1)
//     {
//         // this->scene = scene1;
//         // scene(scene1);
//     }

// }
