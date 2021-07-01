

![paecs](https://hanbaoaaa.xyz/tuchuang/images/2021/06/25/paecs.png)

# paecs

c++ implementation of ECS （Entity Component System）lib

c++的ecs库 （Entity Component System）

## Table of Contents (内容)

- [Record](./records/record.md)
- [Background](#Background)
- [Features](#Features)
- [Todo](#Todo)

## [Record (记录)](./records/record.md)

## Background (背景)

When I'm writing a minecraft like game, I knows that ecs is a way to improve game performance. I'm writing this project not only for preparing for my minecraft project but also to improve my programming capability of c++  ---- it is the first complete and carefully designed c++ lib I'm writing.

在我写我类似于mc游戏--voxelfram的时候，我了解到ecs是一种提升遍历性能的模式。写这个库的目的一方面是给我的voxelframe 用，一方面是提升我编写c++的能力，这也是我第一个完整且仔细设计过的c++库。

## Features (特性)

- Archtype Model，entities are divided by component combination. Data is in continuous array which makes seeking and iteration faster.

  archtype模型，实体（entity）被分为插件的组合，数据是存储在连续空间中的，这是ecs遍历和查找更快速的原因

- Easy to add component and system

  易于添加 **组件** 和 **系统**

  - **Add sys** Only need to write a func with needed prams, then register it to system
  
    只需要编写一个函数，参数包含需要访问到的组件，然后添加为系统即可
  
    ```c++
    void helloworld_sys(A &a)
    {
    }
    paecs::SysGroup systems;
    scene.addSys2Group(
            systems,
            helloworld_sys);
    ```
  
  - **Call Sys** by SysGroup
  
    ```c++
    systems.runAll();
    ```
  
  - **Add Entity** 
  
    Only need to write a simple struct, then register it to component
    
    只需要写一个简单的结构体，然后添加为组件即可
    
    可以添加**空插件**也可以传入一个**实例化的对象**来配置初始参数
    
    支持优雅的链式调用
    
    ```c++
    struct A
    {
        int id;
        A(int id):id(id){}
    };
    struct B
    {
        int id;
        char testChar;
    };
    A a(1);
    scene.createEntity()
            .addComponent(a)
            .addEmptyComponent<B>();
    ```
    
  - **Random Access** Input pointer to access entity by entityID
  
    输入指针然后访问entity对应组件的数据，
    
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
    

## Todo

- [x] random access

  随机访问

- [x] added SysGroup

  系统组概念

- [ ] multiple threads 

  多线程支持