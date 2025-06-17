#include "ECS/ECS_System.h"
#include "ECS/ECS_Entity.h"

#include <ByteForgeMemory.h>

#include <ByteForgeLogging.h>

#include <stdlib.h>

ECS_System* ECS_System_Create(const uint64_t id, const char* const name, const void* const data, const uint64_t required_entity_components_bitset, const ECS_SystemUpdateFunctionSignature update_function, const ECS_SystemFreeFunctionSignature free_function)
{
	ECS_System* system = ALLOC(ECS_System, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);

	if (!system)
	{
		LOG_FATAL("Error when trying to allocate for ECS_System strucure. ");
		return NULL;
	}

	system->id = id;
	system->required_entity_components_bitset = required_entity_components_bitset;
	system->name = (char*) name;
	system->update_function = update_function;
	system->data = (void*) data;
	system->free_function = free_function;


	if (!DynamicArray_Initialize(&system->entities, sizeof(ECS_Entity), 10, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM))
	{
		LOG_FATAL("Error when trying to initialize ECS_Entity dynamic array for ECS_System strucure. ");

		ECS_System_Free(&system);
		return NULL;
	}

	return system;
}

void ECS_System_PrintInfo(const uint64_t registry_vector_index, const ECS_System* const ecs_system)
{
	LOG_DEBUG("==================== ECS System Debug ====================");
	LOG_DEBUG("Index           : %llu", registry_vector_index);
	LOG_DEBUG("System ID       : %llu", ecs_system->id);
	LOG_DEBUG("System Name     : %s", ecs_system->name);
	LOG_DEBUG("Required Bitset : 0x%016llX", ecs_system->required_entity_components_bitset);
	LOG_DEBUG("Entities        : %d", ecs_system->entities ? ecs_system->entities->count : 0);
	LOG_DEBUG("==========================================================");

	LOG_NEW_LINE();
}

void ECS_System_Free(ECS_System** system)
{
	if (!system || !*system) return;

	DynamicArray_Free(&(*system)->entities, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
	(*system)->free_function(&(*system)->data);
	FREE(&(*system)->data, sizeof(void*), MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
	FREE(system, sizeof(ECS_System), MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
}
