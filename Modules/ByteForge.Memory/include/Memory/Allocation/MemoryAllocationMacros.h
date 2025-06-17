#pragma once

#include "MemoryAllocator.h"

/**
 * @brief Macro to allocate memory for a specific type and category.
 *
 * @param type: The type of object to allocate.
 * @param category: The category associated with the allocation.
 * @param file: The file where the allocation is happening.
 * @param line: The line number where the allocation is happening.
 * @param function: The function where the allocation is happening.
 *
 * @return Pointer to the allocated memory block.
 */
#define ALLOC(type, category) MemoryAllocator_Allocate(sizeof(type), category, __FILE__, __LINE__, __FUNCTION__)
#define ALLOC_SIZE(size, category) MemoryAllocator_Allocate(size, category, __FILE__, __LINE__, __FUNCTION__)

 /**
 * @brief Macro to allocate memory for an array of objects of a specific type and category.
 *
 * @param type: The type of objects to allocate.
 * @param count: The number of objects to allocate.
 * @param category: The category associated with the allocation.
 * @param file: The file where the allocation is happening.
 * @param line: The line number where the allocation is happening.
 * @param function: The function where the allocation is happening.
 *
 * @return Pointer to the allocated memory block.
 */
#define ALLOCN(type, count, category) MemoryAllocator_AllocateN(count, sizeof(type), category, __FILE__, __LINE__, __FUNCTION__)


 /**
 * @brief Macro to allocate memory for an array of objects of a specific size and category.
 *
 * @param size: The size of memory to allocate.
 * @param count: The number of objects to allocate.
 * @param category: The category associated with the allocation.
 * @param file: The file where the allocation is happening.
 * @param line: The line number where the allocation is happening.
 * @param function: The function where the allocation is happening.
 *
 * @return Pointer to the allocated memory block.
 */
#define ALLOCN_SIZE(size, count, category) MemoryAllocator_AllocateN(count, size, category, __FILE__, __LINE__, __FUNCTION__)

 /**
  * @brief Macro to reallocate memory for a specific block to a new size.
  *
  * @param memory_block: The pointer to the memory block to be reallocated.
  * @param new_size: The new size of the memory block.
  * @param previous_size: The previous size of the memory block.
  * @param category: The category associated with the reallocation.
  * @param file: The file where the reallocation is happening.
  * @param line: The line number where the reallocation is happening.
  * @param function: The function where the reallocation is happening.
  */
#define REALLOC(memory_block, new_size, previous_size, category) \
    memory_block = MemoryAllocator_Reallocate(memory_block, new_size, previous_size, category, __FILE__, __LINE__, __FUNCTION__)

  /**
    * @brief Macro to deallocate memory for a block of a specific size and category.
    *
    * @param block_size: The size of the memory block to be deallocated.
    * @param category: The category associated with the deallocation.
    * @param file: The file where the deallocation is happening.
    * @param line: The line number where the deallocation is happening.
    * @param function: The function where the deallocation is happening.
    */
#define DEALLOC(block_size, category) MemoryAllocator_Deallocate(block_size, category, __FILE__, __LINE__, __FUNCTION__)

    /**
    * @brief Macro to free memory for a block and set the pointer to NULL.
    *
    * @param memory_block: The pointer to the memory block to be freed.
    * @param block_size: The size of the memory block to be freed.
    * @param category: The category associated with the memory block.
    * @param file: The file where the free is happening.
    * @param line: The line number where the free is happening.
    * @param function: The function where the free is happening.
    */
#define FREE(memory_block, block_size, category) MemoryAllocator_Free(memory_block, block_size, category, __FILE__, __LINE__, __FUNCTION__)
