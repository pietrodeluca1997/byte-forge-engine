#pragma once

#include "Memory/Allocation/MemoryAllocationCategory.h"

#include <stddef.h>

/**
 * @brief Function signature for comparing keys in the dictionary.
 *
 * This function will be used to compare two keys for equality. It should return true if the keys are equal,
 * and false otherwise.
 */
typedef bool (*HandleKeysComparisonFunctionSignature)(const void* const first_key, const void* const second_key);

/**
 * @brief Represents a dictionary structure for storing key-value pairs.
 *
 * This dictionary uses raw memory for both keys and values, and relies on a callback for key comparison.
 */
typedef struct Dictionary
{
	void* keys;
	void* values;
	size_t key_size;
	size_t value_size;
	size_t count;
	size_t capacity;
	HandleKeysComparisonFunctionSignature key_comparison_callback;
} Dictionary;

/**
 * @brief Initializes a dictionary with specified parameters.
 *
 * Allocates memory for the dictionary's keys and values, and sets up the necessary callback for key comparison.
 *
 * @param dictionary: Pointer to the dictionary to initialize.
 * @param key_size: The size of each key in bytes.
 * @param value_size: The size of each value in bytes.
 * @param initial_capacity: The initial capacity of the dictionary.
 * @param key_comparison_callback: Function used to compare keys for equality.
 * @param allocation_category: The memory allocation category for this operation.
 *
 * @return true if the dictionary is successfully initialized, false otherwise.
 */
bool Dictionary_Initialize(
	Dictionary** dictionary, 
	const size_t key_size, 
	const size_t value_size, 
	const size_t initial_capacity, 
	const HandleKeysComparisonFunctionSignature key_comparison_callback, 
	const EMemoryAllocationCategory allocation_category
);

/**
 * @brief Adds a new key-value pair or updates an existing one in the dictionary.
 *
 * If the key already exists, its value will be updated; otherwise, a new key-value pair will be added.
 *
 * @param dictionary: The dictionary in which to add or update the key-value pair.
 * @param key: Pointer to the key to be added or updated.
 * @param value: Pointer to the value associated with the key.
 * @param allocation_category: The memory allocation category for this operation.
 *
 * @return true if the key-value pair was added or updated successfully, false otherwise.
 */
bool Dictionary_AddOrUpdate(
	Dictionary* dictionary, 
	const void* const key, 
	const void* const value,
	const EMemoryAllocationCategory allocation_category
);

/**
 * @brief Removes a key-value pair from the dictionary.
 *
 * The key is used to locate the pair to be removed. If the key is not found, no operation is performed.
 *
 * @param dictionary: The dictionary from which to remove the key-value pair.
 * @param key: Pointer to the key to be removed.
 *
 * @return true if the key-value pair was removed, false otherwise.
 */
bool Dictionary_Remove(Dictionary* dictionary, const void* const key);

/**
 * @brief Retrieves the value associated with a specific key in the dictionary.
 *
 * If the key is found, a pointer to the value is returned. If not, NULL is returned.
 *
 * @param dictionary: The dictionary to search for the key.
 * @param key: Pointer to the key whose value is to be retrieved.
 *
 * @return Pointer to the value associated with the key, or NULL if the key is not found.
 */
void* Dictionary_Get(const Dictionary* dictionary, const void* const key);

/**
 * @brief Frees the memory used by the dictionary.
 *
 * This function deallocates the memory for the keys, values, and the dictionary structure itself.
 *
 * @param dictionary: Pointer to the dictionary to free.
 * @param allocation_category: The memory allocation category for this operation.
 */
void Dictionary_Free(
	Dictionary** dictionary, 
	const EMemoryAllocationCategory allocation_category
);
