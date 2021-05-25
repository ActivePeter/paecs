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

    class HelloworldSystem : public paecs::System
    {
    public:
        HelloworldSystem()
        {
            requireComponent<A, B>();
        }

        void update(Scene &scene)
        {
            scene.each(
                [&](EntityID id, A &a, B &b)
                {
                    count++;
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
        // .addComponent<A>();

        // ecsScene.addSys<HelloworldSystem>();
    }
}