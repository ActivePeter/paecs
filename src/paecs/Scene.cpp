
#include "Core.h"
#include "Scene.h"
#include "memory"

namespace paecs
{
    Scene::Scene(/* args */)
    {
        ECManager = std::make_unique<ECManager>(*this);
        SManager = std::make_unique<SManager>(*this);
        // eventManager = std::make_unique<EventManager>(*this);
    }
}