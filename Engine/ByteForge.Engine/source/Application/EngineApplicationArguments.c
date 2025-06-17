#include "ByteForgeEngine/Application/EngineApplicationArguments.h"

#include <ByteForgeMemory.h>
#include <ByteForgeLogging.h>

bool EngineApplicationArguments_Create(const uint8_t count, const char* const* const values, EngineApplicationArguments** out_arguments)
{
	EngineApplicationArguments* arguments = ALLOC(EngineApplicationArguments, MEMORY_ALLOCATION_CATEGORY_ENGINE_APPLICATION);
	
	if (!arguments)
	{
		LOG_FATAL("Error when trying to allocate memory for engine application arguments.");
		return false;
	}

	arguments->count = count;
	arguments->values = values;

	*out_arguments = arguments;

	return true;
}

void EngineApplicationArguments_Free(EngineApplicationArguments** arguments)
{
	FREE(arguments, sizeof(EngineApplicationArguments), MEMORY_ALLOCATION_CATEGORY_ENGINE_APPLICATION);
}
