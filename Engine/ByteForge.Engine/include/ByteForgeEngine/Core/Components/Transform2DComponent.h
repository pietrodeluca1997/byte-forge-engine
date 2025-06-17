#pragma once

#define TRANSFORM_2D_COMPONENT_NAME "Transform2DComponent"

#include <Math/Vector2.h>

/**
 * @brief Represents a 2D transformation component in the game world.
 *
 * The `Transform2DComponent` structure holds information about an entity's position and size
 * in a 2D space. It is typically used for entities that need to be rendered or interacted with
 * in a 2D coordinate system, such as sprites or other 2D objects.
 */
typedef struct Transform2DComponent
{
    /**
     * @brief The position of the entity in 2D space.
     *
     * This defines the coordinates of the entity, typically used for rendering or movement calculations.
     */
	Vector2 position;

    /**
     * @brief The size of the entity in 2D space.
     *
     * This represents the width and height of the entity, used for scaling or rendering purposes.
     */
	Vector2 size;
} Transform2DComponent;