struct SysGroup;

#ifndef __paecs_SYSTEM_H__
#define __paecs_SYSTEM_H__

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
		// std::type_index sysId;
		virtual void update() {}
		// BaseSystem() {}
	};

	/**
	 * 系统组，用于分离不同调用时的系统
	 * SysGroup, used to separate systems with different calling time
	*/
	struct SysGroup
	{
		phmap::flat_hash_map<std::type_index, std::shared_ptr<BaseSystem>> systems;
		uint64_t run_cnt = 0;
		// std::vector<std::shared_ptr<BaseSystem>> systems;
		void runAll()
		{
			for (const auto& sys : systems)
			{
				sys.second->update();
			}

			//run_cnt++;
		}
	};

	template <typename... Comps>
	class System : public BaseSystem
	{
	public:
		System(Scene& scene1, void* sysFunc1) : scene(scene1)
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
		Scene& scene;
		void* sysFunc;

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
	template <typename ArgType>
	ArgType* _get_arg_ptr(Scene& scene, const std::shared_ptr<paecs::Chunk>& chunk, int index)
	{
		auto a = scene.getSingletonPtr<ArgType>();
		if (a)
		{
			return a;
		}
		return chunk->getCompDataPtrOfIndex<ArgType>(index);
	}
	template <typename T>
	int _cnt_single_(Scene& scene, T* t)
	{
		return scene.getSingletonPtr<T>() != nullptr;
	}
	template <typename T, typename...Ts>
	int _cnt_single_(Scene& scene, T* t, Ts*...ts)
	{
		return _cnt_single_(scene, t) + _cnt_single_(scene, ts...);
	}
	template <typename T>
	int _cnt_of_T(T* t)
	{
		return 1;
	}
	template <typename T, typename...Ts>
	int _cnt_of_T(T* t, Ts* ...ts)
	{
		return _cnt_of_T(t) + _cnt_of_T(ts...);
	}
	//在addsystem的时候创建这样的实例
	template <typename... Comps>
	class UpdateSystem : public System<Comps...>
	{
		int cnt_of_single = 0;
		int cnt_of_T = 0;
	public:
		UpdateSystem(Scene& scene1, void* sysFunc1)
			: System(scene1, sysFunc1)
		{
			char* a = nullptr;
			cnt_of_single = _cnt_single_(scene1, (Comps*)(a)...);
			cnt_of_T = _cnt_of_T<>((Comps*)(a)...);
		}
		void update()
		{
			using CallBack = void (*)(...);
			CallBack callbak = (CallBack)sysFunc;
			//1.根据componentMask获取要遍历的archtype组
			// System<Comps...>::sc
			Scene& scene1 = this->scene;
			if (cnt_of_T == cnt_of_single)
			{
				callbak(
					(scene1.getSingletonPtr<Comps>())...
				);
				return;
			}
			auto archtypes = scene1.archtypeManager->findArchtypeContainingMask(this->componentMask);
			for (int i = 0; i < archtypes.size(); i++)
			{
				auto& chunks = archtypes[i]->chunks;
				auto pos = chunks.cbegin();
				for (; pos != chunks.cend(); ++pos)
				{
					for (uint32_t j = 0; j < (*pos)->entityCnt; j++)
					{
						callbak(
							(_get_arg_ptr<Comps>(scene1, (*pos), j))...
						);
						//callbak(((*pos)->getCompDataPtrOfIndex<Comps>(j))...);
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

#endif // __SYSTEM_H__