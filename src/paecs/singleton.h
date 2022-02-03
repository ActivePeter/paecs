#pragma once
#include "core.h"
#include "vector"
#include "parallel_hashmap/phmap.h"

namespace paecs
{
	class SingletonManager
	{
	private:
		std::vector<char> buf;
		phmap::flat_hash_map<size_t, size_t> typeid_2_pos;
	public:
		template <typename ResType>
		void registSingleton(std::function<void(ResType&)> func);
		template <typename ResType>
		ResType* getSingletonPtr();
	};

	//不提供remove了，singleton没什么动态性
	template <typename ResType>
	void SingletonManager::registSingleton(std::function<void(ResType&)> init_func)
	{
		if (typeid_2_pos.contains(typeid(ResType).hash_code()))
		{
			log::out("same type singleton cant be added more than once");
			return;
		}
		auto begin = buf.size();
		buf.resize(buf.size() + sizeof(ResType));
		typeid_2_pos[typeid(ResType).hash_code()] = begin;
		init_func(*(ResType*)(buf.data() + begin));
	}

	template <typename ResType>
	ResType* SingletonManager::getSingletonPtr()
	{
		if (typeid_2_pos.contains(typeid(ResType).hash_code()))
		{
			return (ResType*)(buf.data() + typeid_2_pos[typeid(ResType).hash_code()]);
		}
		else
		{
			return nullptr;
		}
	}
}