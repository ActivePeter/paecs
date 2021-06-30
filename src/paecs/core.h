#pragma once

#include "_Config.h"
#include "iostream"
namespace paecs
{
    namespace log
    {
        inline void out(const char *info)
        {
            std::cout << "paecs\r\n  " << info << std::endl;
        }
    }

}