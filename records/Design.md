## 按照启动时的运行流程来举例子

### 1.首先是创建一些entity

并且绑定component

```c++
auto e = scene.createEntity();

  e.addComponent<PositionComponent>(100, 100);

  e.addComponent<VelocityComponent>(10, 10);
```

对应的要先写component的**结构体/类**

```c++
struct PositionComponent
{
    PositionComponent(int x = 0, int y = 0) : x(x), y(y) {}
    int x, y;
};

struct VelocityComponent
{
    VelocityComponent(int dx = 0, int dy = 0) : dx(dx), dy(dy) {}
    int dx, dy;
};
```



### 3.考虑一个问题 system如何去获取需要的component 对的

这里网上基本有两种思路，

- 一种是bitset（称为mask，用于标记entity跟componentde 关系
- 另一种是archtype。将一类component组合作为数据存储的最小单元（称为archtype），进行连续存储，然后

对于遍历来说，应该是**后者**更高效，因为system只遍历它关心的东西。我们把它关心的东西放入一个连续内存里，那么唯一的损失是在增删component时，需要转移数据位置

 所以比较关键的一点是先创建archtype数据结构

### 4.设计archtype的数据结构

参考unity的archtype设计，一段连续数据存储在成为chunk的数据块内，而chunk之间则使用类似链表的结构进行连接，因为chunk里的数据量比较大，所以遍历时跳转chunk地址的影响不会很大

比如我们的system 通过一定的语句表示只关心 component A，B 组合

那么我们需要编写代码 自动根据这个组合 去创建一个 专门的archtype 

这个archtype里的单元就是chunk，我们选择list对chunks进行存储

目前来看的话数据的结构大概就是这样的

```c++
struct Archtype<A,B,...>{//某一类set的所有chunk
	SetDescription<A,B> setDesc;
	list<Chunk> chunks;
};
struct Chunk{//chunk的数据结构
	byte storage[BLOCK_MEMORY_16K - sizeof(DataChunkHeader)];
}

struct SetDescription<A,B,...>{//set的描述
	int maxCnt;
	static offset;
}
```

