#include "ECS/ECS_ComponentType.h"
#include "ECS/ECS_Entity.h"

#include <ByteForgeLogging.h>
#include <ByteForgeMemory.h>

ECS_ComponentType* ECS_ComponentType_Create(const uint64_t id, const size_t size, const char* const name)
{
    ECS_ComponentType* component_type = ALLOC(ECS_ComponentType, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

    if (!component_type) return NULL;

    component_type->id = id;
    component_type->size = size;
    component_type->name = (char*) name;

    if (
        !DynamicArray_Initialize(&component_type->data_array, size, 10, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE) ||
        !Dictionary_Initialize(&component_type->entity_id_to_array_index_map, sizeof(uint64_t), sizeof(uint64_t), 10, ECS_Entity_IsEqual, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE)
    )
    {
        ECS_ComponentType_Free(&component_type);
        return NULL;
    }

    return component_type;
}

void ECS_ComponentType_PrintInfo(const size_t registry_array_index, const ECS_ComponentType* const component_type)
{
    LOG_DEBUG("================== ECS Component Type Debug ==================");
    LOG_DEBUG("Component Type ID            : %llu", component_type->id);
    LOG_DEBUG("Component Type Size          : %zu bytes", component_type->size);
    LOG_DEBUG("Component Type Name          : %s", component_type->name ? component_type->name : "NULL");
    LOG_DEBUG("Component Array Size         : %d", component_type->data_array ? component_type->data_array->count : 0);
    LOG_DEBUG("Entity-Index Map Entries     : %d", component_type->entity_id_to_array_index_map ? component_type->entity_id_to_array_index_map->count : 0);

    if (component_type->entity_id_to_array_index_map)
    {
        Dictionary* dictionary = component_type->entity_id_to_array_index_map;

        for (size_t i = 0; i < dictionary->count; i++)
        {
            uint64_t* keys = dictionary->keys;
            uint64_t* values = dictionary->values;

            LOG_DEBUG("Entity ID: %llu -> Vector Index: %llu", keys[i], values[i]);
        }
    }

    LOG_DEBUG("==============================================================");

    LOG_NEW_LINE();
}

void ECS_ComponentType_Free(ECS_ComponentType** component_type)
{
    if (!component_type || !*component_type || !(*component_type)->data_array) return;

    for (uint64_t i = 0; i < (*component_type)->data_array->count; i++)
    {
        void* component_data = DynamicArray_Get((*component_type)->data_array, i);

        if ((*component_type)->free_function)
        {
            (*component_type)->free_function(&component_data);
        }
    }

    DynamicArray_Free(&(*component_type)->data_array, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
    Dictionary_Free(&(*component_type)->entity_id_to_array_index_map, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

    FREE(component_type, sizeof(ECS_ComponentType), MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
}
