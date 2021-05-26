#include "paecs.h"
namespace paecs_example
{
    struct A
    {
        A(int x = 0, int y = 0) : x(x), y(y) {}
        int x, y;
    };

    struct B
    {
        B(int dx = 0, int dy = 0) : dx(dx), dy(dy) {}
        int dx, dy;
    };
    struct C
    {
        C(int dx = 0, int dy = 0) : dx(dx), dy(dy) {}
        int dx, dy;
    };

    class HelloworldSystem : public paecs::System
    {
    public:
        // HelloworldSystem(paecs::Scene scene)
        void init() override
        {
            requireComponent<A, B, C>();
        }

        void update(paecs::Scene &scene)
        {
            scene.foreachComps(
                [&](paecs::EntityID id, A &a, B &b)
                {
                    // count++;
                });
        }
    };

    void main()
    {
        auto ecsScene = *(paecs::createScene());

        ecsScene
            .createEntity()
            .addEmptyComponent<A>()
            .addEmptyComponent<B>();
        ecsScene
            .addSys<HelloworldSystem>();

        while (1)
        {
            ecsScene.loop();
            /* code */
        }

        // .addComponent<A>();

        // ecsScene.addSys<HelloworldSystem>();
    }
}