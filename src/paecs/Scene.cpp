
#include "Core.h"
#include "Scene.h"

namespace paecs
{
    Scene::Scene(/* args */)
    {
        entityManager = std::make_unique<EntityManager>(*this);
        systemManager = std::make_unique<SystemManager>(*this);
        // eventManager = std::make_unique<EventManager>(*this);
    }
}