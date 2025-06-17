#pragma once

#include "Memory/Allocation/MemoryAllocationCategory.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Represents a dynamic array for storing elements of any type.
 *
 * This dynamic array uses a contiguous block of memory to store elements. It can grow in size as needed
 * when more elements are added beyond the current capacity.
 */
typedef struct DynamicArray
{
	void* contiguous_elements;
	size_t count;
	size_t capacity;
	size_t element_size;
} DynamicArray;

/**
 * @brief Initializes a dynamic array with the specified element size and initial capacity.
 *
 * This function allocates memory for the dynamic array and prepares it to store elements. The array
 * will automatically resize when it exceeds its current capacity.
 *
 * @param dynamic_array: Pointer to the dynamic array to initialize.
 * @param element_size: The size of each element in the array in bytes.
 * @param initial_capacity: The initial capacity of the dynamic array.
 * @param allocation_category: The memory allocation category for this operation.
 *
 * @return true if the dynamic array was successfully initialized, false otherwise.
 */
bool DynamicArray_Initialize(
	DynamicArray** dynamic_array, 
	const size_t element_size, 
	const size_t initial_capacity, 
	const EMemoryAllocationCategory allocation_category
);	

/**
 * @brief Adds a new element to the dynamic array.
 *
 * If the array has enough capacity, the new element is added. Otherwise, the array will resize to
 * accommodate the new element.
 *
 * @param dynamic_array: The dynamic array to which the element is to be added.
 * @param new_element: Pointer to the element to be added to the array.
 * @param allocation_category: The memory allocation category for this operation.
 *
 * @return true if the element was successfully added, false otherwise.
 */
bool DynamicArray_Add(
	DynamicArray* dynamic_array, 
	const void* const new_element, 
	const EMemoryAllocationCategory allocation_category
);

/**
 * @brief Retrieves an element from the dynamic array by its index.
 *
 * If the index is valid, the corresponding element is returned. If the index is out of bounds,
 * NULL is returned.
 *
 * @param dynamic_array: The dynamic array to search for the element.
 * @param index: The index of the element to retrieve.
 *
 * @return Pointer to the element at the specified index, or NULL if the index is invalid.
 */
void* DynamicArray_Get(const DynamicArray* dynamic_array, const size_t index);

/**
 * @brief Removes an element from the dynamic array by its index.
 *
 * If the index is valid, the element is removed, and the remaining elements are shifted to fill the gap.
 * If the index is out of bounds, no operation is performed.
 *
 * @param dynamic_array: The dynamic array from which the element will be removed.
 * @param index: The index of the element to remove.
 *
 * @return true if the element was successfully removed, false if the index was invalid.
 */
bool DynamicArray_Remove(DynamicArray* dynamic_array, const size_t index);

/**
 * @brief Frees the memory used by the dynamic array.
 *
 * This function deallocates the memory for the elements and the dynamic array structure itself.
 *
 * @param dynamic_array: Pointer to the dynamic array to free.
 * @param allocation_category: The memory allocation category for this operation.
 */
void DynamicArray_Free(
	DynamicArray** dynamic_array, 
	const EMemoryAllocationCategory allocation_category
);