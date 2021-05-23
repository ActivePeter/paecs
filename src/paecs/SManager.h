#pragma once

#include "Core.h"

// #include "EntityManager.h"
#include "Scene.h"
namespace paecs
{
    class Scene;
    class SManager
    {

    public:
        SManager(Scene &scene1) : scene(scene1) {} // {}

    private:
        Scene &scene;
        /* data */
    };
}