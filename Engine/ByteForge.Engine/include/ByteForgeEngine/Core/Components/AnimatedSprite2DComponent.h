#pragma once

#define ANIMATED_SPRITE_2D_COMPONENT_NAME "AnimatedSprite2DComponent"

#include <ByteForgeMemory.h>

typedef struct AnimatedSprite2DComponent
{
    DynamicArray* animation_textures;
    float current_frame;
    float desired_frame_rate;
} AnimatedSprite2DComponent;

void AnimatedSprite2DComponent_Free(AnimatedSprite2DComponent** component_data);