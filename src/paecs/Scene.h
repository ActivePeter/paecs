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
#include "Entity.h"

namespace paecs
{
	// class ECManager;
	class EntityManager;
	class ArchtypeManager;
	class Scene
	{
	private:
		phmap::flat_hash_map<std::type_index, std::shared_ptr<BaseSystem>> systems;

		// std::unique_ptr<Entity> = nullptr;
		// std::unique_ptr<SManager> sManager = nullptr;
		/* data */

		ArchtypeManager archtypeManager = ArchtypeManager(*this);
		EntityManager entityManager = EntityManager(*this);

	public:
		Scene(/* args */) {}
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
		Scene &addSysByFunc(FuncType func);
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
		template <typename... Comps>
		inline EntityController createEntity();

		//删除entity
		inline bool deleteEntity(EntityID id);

		// std::unique_ptr<EventManager> eventManager = nullptr;
		// ~Scene();
		void loop();
	};

	std::unique_ptr<Scene> createScene();

}