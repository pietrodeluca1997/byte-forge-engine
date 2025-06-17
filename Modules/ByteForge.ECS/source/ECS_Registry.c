#include "ECS/ECS_Registry.h"

#include <ByteForgeLogging.h>

#include <ByteForgeMemory.h>

#include <string.h>

bool ECS_Registry_Create(ECS_Registry** out_registry)
{
	ECS_Registry* registry = ALLOC(ECS_Registry, MEMORY_ALLOCATION_CATEGORY_ECS_REGISTRY);

	if (!registry)
	{
		LOG_FATAL("Error when trying to allocate memory for ECS registry.");
		return false;
	}

	registry->entities_current_id = 0;

	if (
		!DynamicArray_Initialize(&registry->entities, sizeof(ECS_Entity), 10, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY) ||
		!DynamicArray_Initialize(&registry->component_types, sizeof(ECS_ComponentType*), 10, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE) || 
		!DynamicArray_Initialize(&registry->systems, sizeof(ECS_System), 10, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM) || 
		!DynamicArray_Initialize(&registry->entities_components_bitsets, sizeof(uint64_t), 10, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY_COMPONENTS_BITSET) ||
		!DynamicArray_Initialize(&registry->entities_to_kill, sizeof(ECS_Entity), 10, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY) ||
		!DynamicArray_Initialize(&registry->entities_to_add, sizeof(ECS_Entity), 10, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY)
	)
	{
		LOG_FATAL("Error trying to initialize dynamic arrays that the ECS registry depends on.");

		ECS_Registry_Free(&registry);

		return false;
	}

	*out_registry = registry;

	return true;	
}

void ECS_Registry_PrintInfo(const ECS_Registry* registry)
{
	LOG_NEW_LINE();

	LOG_INFO("ECS Registry entities: ");
	for (uint64_t i = 0; i < registry->entities->count; i++)
	{
		ECS_Entity* entity = DynamicArray_Get(registry->entities, i);
		ECS_Entity_PrintInfo(i, entity);
	}

	LOG_INFO("ECS Registry systems: ");
	for (uint64_t i = 0; i < registry->systems->count; i++)
	{
		ECS_System** system = DynamicArray_Get(registry->systems, i);
		ECS_System_PrintInfo(i, *system);
	}

	LOG_INFO("ECS Registry component types: ");
	for (uint64_t i = 0; i < registry->component_types->count; i++)
	{
		ECS_ComponentType** component_type = DynamicArray_Get(registry->component_types, i);
		ECS_ComponentType_PrintInfo(i, *component_type);
	}
}

void ECS_Registry_Update(ECS_Registry* registry, const double delta_time)
{
	for (uint64_t i = 0; i < registry->systems->count; i++)
	{
		ECS_System** system = DynamicArray_Get(registry->systems, i);
		(*system)->update_function(registry, *system, delta_time);
	}
}

void ECS_Registry_Free(ECS_Registry** registry)
{
	for (uint64_t i = 0; i < (*registry)->systems->count; i++)
	{
		ECS_System** system = DynamicArray_Get((*registry)->systems, i);
		ECS_System_Free(system);
	}

	DynamicArray_Free(&(*registry)->systems, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);

	for (uint64_t i = 0; i < (*registry)->component_types->count; i++)
	{
		ECS_ComponentType** component_type = DynamicArray_Get((*registry)->component_types, i);
		ECS_ComponentType_Free(component_type);
	}

	DynamicArray_Free(&(*registry)->component_types, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
	DynamicArray_Free(&(*registry)->entities, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY);
	DynamicArray_Free(&(*registry)->entities_components_bitsets, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY_COMPONENTS_BITSET);
	DynamicArray_Free(&(*registry)->entities_to_kill, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY);
	DynamicArray_Free(&(*registry)->entities_to_add, MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY);

	FREE(registry, sizeof(ECS_Registry), MEMORY_ALLOCATION_CATEGORY_ECS_REGISTRY);
}
