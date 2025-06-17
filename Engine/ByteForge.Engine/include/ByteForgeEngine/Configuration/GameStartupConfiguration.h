#pragma once

#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"
#include "ByteForgeEngine/Levels/GameLevel.h"

/**
 * @brief Loads the startup game level configuration.
 *
 * This function loads the initial level configuration for the game, typically from a script or configuration file.
 * It utilizes the `scripting_subsystem` to handle any required script-based logic for loading the level.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` used for script-based logic to load the startup level.
 * @param out_game_level: A pointer to a pointer to the `GameLevel` structure that will be populated with the loaded level information.
 *
 * @return `true` if the startup level was successfully loaded, `false` otherwise.
 */
bool GameStartupConfiguration_LoadStartupLevel(const ScriptingSubsystem* const scripting_subsystem, GameLevel** out_game_level);