#pragma once
#include <iostream>
#include <bitset>
#include <vector>

namespace paecs
{
    // Some typedefs to aid in reading
    typedef unsigned long long EntityID;
    const int MAX_COMPONENTS = 32;
    typedef std::bitset<MAX_COMPONENTS> ComponentMask;

    struct Scene
    {
        // All the information we need about each entity
        struct EntityDesc
        {
            EntityID id;
            ComponentMask mask;
        };
        std::vector<EntityDesc> entities;
    };
}
