#pragma once

#define BOX_COLLIDER_2D_COMPONENT_NAME "BoxCollider2DComponent"

#include <Math/Vector2.h>

typedef struct BoxCollider2DComponent
{
    Vector2 collision_box;
    int on_collision_script_function;
} BoxCollider2DComponent;