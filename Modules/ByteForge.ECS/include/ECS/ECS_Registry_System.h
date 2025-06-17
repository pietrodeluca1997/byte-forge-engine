#pragma once

#include "ECS_Registry.h"

/**
 * @brief Creates and registers a system within the ECS registry.
 * This system will be associated with the provided component bitset and update function.
 *
 * @param registry: Pointer to the ECS registry where the system will be registered.
 * @param required_entity_component_bitset: Bitset representing the required components for the system.
 * @param name: Name of the system being created.
 * @param update_function: Pointer to the function that will update the system every frame.
 * @param data: Additional data that might be passed to the update function.
 *
 * @return true if the system was successfully created and registered, false otherwise.
 */
bool ECS_Registry_CreateSystem(
    ECS_Registry* registry,
    const uint64_t required_entity_component_bitset,
    const char* const name,
    const ECS_SystemUpdateFunctionSignature update_function,
    const ECS_SystemFreeFunctionSignature free_function,
    const void* const data
);
