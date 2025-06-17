#pragma once

#include "MemoryAllocationCategory.h"

#include <stddef.h>

/**
 * @brief Allocates a block of memory for a specified category.
 *
 * @param block_size: Size of the memory block in bytes.
 * @param category: The category associated with the allocation.
 * @param file: The file where the allocation is happening.
 * @param line: The line number where the allocation is happening.
 * @param function: The function where the allocation is happening.
 *
 * @return Pointer to the allocated memory block or NULL if allocation fails.
 */
void* MemoryAllocator_Allocate(
    const size_t block_size,
    const EMemoryAllocationCategory category,
    const char* file,
    const int line,
    const char* function
);

/**
 * @brief Allocates memory for an array of blocks.
 *
 * @param count: Number of blocks to allocate.
 * @param block_size: Size of each block in bytes.
 * @param category: The category associated with the allocation.
 * @param file: The file where the allocation is happening.
 * @param line: The line number where the allocation is happening.
 * @param function: The function where the allocation is happening.
 *
 * @return Pointer to the allocated memory or NULL if allocation fails.
 */
void* MemoryAllocator_AllocateN(
    const size_t count,
    const size_t block_size,
    const EMemoryAllocationCategory category,
    const char* file,
    const int line,
    const char* function
);

/**
 * @brief Reallocates a memory block to a new size.
 *
 * @param memory_block: Pointer to the current memory block (must not be NULL).
 * @param new_block_size: The new size of the memory block in bytes.
 * @param previous_block_size: The previous size of the memory block in bytes.
 * @param category: The category associated with the reallocation.
 * @param file: The file where the reallocation is happening.
 * @param line: The line number where the reallocation is happening.
 * @param function: The function where the reallocation is happening.
 *
 * @return Pointer to the reallocated memory block or NULL if reallocation fails.
 */
void* MemoryAllocator_Reallocate(
    void** memory_block,
    const size_t new_block_size,
    const size_t previous_block_size,
    const EMemoryAllocationCategory category,
    const char* file,
    const int line,
    const char* function
);

/**
 * @brief Deallocates a memory block of a specified size for a given category.
 *
 * @param block_size: Size of the memory block being deallocated.
 * @param category: The category associated with the deallocation.
 * @param file: The file where the deallocation is happening.
 * @param line: The line number where the deallocation is happening.
 * @param function: The function where the deallocation is happening.
 */
void MemoryAllocator_Deallocate(
    const size_t block_size,
    const EMemoryAllocationCategory category,
    const char* file,
    const int line,
    const char* function
);

/**
 * @brief Frees a memory block and sets the pointer to NULL.
 *
 * @param memory_block: Pointer to the memory block (must not be NULL).
 * @param block_size: Size of the memory block being freed.
 * @param category: The category associated with the memory block.
 * @param file: The file where the free is happening.
 * @param line: The line number where the free is happening.
 * @param function: The function where the free is happening.
 */
void MemoryAllocator_Free(
    void** memory_block,
    const size_t block_size,
    const EMemoryAllocationCategory category,
    const char* file,
    const int line,
    const char* function
);
