#pragma once

#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"
#include "GameLevel.h"

/**
 * @brief Loads a game level.
 *
 * This function loads the specified game level into memory, preparing it for further setup and processing.
 * It may involve loading assets, initializing data, or any other necessary setup operations.
 *
 * @param scripting_system: A pointer to the scripting subsystem to manage scripts related to the level.
 * @param level: A pointer to the `GameLevel` structure that contains the level's information.
 *
 * @return true if the level was successfully loaded, false otherwise.
 */
bool GameLevelManager_LoadLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level);

/**
 * @brief Sets up a game level.
 *
 * This function sets up the game level by initializing game objects, loading resources, or performing
 * other setup actions needed before the game level can be started.
 *
 * @param scripting_system: A pointer to the scripting subsystem to configure scripts related to the level.
 * @param level: A pointer to the `GameLevel` structure that contains the level's information.
 *
 * @return true if the level setup was successful, false otherwise.
 */
bool GameLevelManager_SetupLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level);

/**
 * @brief Starts the game level.
 *
 * This function marks the start of a game level, typically by activating game logic, running scripts,
 * or starting the gameplay mechanics.
 *
 * @param scripting_system: A pointer to the scripting subsystem to manage scripts when the level starts.
 * @param level: A pointer to the `GameLevel` structure that contains the level's information.
 *
 * @return true if the level started successfully, false otherwise.
 */
bool GameLevelManager_StartLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level);

/**
 * @brief Updates the game level.
 *
 * This function updates the game level, typically called each frame or cycle. It may include running game
 * logic, updating entities, and processing level-specific mechanics.
 *
 * @param scripting_system: A pointer to the scripting subsystem for handling scripts and updates during the level.
 * @param level: A pointer to the `GameLevel` structure that contains the level's information.
 * @param delta_time: The time that has passed since the last update, typically used for frame-based updates.
 *
 * @return true if the level update was successful, false otherwise.
 */
bool GameLevelManager_UpdateLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level, double delta_time);

/**
 * @brief Quits the current game level.
 *
 * This function handles the cleanup and deactivation of a game level, stopping scripts and processes
 * associated with the level before transitioning to another level or ending the game.
 *
 * @param scripting_system: A pointer to the scripting subsystem for managing any necessary script shutdown.
 * @param level: A pointer to the `GameLevel` structure that contains the level's information.
 *
 * @return true if the level quit successfully, false otherwise.
 */
bool GameLevelManager_QuitLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level);

void GameLevelManager_UnloadLevel(GameLevel** level);