![image-20210525124310182](https://hanbaoaaa.xyz/tuchuang/images/2021/05/25/image-20210525124310182.png)

如上，我们还需要计算b的起始位置，因此对archtype的描述还要加入offset组



如上的chunk还不能直接获取到我们要的component信息，接下来就是利用语法去设计出获取以及操作component的结构，因为强制转换指针到类型了，所以可以读出

```c++
template<typename ComponentType>
struct ComponentArray {
    ComponentArray(void* pointer) {
        data = (T*)pointer;
    }
    const T& operator[](size_t index) const {
        return data[index];
    }
    T& operator[](size_t index) {
        return data[index];
    }
    ComponentType* data;
}
```

这里位置数据的存储和读出应该是没问题了。

然后要考虑的是。如何设计system以及system过滤出需要的archtype



### 5.实现addSystem函数

system是一个每帧（或特定时段）被调用的函数

> 理想的模式是这样的：
>
> 形如
>
> ```c++
> void helloworld(A a,B b){
>     
> }
> void helloworld2(A a,B b,C c){
>     
> }
> main(){
>     addSys(helloworld);
> 	addSys(helloworld2);
>     while(1){
>         runSys();
>     }
> }
> 
> ```
>
> 这样的形式便让我们可以获取到需要的需要的组件AB的迭代器。然后对他们进行遍历
>
> iter元素有 Entity，A，B
>
> 
>
> 这个函数需要被注册，那么我们要写一个addSystem函数
>
> addSystem函数的参数是helloworld，那么问题来了，addSystem时我们需要生成一个对应system涉及到的component的过滤器10001这样的mask，表示对哪些component感兴趣，以便后续生成迭代器（archtype 跟这个过滤器做位运算，获取到符合过滤器的archtypes，
>
> 还有一个问题是存储systems。c++ 怎么存储不同类型的函数到一个列表里

因为这些问题，我先选择使用较为容易实现的方法（其实一点也不容易

核心代码：

```c++
template <typename SysClass>
Scene &Scene::addSys()
{
    if (hasSys<SysClass>())
    {
        goto end;
    }

    std::shared_ptr<SysClass> system(new SysClass);
    systems.insert(std::make_pair(std::type_index(typeid(SysClass)), system));
    end:
    return this;
}
```

调用代码：

```c++
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
    ecsScene
        .addSys<HelloworldSystem>();
    // .addComponent<A>();

    // ecsScene.addSys<HelloworldSystem>();
}
```

### 6.ComponentMask

这个玩意需要在两个地方存在，一个是System创建的时候；一个是创建archtype(插件组类型)时候

system我参考下mix

```c++
/*
    * 这部分代码用来获取component类型对应的id，以用于生成mask
    */

    // Used to be able to assign unique ids to each component type.
    struct BaseComponentIdCounter
    {
        using Id = uint8_t;
        // static const Id MaxComponents = config::MAX_COMPONENTS;

    protected:
        static Id nextId; //静态全局量,每次递增
    };

    // Used to assign a unique id to a component type, we don't really have to make our components derive from this though.
    template <typename T>
    struct ComponentIdCounter : BaseComponent
    {
        // Returns the unique id of Component<T>
        static Id getId()
        {
            static auto id = nextId++; //只有第一次调用会执行赋值,后续都是记忆之前的数据,
            // if(id==MaxComponents)
            // assert(id < MaxComponents);
            return id;
        }
    };

    // Used to keep track of which components an entity has and also which entities a system is interested in.
    using ComponentMask = std::bitset<config::MAX_COMPONENTS>; //<total size>
```

每次新的不同类型都会nextId+1，

### 7.Archtype 具体实现

chunk是一个单位，他的内存可以在任意的位置创建，所以我们 给每个archtype<...T>一个空的list

当有新的entity创建时候，会需要一个archtype并在里面记录数据，则这个archtype

### 8.讨论entity的作用

entityId

既然archtype已经足够拿来筛选要操作的数据了。那么为什么还会需要entity呢？

应该主要是entity的删除，当需要删除entity的时候，怎么去标记删除掉的区块中的内容，

看了一下，作用应该是随机访问，就是针对性的去操作一个entity的时候，这里我想到的一种是跟随，比如怪物要跟随玩家这样的，怪物应该就得存玩家的entityId



![image-20210527225443466](https://hanbaoaaa.xyz/tuchuang/images/2021/05/27/image-20210527225443466.png)

### 9.entity的创建和删除

先不管entityid 创建和删除，先考虑 archtype中数据的增加删除

增加比较容易。直接将数据长度+1就行了

删除：因为数据在chunk中是连续的，那么删除一组component，目前我想到的办法就是把后面的内存复制到前面来，然后长度-1；

 ~~暂时有一个未认证的思路，删除就对这个数据做个标记，并存入archtype的deleted list里 后续直接使用，就避免了数据还要往前移动的操作；或者把直接把archtype类型+顺序作为entityId，这样再次创建的时候就可以直接查找到原先的位。~~



> 再说entityId的作用，无非就是最终要查到archtype中的具体一项，那么，我准备用hashmap把id作为key。把实际数据的位置作为value。这样就可以方便的查找和删除entity了。
>
> 同时要把删掉的entityids存入一个list，以备后续再利用

> 又有一种思路，如果单纯只是为了查到某个entity的话，会不会直接将entity的数据位置记录下来更快（chunk指针+ 在chunk中的位置，（数据也不是很大。  
>
>  突然又想到一个问题，当这个要被查找的entity删除了，依然可以获取到chunk指针+在chunk中的位置。但获取不到被删除的信息。此时指向的数据已经不再是原来的entity了

这么一想好像entityId有必要了，它用于保证entity变更后（删除 或 添加删除组件，）依然可以被查询到

并且需要标记generation，表示已经是删除后重新生成的entity了