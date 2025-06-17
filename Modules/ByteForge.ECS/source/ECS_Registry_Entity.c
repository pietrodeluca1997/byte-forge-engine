#include "ECS/ECS_Registry_Entity.h"

#include <ByteForgeLogging.h>

bool ECS_Registry_CreateEntity(ECS_Registry* registry, ECS_Entity* const out_entity)
{
	ECS_Entity new_entity = ECS_Entity_Create(registry->entities_current_id++);

	if (!DynamicArray_Add(registry->entities, &new_entity, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY))
	{
		LOG_FATAL("Error when trying to add ECS_Entity to the ECS_Registry systems array.");
		return false;
	}

	*out_entity = new_entity;

	uint64_t initial_entity_bitset = 0;

	if (!DynamicArray_Add(registry->entities_components_bitsets, &initial_entity_bitset, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY_COMPONENTS_BITSET))
	{
		LOG_FATAL("Error when trying to add entity component bitset to the ECS_Registry entities components bitsets array.");
		return false;
	}

	return true;
}

void ECS_Registry_PublishEntity(ECS_Registry* registry, ECS_Entity entity)
{
    DynamicArray_Add(registry->entities_to_add, &entity, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY);
}

void ECS_Registry_SpawnEntities(ECS_Registry* registry)
{
    for (int64_t i = registry->entities_to_add->count - 1; i >= 0; i--)
    {
        ECS_Entity* entity = DynamicArray_Get(registry->entities_to_add, i);
        ECS_Registry_SpawnEntity(registry, *entity);     

        DynamicArray_Remove(registry->entities_to_add, i);
    }
}

void ECS_Registry_SpawnEntity(ECS_Registry* registry, const ECS_Entity entity)
{
    uint64_t* entity_component_bitset = DynamicArray_Get(registry->entities_components_bitsets, entity.id);

    if (!entity_component_bitset) return;

    for (uint64_t i = 0; i < registry->systems->count; i++)
    {
        ECS_System** system = DynamicArray_Get(registry->systems, i);

        if (!system || !*system) return;

        if (((*system)->required_entity_components_bitset & *entity_component_bitset) == (*system)->required_entity_components_bitset)
        {
            DynamicArray_Add((*system)->entities, &entity, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY);
        }
    }
}

void ECS_Registry_AddEntityToKillQueue(ECS_Registry* registry, ECS_Entity entity)
{
	DynamicArray_Add(registry->entities_to_kill, &entity, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY);
}

void ECS_Registry_KillEntities(ECS_Registry* registry)
{
	for (int64_t i = registry->entities_to_kill->count - 1; i >= 0; i--)
	{
		ECS_Entity* entity = DynamicArray_Get(registry->entities_to_kill, i);
		ECS_Registry_KillEntity(registry, *entity);
		DynamicArray_Remove(registry->entities_to_kill, i);
	}
}

void ECS_Registry_KillEntity(ECS_Registry* registry, ECS_Entity entity)
{
    for (int64_t i = (int64_t)registry->systems->count - 1; i >= 0; i--)
    {
        ECS_System** system = DynamicArray_Get(registry->systems, i);

        if (system && *system)
        {
            for (int64_t j = (int64_t)(*system)->entities->count - 1; j >= 0; j--)
            {
                ECS_Entity* interested_entity = DynamicArray_Get((*system)->entities, j);

                if (interested_entity && interested_entity->id == entity.id)
                {
                    DynamicArray_Remove((*system)->entities, j);
                    break;
                }
            }
        }
    }

    for (int64_t i = (int64_t)registry->component_types->count - 1; i >= 0; i--)
    {
        ECS_ComponentType** component_type = DynamicArray_Get(registry->component_types, i);

        if (component_type && *component_type)
        {
            uint64_t* array_index = Dictionary_Get((*component_type)->entity_id_to_array_index_map, &entity.id);

            if (array_index)
            {
                uint64_t array_index_value = *array_index;

                DynamicArray_Remove((*component_type)->data_array, array_index_value);
                Dictionary_Remove((*component_type)->entity_id_to_array_index_map, &entity.id);

                for (int64_t j = (int64_t)(*component_type)->entity_id_to_array_index_map->count - 1; j >= 0; j--)
                {
                    uint64_t* keys = (uint64_t*)(*component_type)->entity_id_to_array_index_map->keys;
                    uint64_t* values = (uint64_t*)(*component_type)->entity_id_to_array_index_map->values;

                    if (values[j] > array_index_value)
                    {
                        values[j]--;
                    }
                }
            }
        }
    }

    for (int64_t i = (int64_t)registry->entities->count - 1; i >= 0; i--)
    {
        ECS_Entity* entity_query = DynamicArray_Get(registry->entities, i);

        if (entity_query && entity_query->id == entity.id)
        {
            DynamicArray_Remove(registry->entities, i);
            break;
        }
    }
}
