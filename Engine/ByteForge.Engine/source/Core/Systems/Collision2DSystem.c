#include "ByteForgeEngine/Core/Systems/Collision2DSystem.h"
#include <ByteForgeEngine/Core/Components/Transform2DComponent.h>
#include <ByteForgeEngine/Core/Components/BoxCollider2DComponent.h>
#include <ByteForgeEngine/Core/Components/Physics2DComponent.h>
#include <lauxlib.h>

static bool Collision2DSystem_CheckCollisionAABB(const Transform2DComponent* a, const Transform2DComponent* b)
{
    float a_left = a->position.x - a->size.x / 2.0f;
    float a_right = a->position.x + a->size.x / 2.0f;
    float a_top = a->position.y + a->size.y / 2.0f;
    float a_bottom = a->position.y - a->size.y / 2.0f;

    float b_left = b->position.x - b->size.x / 2.0f;
    float b_right = b->position.x + b->size.x / 2.0f;
    float b_top = b->position.y + b->size.y / 2.0f;
    float b_bottom = b->position.y - b->size.y / 2.0f;

    return (a_left < b_right && a_right > b_left &&
        a_top > b_bottom && a_bottom < b_top);
}

Collision2DSystem* Collision2DSystem_New(ECS_ComponentType* transform_2d_component, ECS_ComponentType* box_collider_2d_component, ECS_ComponentType* physics_2d_component, ScriptingSubsystem* scripting_subsystem)
{
    Collision2DSystem* system = ALLOC(Collision2DSystem, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);

    if (!system) return NULL;

    system->transform_2d_component = transform_2d_component;
    system->box_collider_2d_component = box_collider_2d_component;
    system->physics_2d_component = physics_2d_component;
    system->scripting_subsystem = scripting_subsystem;

    return system;
}

void Collision2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time)
{
    Collision2DSystem* system_2d_data = (Collision2DSystem*)self->data;

    for (uint64_t i = 0; i < self->entities->count; i++)
    {
        ECS_Entity* entity = DynamicArray_Get(self->entities, i);
        uint64_t* entity_transform_component_index = Dictionary_Get(system_2d_data->transform_2d_component->entity_id_to_array_index_map, &entity->id);

        if (!entity_transform_component_index) continue;

        Transform2DComponent* entity_transform = DynamicArray_Get(system_2d_data->transform_2d_component->data_array, *entity_transform_component_index);

        uint64_t* entity_collision_2d_index = Dictionary_Get(system_2d_data->box_collider_2d_component->entity_id_to_array_index_map, &entity->id);       

        if (!entity_collision_2d_index) continue;

        BoxCollider2DComponent* box_collider_2d_component = DynamicArray_Get(system_2d_data->box_collider_2d_component->data_array, *entity_collision_2d_index);

        for (uint64_t j = 0; j < self->entities->count; j++)
        {
            ECS_Entity* entity_two = DynamicArray_Get(self->entities, j);
                
            if (entity->id == entity_two->id) continue;

            uint64_t* entity_two_transform_component_index = Dictionary_Get(system_2d_data->transform_2d_component->entity_id_to_array_index_map, &entity_two->id);

            if (!entity_two_transform_component_index) continue;

            Transform2DComponent* entity_two_transform = DynamicArray_Get(system_2d_data->transform_2d_component->data_array, *entity_two_transform_component_index);

            uint64_t* entity_two_collision_2d_index = Dictionary_Get(system_2d_data->box_collider_2d_component->entity_id_to_array_index_map, &entity_two->id);

            if (!entity_two_collision_2d_index) continue;
            BoxCollider2DComponent* entity_two_box_collider_2d_component = DynamicArray_Get(system_2d_data->box_collider_2d_component->data_array, *entity_two_collision_2d_index);
        
            if (Collision2DSystem_CheckCollisionAABB(entity_transform, entity_two_transform)) {
                               
                if (box_collider_2d_component->on_collision_script_function != LUA_NOREF)
                {
                    lua_rawgeti(system_2d_data->scripting_subsystem->lua_state, LUA_REGISTRYINDEX, box_collider_2d_component->on_collision_script_function);
                    lua_pushinteger(system_2d_data->scripting_subsystem->lua_state, entity->id);
                    lua_pushinteger(system_2d_data->scripting_subsystem->lua_state, entity_two->id);
                                        
                    lua_pcall(system_2d_data->scripting_subsystem->lua_state, 2, 0, 0);
                }
                else if (entity_two_box_collider_2d_component->on_collision_script_function != LUA_NOREF)
                {
                    lua_rawgeti(system_2d_data->scripting_subsystem->lua_state, LUA_REGISTRYINDEX, entity_two_box_collider_2d_component->on_collision_script_function);
                    lua_pushinteger(system_2d_data->scripting_subsystem->lua_state, entity_two->id);
                    lua_pushinteger(system_2d_data->scripting_subsystem->lua_state, entity->id);

                    lua_pcall(system_2d_data->scripting_subsystem->lua_state, 2, 0, 0);
                }

                uint64_t* entity_one_physics_2d_index = Dictionary_Get(system_2d_data->physics_2d_component->entity_id_to_array_index_map, &entity->id);

                if (entity_one_physics_2d_index)
                {
                    Physics2DComponent* entity_one_physics_2d = DynamicArray_Get(system_2d_data->physics_2d_component->data_array, *entity_one_physics_2d_index);

                    if (entity_transform->position.x < entity_two_transform->position.x)
                    {
                        entity_transform->position.x -= 1;
                    }
                    else
                    {
                        entity_transform->position.x += 1;
                    }

                    if (entity_transform->position.y < entity_two_transform->position.y)
                    {
                        entity_transform->position.y -= 1;
                    }
                    else
                    {
                        entity_transform->position.y += 1;
                    }
                }

                
                uint64_t* entity_two_physics_2d_index = Dictionary_Get(system_2d_data->physics_2d_component->entity_id_to_array_index_map, &entity_two->id);

                if (entity_two_physics_2d_index)
                {
                    Physics2DComponent* entity_two_physics_2d = DynamicArray_Get(system_2d_data->physics_2d_component->data_array, *entity_two_physics_2d_index);

                    if (entity_two_transform->position.x < entity_transform->position.x)
                    {
                        entity_two_transform->position.x -= 1;
                    }
                    else
                    {
                        entity_two_transform->position.x += 1;
                    }

                    if (entity_two_transform->position.y < entity_transform->position.y)
                    {
                        entity_two_transform->position.y -= 1;
                    }
                    else {
                        entity_two_transform->position.y += 1;
                    }
                }
            }
        }
    }
}

void Collision2DSystem_Free(Collision2DSystem** collision_2d_system)
{
    if (!collision_2d_system || !*collision_2d_system)
    {
        return;
    }

    FREE(collision_2d_system, sizeof(Collision2DSystem), MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
}
