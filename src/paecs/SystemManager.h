#pragma once

#include "Core.h"

// #include "EntityManager.h"
#include "Scene.h"
namespace paecs
{
    class Scene;
    class SystemManager
    {

    public:
        SystemManager(Scene &scene1) : scene(scene1) {} // {}

    private:
        Scene &scene;
        /* data */
    };
}