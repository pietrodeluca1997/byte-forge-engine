#include "ByteForgeEngine/Core/Systems/Render2DSystem.h"
#include "ByteForgeEngine/Core/Components/Transform2DComponent.h"
#include "ByteForgeEngine/Core/Components/Sprite2DComponent.h"
#include "ByteForgeEngine/Core/Components/AnimatedSprite2DComponent.h"
#include "ByteForgeEngine/Core/Components/ParallaxSprite2DComponent.h"

#include <Memory/Allocation/MemoryAllocationMacros.h>
#include <Memory/Helpers/MemoryStructureHelper.h>
#include <ByteForgeLogging.h>
#include <ByteForgeEngine/Core/Components/BoxCollider2DComponent.h>

Render2DSystem* Render2DSystem_New(SDL_Renderer* sdl_renderer, ECS_ComponentType* transform_2d_component, ECS_ComponentType* sprite_2d_component, ECS_ComponentType* animated_sprite_2d_component, ECS_ComponentType* parallax_sprite_2d_component, ECS_ComponentType* box_collider_2d_component)
{
    Render2DSystem* system = ALLOC(Render2DSystem, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);

    if (!system) return NULL;

    system->sdl_renderer = sdl_renderer;
    system->transform_2d_component = transform_2d_component;
    system->sprite_2d_component = sprite_2d_component;
    system->animated_sprite_2d_component = animated_sprite_2d_component;
    system->parallax_sprite_2d_component = parallax_sprite_2d_component;
    system->box_collider_2d_component = box_collider_2d_component;

    return system;
}

void Render2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time)
{
    Render2DSystem* render2d_data = (Render2DSystem*)self->data;

    SDL_Renderer* renderer = (SDL_Renderer*)render2d_data->sdl_renderer;

    SDL_RenderClear(renderer);

    for (uint64_t i = 0; i < self->entities->count; i++)
    {
        ECS_Entity* entity = DynamicArray_Get(self->entities, i);

        Transform2DComponent* entity_transform = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(render2d_data->transform_2d_component->entity_id_to_array_index_map, render2d_data->transform_2d_component->data_array, entity->id);

        uint64_t* entity_sprite_component_index = Dictionary_Get(render2d_data->sprite_2d_component->entity_id_to_array_index_map, &entity->id);
        uint64_t* entity_animated_sprite_component_index = Dictionary_Get(render2d_data->animated_sprite_2d_component->entity_id_to_array_index_map, &entity->id);
        uint64_t* entity_parallax_component_index = Dictionary_Get(render2d_data->parallax_sprite_2d_component->entity_id_to_array_index_map, &entity->id);
        uint64_t* entity_box_collider_index = Dictionary_Get(render2d_data->box_collider_2d_component->entity_id_to_array_index_map, &entity->id);

        if (entity_sprite_component_index)
        {
            Sprite2DComponent* entity_sprite = DynamicArray_Get(render2d_data->sprite_2d_component->data_array, *entity_sprite_component_index);

            if (entity_sprite)
            {
                SDL_FRect rect =
                {
                    .w = entity_sprite->texture_size.x,
                    .h = entity_sprite->texture_size.y,
                    .x = entity_transform->position.x,
                    .y = entity_transform->position.y
                };

                SDL_RenderTexture(renderer, entity_sprite->texture, NULL, &rect);
            }
        }
        else if (entity_animated_sprite_component_index)
        {
            AnimatedSprite2DComponent* entity_animated_sprite = DynamicArray_Get(render2d_data->animated_sprite_2d_component->data_array, *entity_animated_sprite_component_index);

            entity_animated_sprite->current_frame += entity_animated_sprite->desired_frame_rate * delta_time;

            if (entity_animated_sprite->current_frame >= entity_animated_sprite->animation_textures->count)
            {
                entity_animated_sprite->current_frame = fmod(entity_animated_sprite->current_frame, entity_animated_sprite->animation_textures->count);
            }

            SDL_Texture* current_texture = *(SDL_Texture**)DynamicArray_Get(
                entity_animated_sprite->animation_textures,
                entity_animated_sprite->current_frame
            );

            SDL_FRect rect = {
                entity_transform->position.x,
                entity_transform->position.y,
                entity_transform->size.x,
                entity_transform->size.y
            };

            SDL_RenderTexture(renderer, current_texture, NULL, &rect);
        }
        else if (entity_parallax_component_index)
        {
            ParallaxSprite2DComponent* entity_parallax_sprite = DynamicArray_Get(render2d_data->parallax_sprite_2d_component->data_array, *entity_parallax_component_index);

            for (uint64_t j = 0; j < entity_parallax_sprite->animation_textures->count; j++)
            {
                ParallaxTexture* parallax_texture = DynamicArray_Get(entity_parallax_sprite->animation_textures, j);

                parallax_texture->offset.x -= entity_parallax_sprite->scroll_speed;

                if (parallax_texture->offset.x < -entity_transform->size.x)
                {
                    parallax_texture->offset.x = (entity_parallax_sprite->animation_textures->count - 1) * entity_transform->size.x;
                }

                SDL_FRect rect = {
                    entity_transform->position.x + parallax_texture->offset.x,
                    entity_transform->position.y + parallax_texture->offset.y,
                    entity_transform->size.x,
                    entity_transform->size.y
                };

                SDL_RenderTexture(render2d_data->sdl_renderer, parallax_texture->texture, NULL, &rect);
            }
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_FRect rect =
            {
                entity_transform->position.x,
                entity_transform->position.y,
                entity_transform->size.x,
                entity_transform->size.y
            };

            SDL_RenderFillRect(renderer, &rect);
        }

        if (entity_box_collider_index)
        {
            BoxCollider2DComponent* box_collider = DynamicArray_Get(render2d_data->box_collider_2d_component->data_array, *entity_box_collider_index);
            SDL_FRect rect =
            {
                entity_transform->position.x,
                entity_transform->position.y,
                box_collider->collision_box.x,
                box_collider->collision_box.y,
            };

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

            SDL_RenderRect(renderer, &rect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    }
}

void Render2DSystem_Free(Render2DSystem** render_2d_system)
{
    if (!render_2d_system || !*render_2d_system)
    {
        return;
    }

    FREE(render_2d_system, sizeof(Render2DSystem), MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
}
