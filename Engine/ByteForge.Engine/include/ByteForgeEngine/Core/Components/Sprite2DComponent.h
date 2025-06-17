#pragma once

#define SPRITE_2D_COMPONENT_NAME "Sprite2DComponent"

#include <stdint.h>

#include <SDL3/SDL.h>

#include <Math/Vector2.h>

typedef struct Sprite2DComponent
{
    Vector2 texture_size;
    SDL_Texture* texture;
    uint32_t texture_id;
} Sprite2DComponent;