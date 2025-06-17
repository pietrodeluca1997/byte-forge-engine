#pragma once

#include "ECS_Entity.h"
#include "ECS_ComponentType.h"
#include "ECS_System.h"

#include <ByteForgeMemory.h>

// Represents the ECS registry, which holds all entities, component types, and systems.
typedef struct ECS_Registry
{
    DynamicArray* entities;                       // Array of entities in the registry.
    DynamicArray* component_types;                // Array of component types in the registry.
    DynamicArray* systems;                        // Array of systems in the registry.
    DynamicArray* entities_components_bitsets;    // Bitset tracking components for each entity.
    DynamicArray* entities_to_kill;
    DynamicArray* entities_to_add;
    uint64_t entities_current_id;
} ECS_Registry;


/**
 * @brief Creates a new ECS registry.
 *
 * @param out_registry: Pointer to a pointer where the new registry will be stored.
 *
 * @return `true` if the registry was created successfully, `false` otherwise.
 */
bool ECS_Registry_Create(ECS_Registry** out_registry);

/**
 * @brief Prints the information of an ECS registry, including entities, component types, and systems.
 *
 * @param registry: Pointer to the ECS registry whose information is to be printed.
 */
void ECS_Registry_PrintInfo(const ECS_Registry* registry);

/**
 * @brief Updates all systems in the registry, passing the delta time for each update.
 *
 * @param registry: Pointer to the ECS registry to update.
 * @param delta_time: Time difference between the current and previous frame.
 */
void ECS_Registry_Update(ECS_Registry* registry, const double delta_time);

/**
 * @brief Frees the memory used by the ECS registry and its components.
 *
 * @param registry: Pointer to a pointer to the ECS registry to be freed.
 */
void ECS_Registry_Free(ECS_Registry** registry);