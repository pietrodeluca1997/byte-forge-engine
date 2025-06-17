#include "Memory/Structures/DynamicArray.h"
#include "Memory/Allocation/MemoryAllocationMacros.h"

#include <stdlib.h>
#include <string.h>

bool DynamicArray_Initialize(DynamicArray** dynamic_array, const size_t element_size, const size_t initial_capacity, const EMemoryAllocationCategory allocation_category)
{
    if (element_size == 0 || initial_capacity == 0)
    {
        return false;
    }

    DynamicArray* new_dynamic_array = ALLOC(DynamicArray, allocation_category);

    if (!new_dynamic_array)
    {
        return false;
    }

    void* contiguous_elements = ALLOCN_SIZE(element_size, initial_capacity, allocation_category);

    if (!contiguous_elements)
    {
        return false;
    }

    new_dynamic_array->contiguous_elements = contiguous_elements;
    new_dynamic_array->element_size = element_size;
    new_dynamic_array->capacity = initial_capacity;
    new_dynamic_array->count = 0;

    *dynamic_array = new_dynamic_array;

    return true;
}

bool DynamicArray_Add(DynamicArray* dynamic_array, void* new_element, EMemoryAllocationCategory allocation_category)
{
    if (dynamic_array == NULL || new_element == NULL)
    {
        return false;
    }

    if (dynamic_array->count + 1 > dynamic_array->capacity)
    {
        void* new_data = MemoryAllocator_Reallocate(&dynamic_array->contiguous_elements, dynamic_array->element_size * dynamic_array->capacity * 2, dynamic_array->element_size * dynamic_array->capacity, allocation_category, "D:\\Programming\\Projects\\byte-forge-project\\Modules\\ByteForge.Memory\\source\\Structures\\DynamicArray.c", 52, __FUNCTION__);

        if (!new_data)
        {
            return false;
        }

        dynamic_array->capacity *= 2;
        dynamic_array->contiguous_elements = new_data;
    }

    memcpy((char*)dynamic_array->contiguous_elements + dynamic_array->count * dynamic_array->element_size, new_element, dynamic_array->element_size);

    dynamic_array->count++;

    return true;
}

void* DynamicArray_Get(const DynamicArray* dynamic_array, const size_t index)
{
    if (dynamic_array == NULL || index >= dynamic_array->count)
    {
        return NULL;
    }

    return (char*) dynamic_array->contiguous_elements + dynamic_array->element_size * index;
}

bool DynamicArray_Remove(DynamicArray* dynamic_array, const size_t index)
{
    if (!dynamic_array || index >= dynamic_array->count)
    {
        return false;
    }

    char* data = (char*) dynamic_array->contiguous_elements;

    memmove
    (
        &data[index * dynamic_array->element_size],
        &data[(index + 1) * dynamic_array->element_size],
        (dynamic_array->count - index - 1) * dynamic_array->element_size
    );

    dynamic_array->count--;

    

    return true;
}

void DynamicArray_Free(DynamicArray** dynamic_array, const EMemoryAllocationCategory allocation_category)
{
    if (!dynamic_array || !*dynamic_array) return;

    if ((*dynamic_array)->contiguous_elements) {
        FREE(
            &(*dynamic_array)->contiguous_elements,
            (*dynamic_array)->element_size * (*dynamic_array)->capacity,
            allocation_category
        );

        (*dynamic_array)->contiguous_elements = NULL;
    }

    FREE(dynamic_array, sizeof(DynamicArray), allocation_category);
}