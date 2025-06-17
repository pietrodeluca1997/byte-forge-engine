#pragma once

#include <stdint.h>

#include <ByteForgeMemory.h>

/**
 * @brief Update function for the ECS system, called on every ECS update cycle.
 *
 * @param registry: Pointer to the ECS registry.
 * @param ecs_system: Pointer to the system being updated.
 */
typedef void (*ECS_SystemUpdateFunctionSignature)(struct ECS_Registry*, struct ECS_System*, const double delta_time);
typedef void (*ECS_SystemFreeFunctionSignature)(void** system_data);

/**
 * @brief Structure representing a system in the ECS.
 */
typedef struct ECS_System
{    
    uint64_t id;
    char* name;
    void* data;
    uint64_t required_entity_components_bitset;
    ECS_SystemUpdateFunctionSignature update_function;
    ECS_SystemFreeFunctionSignature free_function;
    DynamicArray* entities;
} ECS_System;

/**
 * @brief Creates a new ECS system with the provided parameters.
 *
 * @param id: Unique identifier for the system.
 * @param name: Name of the system.
 * @param data: Data specific to the system.
 * @param required_entity_components_bitset: Bitset representing the required components for the system.
 * @param update_function: Function to be called to update the system.
 *
 * @return A pointer to the newly created ECS system.
 */
ECS_System* ECS_System_Create(
    const uint64_t id,
    const char* const name,
    const void* const data,
    const uint64_t required_entity_components_bitset,
    const ECS_SystemUpdateFunctionSignature update_function,
    const ECS_SystemFreeFunctionSignature free_function
);

/**
 * @brief Prints information about an ECS system.
 *
 * @param registry_vector_index: Index of the system in the ECS registry vector.
 * @param ecs_system: Pointer to the system to print information for.
 */
void ECS_System_PrintInfo(const uint64_t registry_vector_index, const ECS_System* const ecs_system);

/**
 * @brief Frees the memory allocated for an ECS system.
 *
 * @param system: Pointer to the system to free.
 */
void ECS_System_Free(ECS_System** system);