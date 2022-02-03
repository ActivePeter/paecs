#include "Scene.h"

#include "Core.h"
#include "memory"
#include "System.h"
#include "EntityManager.h"

namespace paecs
{
	class EntityManager;
	/////////////////////////////////////////////////////
	// comp
	/////////////////////////////////////////////////////
	template <typename Func>
	void Scene::foreachComps(Func&& func)
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

	// template <typename... CompType>

	bool Scene::deleteEntity(EntityID id)
	{
		return this->entityManager->deleteEntity(id);
	}
}