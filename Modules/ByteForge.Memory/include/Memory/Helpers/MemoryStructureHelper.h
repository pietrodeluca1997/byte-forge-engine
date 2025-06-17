#pragma once

#include <stdint.h>
#include <stddef.h>

#include "Memory/Structures/Dictionary.h"
#include "Memory/Structures/DynamicArray.h"

void* MemoryStructureHelper_GetValueFromArrayUsingDictIndex(const Dictionary* dict, const DynamicArray* array, const uint64_t dict_key);