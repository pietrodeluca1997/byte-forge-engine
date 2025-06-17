#pragma once

#include <ByteForgeMemory.h>

#include <stdint.h>
#include <stddef.h>


typedef void (*ECS_ComponentTypeFreeFunctionSignature)(void** component_type_data);


// Represents a component type in the ECS system.
typedef struct ECS_ComponentType
{
    uint64_t id;
    size_t size;
    char* name;
    DynamicArray* data_array;
    Dictionary* entity_id_to_array_index_map;
    ECS_ComponentTypeFreeFunctionSignature free_function;
} ECS_ComponentType;

/**
 * @brief Creates and initializes a new ECS_ComponentType.
 *
 * @param id: Unique identifier for the component type.
 * @param size: Size of each component instance in bytes.
 * @param name: Name of the component type.
 *
 * @return Pointer to the newly created ECS_ComponentType.
 */
ECS_ComponentType* ECS_ComponentType_Create(const uint64_t id, const size_t size, const char* const name);

/**
 * @brief Prints the information of a given ECS_ComponentType.
 *
 * @param registry_index: Index of the component type in the ECS registry.
 * @param component_type: Pointer to the ECS_ComponentType to print info for.
 */
void ECS_ComponentType_PrintInfo(const size_t registry_index, const ECS_ComponentType* const component_type);

/**
 * @brief Frees the resources used by a given ECS_ComponentType.
 *
 * @param component_type: Pointer to the ECS_ComponentType to free.
 */
void ECS_ComponentType_Free(ECS_ComponentType** component_type);