#pragma once
#include "iostream"

namespace paecs
{
    namespace config
    {
        static const uint32_t INDEX_BITS = 24;
        static const uint32_t MINIMUM_FREE_IDS = 1024;
        static const uint32_t VERSION_BITS = 8;
        // static const uint32_t MAX_COMPONENTS = 64;
        static const uint32_t DEFAULT_POOL_SIZE = 100;
        static const uint32_t ChunkSize = 16 * 1024; //16K
    }
}
