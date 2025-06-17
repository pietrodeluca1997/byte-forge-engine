#include "Memory/Helpers/MemoryStructureHelper.h"

void* MemoryStructureHelper_GetValueFromArrayUsingDictIndex(const Dictionary* dict, const DynamicArray* array, const uint64_t dict_key)
{
    uint64_t* array_index_ptr = Dictionary_Get(dict, &dict_key);

    if (!array_index_ptr)
    {
        return NULL;
    }
    
    return DynamicArray_Get(array, *array_index_ptr);
}