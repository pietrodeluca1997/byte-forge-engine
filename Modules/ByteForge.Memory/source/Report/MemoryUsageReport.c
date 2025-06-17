#include "Memory/Reports/MemoryUsageReport.h"
#include "Memory/Structures/Dictionary.h"
#include "Memory/Allocation/MemoryAllocationMacros.h"

#include <ByteForgeLogging.h>

#include <stdlib.h>
#include <stdint.h>

static Dictionary* memory_usage_by_allocation_category = NULL;

void MemoryUsageReport_PrintInfo()
{
    if (!memory_usage_by_allocation_category)
    {
        LOG_ERROR("===========================================================");
        LOG_ERROR("             MEMORY USAGE REPORT UNAVAILABLE               ");
        LOG_ERROR("===========================================================");
        return;
    }

    LOG_NEW_LINE();

    LOG_INFO("===============================================");
    LOG_INFO("             MEMORY USAGE REPORT               ");
    LOG_INFO("===============================================");
    LOG_INFO("| %-28s | %-10s |", "Category", "Usage (Bytes)");
    LOG_INFO("===============================================");

    int64_t total_usage = 0;

    for (int64_t i = 0; i < MEMORY_ALLOCATION_CATEGORY_COUNT; i++)
    {
        int64_t* usage_by_category = Dictionary_Get(memory_usage_by_allocation_category, &i);
        int64_t usage = usage_by_category ? *usage_by_category : 0;
        total_usage += usage;

        LOG_INFO("| %-28s | %-13zu |", MemoryAllocation_GetCategoryName(i), usage);
    }

    LOG_INFO("===============================================");
    LOG_INFO("| %-28s | %-13zu |", "TOTAL USAGE", total_usage);
    LOG_INFO("===============================================");

    LOG_NEW_LINE();
}

bool MemoryUsageReport_Init()
{
    memory_usage_by_allocation_category = calloc(1, sizeof(Dictionary));

    if (!memory_usage_by_allocation_category)
    {
        LOG_FATAL("Error when trying to allocate memory for memory usage report dictionary.");
        return false;
    }

    memory_usage_by_allocation_category->capacity = MEMORY_ALLOCATION_CATEGORY_COUNT;
    memory_usage_by_allocation_category->count = 0;
    memory_usage_by_allocation_category->key_comparison_callback = MemoryAllocation_AreCategoriesEqual;
    memory_usage_by_allocation_category->key_size = sizeof(EMemoryAllocationCategory);
    memory_usage_by_allocation_category->value_size = sizeof(int64_t);

    void* keys = calloc(memory_usage_by_allocation_category->capacity, memory_usage_by_allocation_category->key_size);

    if (!keys)
    {
        LOG_FATAL("Error when trying to allocate memory for memory usage report dictionary keys.");
        return false;
    }

    void* values = calloc(memory_usage_by_allocation_category->capacity, memory_usage_by_allocation_category->value_size);

    if (!values)
    {
        LOG_FATAL("Error when trying to allocate memory for memory usage report dictionary values.");
        return false;
    }

    memory_usage_by_allocation_category->keys = keys;
    memory_usage_by_allocation_category->values = values;

    int64_t initial_value = 0;
    for (EMemoryAllocationCategory i = 0; i < MEMORY_ALLOCATION_CATEGORY_COUNT; i++)
    {
        if (!Dictionary_AddOrUpdate(memory_usage_by_allocation_category, &i, &initial_value, MEMORY_ALLOCATION_CATEGORY_MEMORY_USAGE_REPORT))
        {
            LOG_FATAL("Error when trying to add or update memory allocation category: %s.", MemoryAllocation_GetCategoryName(i));
            return false;
        }
    }

    MemoryAllocator_Allocate(sizeof(Dictionary), MEMORY_ALLOCATION_CATEGORY_MEMORY_USAGE_REPORT, __FILE__, __LINE__, __FUNCTION__);
    MemoryAllocator_Allocate(memory_usage_by_allocation_category->capacity * memory_usage_by_allocation_category->value_size, MEMORY_ALLOCATION_CATEGORY_MEMORY_USAGE_REPORT, __FILE__, __LINE__, __FUNCTION__);
    MemoryAllocator_Allocate(memory_usage_by_allocation_category->capacity * memory_usage_by_allocation_category->key_size, MEMORY_ALLOCATION_CATEGORY_MEMORY_USAGE_REPORT, __FILE__, __LINE__, __FUNCTION__);

    return true;
}

void MemoryUsageReport_TrackAllocation(const size_t allocation_size, const EMemoryAllocationCategory allocation_category, const char* file, const int line, const char* func)
{
    if (allocation_category == MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY)
    {
        LOG_TRACE(
            "Allocated %zu bytes in category %s at %s:%d (%s).",
            allocation_size,
            MemoryAllocation_GetCategoryName(allocation_category),
            file,
            line,
            func
        );
    }

    int64_t* current_usage = Dictionary_Get(memory_usage_by_allocation_category, &allocation_category);

	if (current_usage)
	{
		*current_usage += allocation_size;
	}   
}

void MemoryUsageReport_TrackDeallocation(const size_t deallocation_size, const EMemoryAllocationCategory deallocation_category, const char* file, const int line, const char* func)
{
    if (deallocation_category == MEMORY_ALLOCATION_CATEGORY_ECS_ENTITY)
    {
        LOG_TRACE(
            "Deallocated %zu bytes in category %s at %s:%d (%s).",
            deallocation_size,
            MemoryAllocation_GetCategoryName(deallocation_category),
            file,
            line,
            func
        );
    }

    int64_t* current_usage = Dictionary_Get(memory_usage_by_allocation_category, &deallocation_category);

	if (current_usage)
	{
		*current_usage -= deallocation_size;
	}
}

void MemoryUsageReport_Exit()
{
    if (!memory_usage_by_allocation_category)
    {
        LOG_WARNING("An attempt was made to close the Memory Usage Report but it was not initialized.");
        return;
    }

    if (memory_usage_by_allocation_category->keys != NULL)
    {
        free(memory_usage_by_allocation_category->keys);
    }
    if (memory_usage_by_allocation_category->values != NULL)
    {
        free(memory_usage_by_allocation_category->values);
    }

    free(memory_usage_by_allocation_category);
}