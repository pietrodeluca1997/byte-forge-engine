#pragma once

#include "ECS_Registry.h"

/**
 * @brief Adds a component to an entity in the registry.
 *
 * @param registry: Pointer to the ECS registry where the component will be added.
 * @param component_type: Pointer to the component type to be added.
 * @param component: Pointer to the component data.
 * @param entity: The entity to which the component will be added.
 */
void ECS_Registry_AddComponentToEntity(
    ECS_Registry* registry,
    const ECS_ComponentType* const component_type,
    const void* const component,
    const ECS_Entity entity
);

/**
 * @brief Registers a new component type in the ECS registry.
 *
 * @param registry: Pointer to the ECS registry where the component type will be registered.
 * @param size: Size of the component type.
 * @param name: Name of the component type.
 *
 * @return `true` if the component type was successfully registered, `false` otherwise.
 */
bool ECS_Registry_RegisterComponentType(
    ECS_Registry* registry,
    const size_t size,
    const char* const name,
    const ECS_ComponentTypeFreeFunctionSignature free_function
);

/**
 * @brief Retrieves a component type reference from the registry by its name.
 *
 * @param registry: Pointer to the ECS registry from which to retrieve the component type.
 * @param name: Name of the component type to retrieve.
 *
 * @return A pointer to the component type, or `NULL` if not found.
 */
ECS_ComponentType* ECS_Registry_GetComponentTypeReferenceByName(
    const ECS_Registry* registry,
    const char* const name
);
