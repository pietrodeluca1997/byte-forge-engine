#include "Memory/Allocation/MemoryAllocationCategory.h"

#include <stdlib.h>

#include <ByteForgeLogging.h>

static const char* const MEMORY_ALLOCATION_CATEGORY_NAMES[] =
{
    [ MEMORY_ALLOCATION_CATEGORY_MEMORY_USAGE_REPORT ] = "Memory Usage Report",
    [ MEMORY_ALLOCATION_CATEGORY_SCRIPTING_SUBSYSTEM ] = "Scripting Subsystem",
    [ MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY ] = "ECS Entity",
    [ MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY_COMPONENTS_BITSET ] = "ECS Entity Components Bitset",
    [ MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE ] = "ECS Component Type",
    [ MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM ] = "ECS System",
    [ MEMORY_ALLOCATION_CATEGORY_ECS_REGISTRY ] = "ECS Registry",
    [ MEMORY_ALLOCATION_CATEGORY_ENGINE_APPLICATION ] = "Engine Application",
    [ MEMORY_ALLOCATION_CATEGORY_STRING ] = "String",
    [ MEMORY_ALLOCATION_CATEGORY_GAME_LEVEL ] = "Game Level",
    [ MEMORY_ALLOCATION_CATEGORY_PLATFORM ] = "Platform",
    [ MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER ] = "Asset Manager"
};

const char* const MemoryAllocation_GetCategoryName(const EMemoryAllocationCategory category)
{
    if (category >= 0 && category < MEMORY_ALLOCATION_CATEGORY_COUNT)
    {
        return MEMORY_ALLOCATION_CATEGORY_NAMES[category];
    }

    LOG_ERROR("Invalid memory allocation category: %d.", category);
    return NULL;
}

bool MemoryAllocation_AreCategoriesEqual(const EMemoryAllocationCategory* first, const EMemoryAllocationCategory* second)
{
    if (!first || !second)
    {
        LOG_WARNING("NULL pointer passed to memory allocation categories equality check.");
        return false;
    }

    return *first == *second;
}