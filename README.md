[【中文】](./README_CN.md)

# paecs

Implementation of ECS （Entity Component System）lib

## Table of Contents

[TOC]

## Background

When I'm writing a minecraft like game, I knows that ecs is a way to improve game performance. I'm writing this project not only for preparing for my minecraft project but also to improve my programming capability of c++  ---- it is the first complete and carefully designed c++ lib I'm writing.

## Features

- Archtype Model，entities are divided by component combination. Data is in continuous array which makes seeking and iteration faster.

- Easy to add component and system

  - only need to write a func with needed prams, then register it to system

    ```c++
    void helloworld_sys(A &a)
    {
    }
    scene.addSysByFunc(helloworld_sys);
    ```

  - only need to write a simple struct, then register it to component

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

## Design

## Start using

## Todo

- [ ]  multiple threads 