#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Represents an entity in the ECS (Entity-Component-System) framework.
typedef struct ECS_Entity
{
    uint64_t id;
} ECS_Entity;

/**
 * @brief Creates a new ECS_Entity with a specified unique identifier.
 *
 * @param id: The unique identifier for the new entity.
 *
 * @return The newly created ECS_Entity.
 */
ECS_Entity ECS_Entity_Create(const uint64_t id);

/**
 * @brief Compares two ECS_Entity instances to check if they are equal.
 *
 * @param first: Pointer to the first ECS_Entity to compare.
 * @param second: Pointer to the second ECS_Entity to compare.
 *
 * @return `true` if the entities are equal (i.e., have the same ID), `false` otherwise.
 */
bool ECS_Entity_IsEqual(const ECS_Entity* first, const ECS_Entity* second);

/**
 * @brief Prints the information of a specified ECS_Entity.
 *
 * @param registry_index: The index of the entity in the ECS registry (for context).
 * @param entity: Pointer to the ECS_Entity whose information is to be printed.
 */
void ECS_Entity_PrintInfo(const size_t registry_index, const ECS_Entity* entity);