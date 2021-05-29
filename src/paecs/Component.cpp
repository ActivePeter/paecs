#include "Component.h"
#include "parallel_hashmap/phmap.h"

namespace paecs
{
    /*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */
    BaseComponent::Id BaseComponent::nextId = 0;
    uint8_t BaseComponent::maskVecSize = 1;

    template <typename T>
    static Component<T>::ComponentMask cm;

    static phmap::flat_hash_map<BaseComponent::Id, ComponentDiscription> componentId2DiscriptionMap;
}
