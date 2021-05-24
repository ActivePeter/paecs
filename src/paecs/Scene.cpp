
#include "Core.h"
#include "Scene.h"
#include "memory"

namespace paecs
{
    Scene::Scene(/* args */)
    {
        ecManager = std::make_unique<ECManager>(*this);
        sManager = std::make_unique<SManager>(*this);
        // eventManager = std::make_unique<EventManager>(*this);
    }
}