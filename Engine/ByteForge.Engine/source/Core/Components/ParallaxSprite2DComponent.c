#include "ByteForgeEngine/Core/Components/ParallaxSprite2DComponent.h"

void ParallaxSprite2DComponent_Free(ParallaxSprite2DComponent** component_data)
{
	ParallaxSprite2DComponent* component_data_deref = *component_data;

	DynamicArray_Free(&component_data_deref->animation_textures, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);
}