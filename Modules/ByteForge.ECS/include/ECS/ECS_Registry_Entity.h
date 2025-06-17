#pragma once

#include "ECS_Registry.h"

/**
 * @brief Creates a new entity and adds it to the ECS registry.
 *
 * @param registry: Pointer to the ECS registry where the entity will be created.
 * @param out_entity: Pointer to store the created entity.
 */
bool ECS_Registry_CreateEntity(
    ECS_Registry* registry,
    ECS_Entity* out_entity
);

/**
 * @brief Publishes an entity to the ECS registry, making it active and ready for use.
 *
 * @param registry: Pointer to the ECS registry where the entity will be published.
 * @param entity: The entity to be published.
 */
void ECS_Registry_PublishEntity(
    ECS_Registry* registry,
    const ECS_Entity entity
);

void ECS_Registry_SpawnEntities(ECS_Registry* registry);

void ECS_Registry_SpawnEntity(
    ECS_Registry* registry,
    const ECS_Entity entity
);

void ECS_Registry_AddEntityToKillQueue(ECS_Registry* registry, ECS_Entity entity);

void ECS_Registry_KillEntities(ECS_Registry* registry);

/**
 * @brief Kills (removes) an entity from the ECS registry and frees associated resources.
 *
 * @param registry: Pointer to the ECS registry where the entity will be removed.
 * @param entity: The entity to be removed.
 */
void ECS_Registry_KillEntity(
    ECS_Registry* registry,
    const ECS_Entity entity
);
