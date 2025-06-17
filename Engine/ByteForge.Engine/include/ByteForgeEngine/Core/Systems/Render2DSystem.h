#pragma once

#define RENDER_2D_SYSTEM_NAME "Render2DSystem"

#include <SDL3/SDL.h>

#include "ECS/ECS_Registry.h"
#include "ECS/ECS_System.h"
#include "ECS/ECS_ComponentType.h"

/**
 * @brief Represents a system that handles 2D rendering in the game engine.
 *
 * The `Render2DSystem` is responsible for rendering 2D entities to the screen. It processes entities
 * that have `Transform2DComponent`to update their visual representation in the game world.
 */
typedef struct Render2DSystem
{
    SDL_Renderer* sdl_renderer;
    ECS_ComponentType* transform_2d_component;
    ECS_ComponentType* sprite_2d_component;
    ECS_ComponentType* animated_sprite_2d_component;
    ECS_ComponentType* parallax_sprite_2d_component;
    ECS_ComponentType* box_collider_2d_component;
} Render2DSystem;

/**
 * @brief Creates a new Render2DSystem instance.
 *
 * @param sdl_renderer: The SDL_Renderer used for rendering 2D content.
 * @param transform_2d_component: The `Transform2DComponent` used to handle position and size information.
 *
 * @return A pointer to the newly created `Render2DSystem` instance.
 */
Render2DSystem* Render2DSystem_New(SDL_Renderer* sdl_renderer, ECS_ComponentType* transform_2d_component, ECS_ComponentType* sprite_2d_component, ECS_ComponentType* animated_sprite_2d_component, ECS_ComponentType* parallax_sprite_2d_component, ECS_ComponentType* box_collider_2d_component);

/**
 * @brief Updates the `Render2DSystem` by rendering entities in the ECS registry.
 *
 * This function processes entities that have both `Transform2DComponent` and `Sprite2DComponent`
 * and renders them to the screen using the `SDL_Renderer`.
 *
 * @param registry: The ECS registry containing all entities and their components.
 * @param self: The current `Render2DSystem` instance to be updated.
 */
void Render2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time);

void Render2DSystem_Free(Render2DSystem** render_2d_system);