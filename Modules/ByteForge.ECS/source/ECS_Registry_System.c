#include "ECS/ECS_Registry_System.h"

#include <ByteForgeLogging.h>

bool ECS_Registry_CreateSystem(ECS_Registry* registry, const uint64_t required_entity_component_bitset, const char* const name, const ECS_SystemUpdateFunctionSignature update_function, const ECS_SystemFreeFunctionSignature free_function, const void* const data)
{
	ECS_System* system = ECS_System_Create(registry->systems->count, name, data, required_entity_component_bitset, update_function, free_function);

	if (!system)
	{
		LOG_FATAL("Error when trying to create ECS_System strucure for ECS_Registry.");
		return false;
	}

	if (!DynamicArray_Add(registry->systems, &system, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM))
	{
		LOG_FATAL("Error when trying to add ECS_System to the ECS_Registry systems array.");
		return false;
	}

	return true;
}