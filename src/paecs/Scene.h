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
#include "singleton.h"

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
		//
		//		Part: system

		/**
			* @brief 将系统加入组
			* @param sysGroup    目标系统组
			* @param sysFunc        系统函数
		*/
		template <typename FuncType>
		Scene& addSys2Group(SysGroup& sysGroup, FuncType* func); //;

		// EventManager &getEventManager() const;

		/////////////////////////////////////////////////////
		//
		// 		Part: comp
		//
		template <typename Func>
		void foreachComps(Func&& func);

		//////////////////////////////////////////////////////
		//
		//		entity

		//创建entity
		// template <typename... Comps>
		EntityController createEntity();

	private:
		void setCompRef(EntityDataPos& entityDataPos1, ...) {}					  //定义零个参数函数，递归调用到零个参数函数时。调用该函数，然后终止继续递归
		template <typename T, typename... Args>									  //Args是一个模板参数包
		void setCompRef(EntityDataPos& entityDataPos1, T*& first, Args*&...left) //args是一个函数参数包
		{
			first = entityDataPos1.chunkPtr->getCompDataPtrOfIndex<T>(entityDataPos1.index);
			setCompRef(entityDataPos1, left...);
		}
		SingletonManager singleton_manager;
	public:
		/**
		 * templete函数
		 * 随机访问entity的某一个插件属性
		 * 	 要通过返回值判断是否有效
		*/
		template <typename... CompType>
		bool randomAccessEntity(const EntityID& id, CompType*&...comp)
		{
			auto& entityDataPos1 = entityManager->getEntityDataPosById(id);
			setCompRef(entityDataPos1, comp...);
			// entityDataPos1.chunkPtr->getCompDataOfIndex<CompType>(entityDataPos1.index)...;

			return true;
		}
		//删除entity
		bool deleteEntity(EntityID id);

		template <typename ResType>
		void registSingleton(std::function<void(ResType&)> init_func)
		{
			singleton_manager.registSingleton(init_func);
		}
		template <typename ResType>
		ResType* getSingletonPtr()
		{
			return singleton_manager.getSingletonPtr<ResType>();
		}
	};

	std::unique_ptr<Scene> createScene();

}

#include "Scene.temp.h"