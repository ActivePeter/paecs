[【中文】](./README_CN.md)

# paecs

c++的ecs库 （Entity Component System）

## 内容

- [记录](./records/record.md)
- [背景](#Background)
- [特性](#Features)
- [开始使用](#Start-using)
- [Todo](#Todo)

## [记录](./records/record.md)

## Background

在我写我类似于mc游戏--voxelfram的时候，我了解到ecs是一种提升遍历性能的模式。写这个库的目的一方面是给我的voxelframe 用，一方面是提升我编写c++的能力，这也是我第一个完整且仔细设计过的c++库。

## Features

- Archtype Model，entities are divided by component combination. Data is in continuous array which makes seeking and iteration faster.

- Easy to add component and system

  - Only need to write a func with needed prams, then register it to system

    ```c++
    void helloworld_sys(A &a)
    {
    }
    scene.addSysByFunc(helloworld_sys);
    ```

  - Only need to write a simple struct, then register it to component

    ```c++
    struct A
    {
        int id;
    };
    struct B
    {
        int id;
        char testChar;
    };
    scene.createEntity()
            .addEmptyComponent<A>()
            .addEmptyComponent<B>();
    ```

  - Input pointer to access entity by entityID

    ```c++
    EcsComp::Position3D *ecspos;
    if (App::getInstance().ecsPtr->randomAccessEntity(
        entityId,
        ecspos))
    {
        ecspos->x = pos.x;
        ecspos->y = pos.y;
        ecspos->z = pos.z;
    }
    cameraPtr->Position = pos;
    ```

    

## Start using

## Todo

- [ ] random access
- [ ] multiple threads 