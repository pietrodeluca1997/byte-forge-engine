#include "ByteForgeEngine/Core/Components/AnimatedSprite2DComponent.h"

void AnimatedSprite2DComponent_Free(AnimatedSprite2DComponent** component_data)
{
	AnimatedSprite2DComponent* component_data_deref = *component_data;

	DynamicArray_Free(&component_data_deref->animation_textures, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
}