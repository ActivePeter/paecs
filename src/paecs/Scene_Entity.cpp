#include "Scene.h"
namespace paecs
{
    template <typename... Comps>
    inline EntityController Scene::createEntity()
    {
        // Archetype *arch = nullptr;
        // //empty component list will use the hardcoded null archetype
        // if constexpr (sizeof...(Comps) != 0)
        // {
        //     static const Metatype *types[] = {adv::get_metatype<Comps>()...};
        //     constexpr size_t num = (sizeof(types) / sizeof(*types));

        //     adv::sort_metatypes(types, num);
        //     arch = adv::find_or_create_archetype(this, types, num);
        // }
        // else
        // {
        //     arch = get_empty_archetype();
        // }
        // auto entityId = adv::create_entity_with_archetype(arch);
        // return EntityController(*this, entityId);
    }
}
