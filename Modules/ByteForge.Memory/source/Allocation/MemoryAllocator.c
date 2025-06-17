#include "Memory/Allocation/MemoryAllocator.h"
#include "Memory/Reports/MemoryUsageReport.h"

#include <stdlib.h>

void* MemoryAllocator_Allocate(const size_t block_size, const EMemoryAllocationCategory category, const char* file, int line, const char* function)
{
    void* memory_block = calloc(1, block_size);

    MemoryUsageReport_TrackAllocation(block_size, category, file, line, function);

    return memory_block;
}

void* MemoryAllocator_AllocateN(const size_t count, const size_t block_size, const EMemoryAllocationCategory category, const char* file, int line, const char* function)
{
    void* memory_block = calloc(count, block_size);

    MemoryUsageReport_TrackAllocation(block_size * count, category, file, line, function);

    return memory_block;
}

void* MemoryAllocator_Reallocate(void** memory_block, const size_t new_block_size, const size_t previous_block_size, const EMemoryAllocationCategory category, const char* file, int line, const char* function)
{
    if (!memory_block || !*memory_block) return NULL;

    void* new_memory_block = realloc((char*)*memory_block, new_block_size);

    if (!new_memory_block)
    {
        return NULL;
    }

    bool size_increased = new_block_size > previous_block_size;

    if (size_increased)
    {
        MemoryUsageReport_TrackAllocation(new_block_size - previous_block_size, category, file, line, function);
    }
    else
    {
        MemoryUsageReport_TrackDeallocation(previous_block_size - new_block_size, category, file, line, function);
    }

    return new_memory_block;
}

void MemoryAllocator_Deallocate(const size_t block_size, const EMemoryAllocationCategory category, const char* file, int line, const char* function)
{
    MemoryUsageReport_TrackDeallocation(block_size, category, file, line, function);
}

void MemoryAllocator_Free(void** memory_block, const size_t block_size, const EMemoryAllocationCategory category, const char* file, int line, const char* function)
{
    if (!memory_block || !*memory_block)
    {
        return;
    }

    free(*memory_block);
    *memory_block = NULL;

    MemoryUsageReport_TrackDeallocation(block_size, category, file, line, function);
}
