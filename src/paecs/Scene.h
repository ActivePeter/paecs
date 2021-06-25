#pragma once
// #include "ECManager.h"
// #include "SManager.h"
#include <memory>
#include <typeindex>

#include "parallel_hashmap/phmap.h"

#include "Core.h"
#include "System.h"
#include "Entity.h"
#include "Archtype.h"
#include "EntityManager.h"
#include "ArchtypeManager.h"
// #include "Entity.h"
#include "unordered_map"

namespace paecs
{
	// class ECManager;
	class EntityManager;
	class ArchtypeManager;
	class EntityController;
	class BaseSystem;
	/////////////////////////////////////

	class Scene
	{
	private:
	public:
		// variable /////////////////////////
		phmap::flat_hash_map<std::type_index, std::shared_ptr<BaseSystem>> systems;
		// std::unordered_map<std::type_index, std::shared_ptr<BaseSystem>> systems;
		// std::unique_ptr<Entity> = nullptr;
		// std::unique_ptr<SManager> sManager = nullptr;
		/* data */

		// ArchtypeManager archtypeManager(*this);
		// EntityManager entityManager(*this);

		std::shared_ptr<ArchtypeManager> archtypeManager;
		std::shared_ptr<EntityManager> entityManager;
		/////////////////////////////////////

		Scene(/* args */)
		{
			archtypeManager = std::make_shared<ArchtypeManager>(*this);
			entityManager = std::make_shared<EntityManager>(*this);
		}
		// ECManager &getEntityManager() const;
		// SManager &getSystemManager() const;

		/////////////////////////////////////////////////////
		// sys
		/////////////////////////////////////////////////////
		template <typename SysClass>
		Scene &addSys();

		template <typename SysClass>
		bool hasSys();

		template <typename FuncType>
		Scene &addSysByFunc(FuncType *func) //;
		{
			//1.获取函数类型
			// using functype = decltype(func);

			//2.获取到含有函数参数类型的sys类型
			// using speSys = UpdateSystem<A>;
			using speSys = SystemAbout::Specializer<FuncType>::SpecializedUpdateSystemType;
			// speSys(*this, &func);

			auto a = speSys(*this, func);
			auto b = std::make_shared<speSys>(*this, func);
			auto sysId = std::type_index(typeid(FuncType));
			// auto baseSysPtr = std::dynamic_cast<BaseSystem>(std::make_shared<speSys>(*this, func));
			systems[sysId] = std::static_pointer_cast<BaseSystem>(b);
			// systems[std::type_index(typeid(int)] =baseSysPtr;
			// std::make_shared<speSys>(*this, func);

			return *this;
			//然后根据拿到的types创建system
			// SpeSys()
			//1.获取函数的参数类型组
			// using params = decltype(util::args(helloworld));
			//2.构造sys对象
			// UpdateSystem<params>
		}
		// EventManager &getEventManager() const;

		/////////////////////////////////////////////////////
		// comp
		/////////////////////////////////////////////////////

		template <typename Func>
		void foreachComps(Func &&func);

		/////////////////////////////////////////////////////
		// entity
		/////////////////////////////////////////////////////

		//创建entity
		// template <typename... Comps>
		EntityController createEntity();

		/**
		 * templete函数
		 * 随机访问entity的某一个插件属性
		 * 	 要通过返回值判断是否有效
		*/
		template <typename... CompType>
		bool randomAccessEntity(const EntityID &id, CompType &&...comp)
		{
			return false;
		}
		//删除entity
		bool deleteEntity(EntityID id);

		// std::unique_ptr<EventManager> eventManager = nullptr;
		// ~Scene();
		void loop();
	};

	std::unique_ptr<Scene> createScene();

}