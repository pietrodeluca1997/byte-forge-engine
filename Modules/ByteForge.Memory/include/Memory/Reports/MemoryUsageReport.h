#pragma once

#include "Memory/Allocation/MemoryAllocationCategory.h"

#include <stddef.h>

/**
 * @brief Initializes the memory usage report system.
 *
 * This function prepares the reporting mechanism to track memory allocations and deallocations.
 * It should be called before any tracking operations.
 *
 * @return true if the initialization was successful, false otherwise.
 */
bool MemoryUsageReport_Init();

/**
 * @brief Prints the current memory usage information.
 *
 * This function outputs the tracked memory usage data, providing insights into memory allocation
 * and deallocation across various categories.
 */
void MemoryUsageReport_PrintInfo();

/**
 * @brief Tracks a memory allocation.
 *
 * This function logs the allocated memory size for a specific allocation category.
 *
 * @param allocation_size: The size of the allocated memory block in bytes.
 * @param allocation_category: The category associated with the allocation.
 * @param file: The file where the allocation was made.
 * @param line: The line number where the allocation occurred.
 * @param func: The function name where the allocation was made.
 */
void MemoryUsageReport_TrackAllocation(
	const size_t allocation_size,
	const EMemoryAllocationCategory allocation_category,
	const char* file,
	const int line,
	const char* func
);

/**
 * @brief Tracks a memory deallocation.
 *
 * This function logs the deallocated memory size for a specific deallocation category.
 *
 * @param deallocation_size: The size of the deallocated memory block in bytes.
 * @param deallocation_category: The category associated with the deallocation.
 * @param file: The file where the deallocation was made.
 * @param line: The line number where the deallocation occurred.
 * @param func: The function name where the deallocation was made.
 */
void MemoryUsageReport_TrackDeallocation(
	const size_t deallocation_size,
	const EMemoryAllocationCategory deallocation_category,
	const char* file,
	const int line,
	const char* func
);

/**
 * @brief Frees resources used by the memory usage report system.
 *
 * This function should be called when the memory usage reporting is no longer needed,
 * to clean up any allocated resources.
 */
void MemoryUsageReport_Exit();
