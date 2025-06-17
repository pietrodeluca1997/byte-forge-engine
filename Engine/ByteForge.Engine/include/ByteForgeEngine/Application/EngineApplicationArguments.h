#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Represents the arguments passed to the engine application at startup.
 *
 * This struct holds the count and values of the arguments passed to the engine,
 * typically through command-line input. The values array is expected to be NULL-terminated.
 */
typedef struct EngineApplicationArguments
{
	uint8_t count;
	char** values;
} EngineApplicationArguments;

bool EngineApplicationArguments_Create(const uint8_t count, const char* const* const values, EngineApplicationArguments** out_arguments);
void EngineApplicationArguments_Free(EngineApplicationArguments** arguments);