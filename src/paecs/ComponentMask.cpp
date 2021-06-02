#include "ComponentMask.h"

namespace paecs
{
    namespace ComponentMaskFuncs
    {
        void getEmptyMask(ComponentMask &cm)
        {
            cm.resize(BaseComponent::maskVecSize);
        }
    }
}