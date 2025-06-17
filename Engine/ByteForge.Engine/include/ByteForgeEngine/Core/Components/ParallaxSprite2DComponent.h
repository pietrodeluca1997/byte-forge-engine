#pragma once

#define PARALLAX_SPRITE_2D_COMPONENT_NAME "ParallaxSprite2DComponent"

#include <ByteForgeMemory.h>

#include <SDL3/SDL.h>
#include <Math/Vector2.h>

typedef struct ParallaxTexture
{
    SDL_Texture* texture;
    uint32_t texture_id;
    Vector2 offset;
} ParallaxTexture;

typedef struct ParallaxSprite2DComponent
{
    DynamicArray* animation_textures;
    float scroll_speed;
} ParallaxSprite2DComponent;

void ParallaxSprite2DComponent_Free(ParallaxSprite2DComponent** component_data);