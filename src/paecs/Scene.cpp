
#include "Core.h"
#include "Scene.h"
#include "memory"
#include "System.h"
#include "EntityManager.h"

namespace paecs
{
	class EntityManager;
	/////////////////////////////////////////////////////
	// system
	/////////////////////////////////////////////////////
	template <typename SysClass>
	Scene &Scene::addSys()
	{
		// if (hasSys<SysClass>())
		// {
		// 	goto end;
		// }

		// std::shared_ptr<SysClass> system(new SysClass(*this));
		// system->init();

		// systems.insert(std::make_pair(std::type_index(typeid(SysClass)), system));
	end:
		return *this;
	}

	template <typename SysClass>
	bool Scene::hasSys()
	{
	}

	//testing
	// void hhh(int a, bool b)
	// {
	// }
	// template <typename FuncType>
	// Scene &Scene::addSysByFunc(FuncType func)
	// {
	// 	//1.获取函数类型
	// 	using functype = decltype(hhh);

	// 	//2.获取到含有函数参数类型的sys类型
	// 	using speSys = SystemAbout::Specializer<funcType>::SpecializedUpdateSystemType;

	// 	// systems[std::type_index(typeid(funcType)];
	// 	// systems[std::type_index(typeid(funcType)] =std::dynamic_cast<BaseSystem>(std::make_shared<speSys>(*this, func));
	// 	// std::make_shared<speSys>(*this, func);

	// 	return *this;
	// 	//然后根据拿到的types创建system
	// 	// SpeSys()
	// 	//1.获取函数的参数类型组
	// 	// using params = decltype(util::args(helloworld));
	// 	//2.构造sys对象
	// 	// UpdateSystem<params>
	// }
	void Scene::loop()
	{ //遍历所有system
		for (const auto &sys : systems)
		{
			sys.second->update();
		}
	}

	/////////////////////////////////////////////////////
	// comp
	/////////////////////////////////////////////////////
	template <typename Func>
	void Scene::foreachComps(Func &&func)
	{
		using paramTypes = decltype(adv::args(&Func::operator()));

		// Query query;
		// adv::unpack_querywith(paramTypes{}, query).build();

		// for_each<Func>(query, std::move(function));
	}

	// std::unique_ptr<Scene>
	std::unique_ptr<Scene> createScene()
	{
		return std::make_unique<Scene>();
	}

	/////////////////////////////////////////////////////
	// entity
	/////////////////////////////////////////////////////
	// template <typename... Comps>
	EntityController Scene::createEntity()
	{
		return entityManager->createEntity();
	}

	bool Scene::deleteEntity(EntityID id)
	{
		return this->entityManager->deleteEntity(id);
	}
}