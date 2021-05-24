#pragma once

#include "Core.h"

#include "ECManager.h"
#include "SManager.h"

#include <memory>

namespace paecs
{
    class ECManager;
    class Scene
    {
    private:
        /* data */
    public:
        Scene(/* args */);
        std::unique_ptr<ECManager> ecManager = nullptr;
        std::unique_ptr<SManager> sManager = nullptr;
        // std::unique_ptr<EventManager> eventManager = nullptr;
        // ~Scene();
    };

}