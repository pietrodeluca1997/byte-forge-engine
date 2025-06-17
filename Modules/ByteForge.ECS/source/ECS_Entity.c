#include "ECS/ECS_Entity.h"

#include <ByteForgeLogging.h>

ECS_Entity ECS_Entity_Create(uint64_t id)
{
    ECS_Entity new_entity = { .id = id };
    return new_entity;
}

bool ECS_Entity_IsEqual(const ECS_Entity* first, const ECS_Entity* second)
{    
    if (!first || !second) return false;

    return first->id == second->id;
}

void ECS_Entity_PrintInfo(const size_t registry_index, const ECS_Entity* entity)
{
    LOG_DEBUG("==================== ECS Entity Debug ====================");
    LOG_DEBUG("Index           : %llu", registry_index);
    LOG_DEBUG("Entity ID       : %llu", entity->id);
    LOG_DEBUG("==========================================================");

    LOG_NEW_LINE();
}