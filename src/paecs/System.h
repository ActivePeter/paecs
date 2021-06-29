#pragma once

// #include "Event.h"
#include "Entity.h"
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
// #include "Component.h"
#include "Component.h"
#include "Scene.h"

namespace paecs
{

	class World;
	class Scene;

	struct SysGroup
	{
		std::vector<std::shared_ptr<BaseSystem>> sysVector;
		void runAll()
		{
			for (const auto &sys : sysVector)
			{
				sys->update();
			}
		}
	};

	// template <typename... Comps>
	// class UpdateSystem : public System;
	template <typename... Comps>
	class UpdateSystem;

	namespace SystemAbout
	{
		template <class FuncType>
		struct Specializer
		{
			using SpecializedUpdateSystemType = int;
			enum
			{
				SysFuncOk = 0,
			};
		};
		template <class RetType, class... ArgsType>
		struct Specializer<RetType(ArgsType &...)>
		{
			using SpecializedUpdateSystemType = UpdateSystem<ArgsType...>;

			enum
			{
				SysFuncOk = 1,
			};
		};
	}
	// The system processes entities that it's interested in each frame. Derive from this one!

	class BaseSystem
	{
	public:
		virtual void update() {}
	};

	template <typename... Comps>
	class System : public BaseSystem
	{
	public:
		System(Scene &scene1, void *sysFunc1) : scene(scene1)
		{

			//在这里根据Comps生成componentMask
			ComponentMaskFuncs::ComponentMaskConstrctor<Comps...>().getMask(this->componentMask); // ComponentMaskFuncs::getComponentMaskOfComps<Comps...>();
			//传入需要回调的函数
			sysFunc = sysFunc1;
		}
		// virtual ~System();
		// virtual void init();
		virtual void update() {}
		// what component types the system requires of entities (we can use this method in the constructor for example)
		// template <typename FirsrCompType, typename... RestCompTypes>
		//void requireComponent();

		// returns a list of entities that the system should process each frame
		// std::vector<Entity> getEntities() { return entities; }

		// // adds an entity of interest
		// void addEntity(Entity e);

		// // if the entity is not alive anymore (during processing), the entity should be removed
		// void removeEntity(Entity e);

		//const ComponentMask& getComponentMask() const { return componentMask; }

	protected:
		// Scene &getScene() const;
		ComponentMask componentMask;
		Scene &scene;
		void *sysFunc;

	private:
		// template <typename CompType>
		// void requireComponent();
		// which components an entity must have in order for the system to process the entity

		//存储需要执行的函数指针

		// vector of all entities that the system is interested in
		// std::vector<Entity> entities;
	};

	// template <typename... Comps>
	// class SystemHasComp:System{

	// }
	/**
	 *
	 * 参考一下decs
	 *
	 * **/
	// 		template<typename... Args, typename Func>
	// 		void entity_chunk_iterate(DataChunk* chnk, Func&& function) {
	// 			auto tup = std::make_tuple(get_chunk_array<Args>(chnk)...);
	// #ifndef NDEBUG
	// 			(assert(std::get<decltype(get_chunk_array<Args>(chnk))>(tup).chunkOwner == chnk), ...);
	// #endif

	// 			for (int i = chnk->header.last - 1; i >= 0; i--) {
	// 				function(std::get<decltype(get_chunk_array<Args>(chnk))>(tup)[i]...);
	// 			}
	// 		}

	//在addsystem的时候创建这样的实例
	template <typename... Comps>
	class UpdateSystem : public System<Comps...>
	{
	public:
		UpdateSystem(Scene &scene1, void *sysFunc1)
			: System(scene1, sysFunc1) {}
		void update()
		{
			using CallBack = void (*)(...);
			CallBack callbak = (CallBack)sysFunc;
			//1.根据componentMask获取要遍历的archtype组
			// System<Comps...>::sc
			Scene &scene = this->scene;
			auto archtypes = scene.archtypeManager->findArchtypeContainingMask(this->componentMask);
			for (int i = 0; i < archtypes.size(); i++)
			{
				auto &chunks = archtypes[i]->chunks;
				auto pos = chunks.cbegin();
				for (; pos != chunks.cend(); ++pos)
				{
					for (int j = 0; j < (*pos)->entityCnt; j++)
					{
						callbak(((*pos)->getCompDataPtrOfIndex<Comps>(j))...);
					}
					//  useData(*pos);
				}
			}

			//2.遍历archtype中的数据。并且
		}
	};
	// template <typename T>
	// void System::requireComponent()
	// {
	//     const auto componentId = Component<T>::getId();
	//     componentMask.set(componentId);
	// }

}
