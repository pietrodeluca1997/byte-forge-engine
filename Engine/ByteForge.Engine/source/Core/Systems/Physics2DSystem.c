#include "ByteForgeEngine/Core/Systems/Physics2DSystem.h"
#include "ByteForgeEngine/Core/Components/Transform2DComponent.h"
#include "ByteForgeEngine/Core/Components/Physics2DComponent.h"

#include <Memory/Helpers/MemoryStructureHelper.h>

Physics2DSystem* Physics2DSystem_New(ECS_ComponentType* transform_2d_component, ECS_ComponentType* physics_2d_component)
{
    Physics2DSystem* system = ALLOC(Physics2DSystem, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);

    if (!system) return NULL;

    system->transform_2d_component = transform_2d_component;
    system->physics_2d_component = physics_2d_component;

    return system;
}

void Physics2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time)
{
    Physics2DSystem* physics_2d_data = (Physics2DSystem*)self->data;

    for (uint64_t i = 0; i < self->entities->count; i++)
    {
        ECS_Entity* entity = DynamicArray_Get(self->entities, i);

        Transform2DComponent* entity_transform = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(physics_2d_data->transform_2d_component->entity_id_to_array_index_map, physics_2d_data->transform_2d_component->data_array, entity->id);
        Physics2DComponent* entity_physics = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(physics_2d_data->physics_2d_component->entity_id_to_array_index_map, physics_2d_data->physics_2d_component->data_array, entity->id);
        
        entity_transform->position.x += entity_physics->velocity.x * delta_time;
        entity_transform->position.y += entity_physics->velocity.y * delta_time;
    }
}

void Physics2DSystem_Free(Physics2DSystem** physics_2d_system)
{
    if (!physics_2d_system || !*physics_2d_system)
    {
        return;
    }

    FREE(physics_2d_system, sizeof(Physics2DSystem), MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
}
