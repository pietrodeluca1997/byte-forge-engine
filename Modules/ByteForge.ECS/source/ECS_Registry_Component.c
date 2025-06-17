#include "ECS/ECS_Registry_Component.h"

#include <string.h>

void ECS_Registry_AddComponentToEntity(ECS_Registry* registry, const ECS_ComponentType* const component_type, const void* const component, const ECS_Entity entity)
{
	uint64_t* entity_component_bitset = DynamicArray_Get(registry->entities_components_bitsets, entity.id);
	uint64_t component_bit = 1ULL << component_type->id;
	*entity_component_bitset |= component_bit;

	Dictionary_AddOrUpdate(component_type->entity_id_to_array_index_map, &entity.id, &component_type->data_array->count, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
	DynamicArray_Add(component_type->data_array, component, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
}

bool ECS_Registry_RegisterComponentType(ECS_Registry* registry, const size_t size, const char* const name, const ECS_ComponentTypeFreeFunctionSignature free_function)
{
	ECS_ComponentType* component_type = ECS_ComponentType_Create(registry->component_types->count, size, name);

	if (!component_type) return false;

	if (free_function)
	{
		component_type->free_function = free_function;
	}

	DynamicArray_Add(registry->component_types, &component_type, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

	return true;
}

ECS_ComponentType* ECS_Registry_GetComponentTypeReferenceByName(const ECS_Registry* registry, const char* const name)
{
	for (uint64_t i = 0; i < registry->component_types->count; i++)
	{
		ECS_ComponentType** component_type = DynamicArray_Get(registry->component_types, i);

		if (strcmp((*component_type)->name, name) == 0)
		{
			return *component_type;
		}
	}

	return NULL;
}