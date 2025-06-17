#pragma once

#include "ByteForgeEngine/API/EngineApiSettings.h"
#include "ByteForgeEngine/Application/EngineApplicationArguments.h"

#include <stdbool.h>

/**
 * @brief Starts the ByteForge Engine with the provided application arguments.
 *
 * This function initializes and runs the engine, processing the provided arguments.
 * It sets up the necessary subsystems and starts the engine loop.
 *
 * @param argc: Number of command-line arguments.
 * @param argv: Array of command-line argument strings.
 *
 * @return A boolean indicating whether the engine started successfully.
 *         Returns true if successful, false if there was an error during startup.
 */
BF_ENGINE_API bool ByteForgeEngine_Start(const int argc, const char** argv);