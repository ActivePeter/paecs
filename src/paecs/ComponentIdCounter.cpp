#include "ComponentIdCounter.h"

namespace paecs
{
    /*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */
    BaseComponentIdCounter::Id BaseComponentIdCounter::nextId = 0;
    uint8_t BaseComponentIdCounter::bitsetCnt = 1;

    template <typename T>
    static ComponentIdCounter<T>::ComponentMask cm;
}
