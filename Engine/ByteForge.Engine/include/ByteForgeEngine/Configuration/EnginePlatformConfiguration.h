#pragma once

#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"

#include <ByteForgePlatform.h>

/**
 * @brief Loads platform-specific configuration for the engine.
 *
 * This function initializes platform-specific data required for the engine to function properly.
 * It makes use of the provided `scripting_subsystem` to load and apply configurations from scripts or other sources.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` used to handle scripting-related tasks and configurations.
 * @param out_platform_data: A pointer to a pointer to the `PlatformData` structure that will be populated with platform-specific configuration.
 *
 * @return `true` if the platform configuration was successfully loaded, `false` otherwise.
 */
bool EnginePlatformConfiguration_LoadFromConfigurationFile(const ScriptingSubsystem* const scripting_subsystem, PlatformData** out_platform_data);