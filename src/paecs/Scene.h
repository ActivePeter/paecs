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
        std::unique_ptr<ECManager> ecManager = nullptr;
        std::unique_ptr<SManager> sManager = nullptr;
        /* data */
    public:
        Scene(/* args */);
        ECManager &getEntityManager() const;
        SManager &getSystemManager() const;
        // EventManager &getEventManager() const;

        // std::unique_ptr<EventManager> eventManager = nullptr;
        // ~Scene();
    };

}