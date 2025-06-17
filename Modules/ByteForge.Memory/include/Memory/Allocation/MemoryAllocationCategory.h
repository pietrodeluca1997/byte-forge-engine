#pragma once

#include <stdbool.h>

/**
 * @brief Enum representing different categories for memory allocation.
 */
typedef enum EMemoryAllocationCategory
{
	MEMORY_ALLOCATION_CATEGORY_MEMORY_USAGE_REPORT,
	MEMORY_ALLOCATION_CATEGORY_SCRIPTING_SUBSYSTEM,
	MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY,
	MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY_COMPONENTS_BITSET,
	MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE,
	MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM,
	MEMORY_ALLOCATION_CATEGORY_ECS_REGISTRY,
	MEMORY_ALLOCATION_CATEGORY_ENGINE_APPLICATION,
	MEMORY_ALLOCATION_CATEGORY_STRING,
	MEMORY_ALLOCATION_CATEGORY_GAME_LEVEL,
	MEMORY_ALLOCATION_CATEGORY_PLATFORM,
	MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER,

	MEMORY_ALLOCATION_CATEGORY_COUNT
} EMemoryAllocationCategory;

/**
 * @brief Names corresponding to each memory allocation category.
 *
 * Use this array to get the human-readable name of a category.
 * Ensure `MEMORY_ALLOCATION_CATEGORY_COUNT` matches the number of entries in the enum.
 */
extern const char* const MEMORY_ALLOCATION_CATEGORY_NAMES[MEMORY_ALLOCATION_CATEGORY_COUNT];

/**
 * @brief Retrieves the name of the specified memory allocation category.
 *
 * @param category: The memory allocation category to get the name for.
 *
 * @return Pointer to a string representing the name of the category, or NULL if invalid.
 */
const char* const MemoryAllocation_GetCategoryName(const EMemoryAllocationCategory category);

/**
 * @brief Compares two memory allocation categories for equality.
 *
 * @param first: Pointer to the first category.
 * @param second: Pointer to the second category.
 *
 * @return true if both categories are equal, false otherwise.
 * If either pointer is NULL, returns false.
 */
bool MemoryAllocation_AreCategoriesEqual(const EMemoryAllocationCategory* const first, const EMemoryAllocationCategory* const second);