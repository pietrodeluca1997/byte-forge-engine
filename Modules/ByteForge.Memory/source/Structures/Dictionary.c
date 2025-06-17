#include "Memory/Structures/Dictionary.h"
#include "Memory/Allocation/MemoryAllocationMacros.h"

#include <stdlib.h>
#include <string.h>

bool Dictionary_Initialize(Dictionary** dictionary, const size_t key_size, const size_t value_size, const size_t initial_capacity, const HandleKeysComparisonFunctionSignature key_comparison_callback, const EMemoryAllocationCategory allocation_category)
{
    if (key_size == 0 || value_size == 0 || initial_capacity == 0 || key_comparison_callback == NULL)
    {
        return false;
    }

    Dictionary* new_dictionary = ALLOC(Dictionary, allocation_category);

    if (!new_dictionary) return false;

    void* new_keys = ALLOCN_SIZE(key_size, initial_capacity, allocation_category);

    if (!new_keys) return false;

    void* new_values = ALLOCN_SIZE(value_size, initial_capacity, allocation_category);

    if (!new_values) return false;

    new_dictionary->keys = new_keys;
    new_dictionary->values = new_values;
    new_dictionary->key_size = key_size;
    new_dictionary->value_size = value_size;
    new_dictionary->capacity = initial_capacity;
    new_dictionary->count = 0;
    new_dictionary->key_comparison_callback = key_comparison_callback;

    *dictionary = new_dictionary;

    return true;
}

bool Dictionary_AddOrUpdate(Dictionary* dictionary, const void* const key, const void* const value, const EMemoryAllocationCategory allocation_category)
{
    if (!dictionary || !key || !value)
    {
        return false;
    }

    for (size_t i = 0; i < dictionary->count; i++)
    {
        void* current_key = (char*)dictionary->keys + i * dictionary->key_size;

        if (dictionary->key_comparison_callback(current_key, key))
        {
            memcpy((char*)dictionary->values + i * dictionary->value_size, value, dictionary->value_size);
            return true;
        }
    }

    if (dictionary->count + 1 > dictionary->capacity)
    {
        void* new_keys_data = MemoryAllocator_Reallocate(&dictionary->keys, dictionary->capacity * dictionary->key_size * 2, dictionary->capacity * dictionary->key_size, allocation_category, "D:\\Programming\\Projects\\byte-forge-project\\Modules\\ByteForge.Memory\\source\\Structures\\Dictionary.c", 59, __FUNCTION__);
        void* new_values_data = MemoryAllocator_Reallocate(&dictionary->values, dictionary->capacity * dictionary->value_size * 2, dictionary->capacity * dictionary->value_size, allocation_category, "D:\\Programming\\Projects\\byte-forge-project\\Modules\\ByteForge.Memory\\source\\Structures\\Dictionary.c", 60, __FUNCTION__);

        if (!new_keys_data || !new_values_data)
        {
            return false;
        }

        dictionary->capacity *= 2;
        dictionary->keys = new_keys_data;
        dictionary->values = new_values_data;
    }

    void* target_key = (char*)dictionary->keys + dictionary->count * dictionary->key_size;
    void* value_key = (char*)dictionary->values + dictionary->count * dictionary->value_size;

    memcpy(target_key, key, dictionary->key_size);
    memcpy(value_key, value, dictionary->value_size);

    dictionary->count++;

    return true;
}

bool Dictionary_Remove(Dictionary* dictionary, const void* const key)
{
    if (!dictionary || !key)
    {
        return false;
    }

    for (size_t i = 0; i < dictionary->count; i++)
    {
        void* current_key = (char*)dictionary->keys + i * dictionary->key_size;

        if (dictionary->key_comparison_callback(current_key, key))
        {
            memmove(
                current_key,
                (char*)dictionary->keys + (i + 1) * dictionary->key_size,
                (dictionary->count - i - 1) * dictionary->key_size
            );

            void* current_value = (char*)dictionary->values + i * dictionary->value_size;

            memmove(
                current_value,
                (char*)dictionary->values + (i + 1) * dictionary->value_size,
                (dictionary->count - i - 1) * dictionary->value_size
            );

            dictionary->count--;
            return true;
        }
    }

    return false;
}


void* Dictionary_Get(const Dictionary* dictionary, const void* const key)
{
    if (!dictionary || !key)
    {
        return NULL;
    }

    for (size_t i = 0; i < dictionary->count; i++)
    {
        void* current_key = (char*)dictionary->keys + i * dictionary->key_size;

        if (dictionary->key_comparison_callback(current_key, key))
        {
            return (char*)dictionary->values + i * dictionary->value_size;
        }
    }

    return NULL;
}

void Dictionary_Free(Dictionary** dictionary, const EMemoryAllocationCategory allocation_category)
{
    FREE(&(*dictionary)->keys, (*dictionary)->key_size * (*dictionary)->capacity, allocation_category);
    FREE(&(*dictionary)->values, (*dictionary)->value_size * (*dictionary)->capacity, allocation_category);
    FREE(dictionary, sizeof(Dictionary), allocation_category);
}