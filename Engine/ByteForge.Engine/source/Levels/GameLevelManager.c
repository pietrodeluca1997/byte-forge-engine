#include "ByteForgeEngine/Levels/GameLevelManager.h"
#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"

#include <ByteForgeMemory.h>
#include <ByteForgeLogging.h>

#include <stdio.h>
#include <string.h>

static const char* const SCRIPTING_LEVEL_ON_SETUP_FUNCTION_NAME = "OnSetup";
static const char* const SCRIPTING_LEVEL_ON_START_FUNCTION_NAME = "OnStart";
static const char* const SCRIPTING_LEVEL_ON_UPDATE_FUNCTION_NAME = "OnUpdate";
static const char* const SCRIPTING_LEVEL_ON_QUIT_FUNCTION_NAME = "OnQuit";

bool GameLevelManager_LoadLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level)
{
    if (!level->level_name || !level->level_path) return false;

    size_t path_size = strlen(level->level_path) + strlen(level->level_name) + strlen(SCRIPTING_LANGUAGE_FILE_EXTENSION) + 1;

    char* level_path = ALLOCN(char, path_size, MEMORY_ALLOCATION_CATEGORY_STRING);

    if (!level_path) return false;

    strcpy_s(level_path, path_size, level->level_path);
    strcat_s(level_path, path_size, level->level_name);
    strcat_s(level_path, path_size, SCRIPTING_LANGUAGE_FILE_EXTENSION);

    ScriptingSubsystem_LoadFile(scripting_system, level_path);

    FREE(&level_path, path_size, MEMORY_ALLOCATION_CATEGORY_STRING);

    return true;
}

bool GameLevelManager_SetupLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level)
{
    return ScriptingSubsystem_Call(scripting_system, SCRIPTING_LEVEL_ON_SETUP_FUNCTION_NAME, 0);
}

bool GameLevelManager_StartLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level)
{
    return ScriptingSubsystem_Call(scripting_system, SCRIPTING_LEVEL_ON_START_FUNCTION_NAME, 0);
}

bool GameLevelManager_UpdateLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level, double delta_time)
{
    return ScriptingSubsystem_Call(scripting_system, SCRIPTING_LEVEL_ON_UPDATE_FUNCTION_NAME, 1, SCRIPTING_NUMBER_TYPE, delta_time);
}

bool GameLevelManager_QuitLevel(const ScriptingSubsystem* scripting_system, const GameLevel* level)
{
    return ScriptingSubsystem_Call(scripting_system, SCRIPTING_LEVEL_ON_QUIT_FUNCTION_NAME, 0);
}

void GameLevelManager_UnloadLevel(GameLevel** game_level)
{
    LOG_INFO("Freeing game level structure...");

    if (!game_level || !*game_level)
    {
        LOG_WARNING("\t - Warning: Attempted to free a NULL game level structure.");
        return;
    }

    GameLevel* game_level_deref = *game_level;

    FREE(&game_level_deref->level_name, sizeof(char) * (strlen(game_level_deref->level_name) + 1), MEMORY_ALLOCATION_CATEGORY_STRING);
    FREE(&game_level_deref->level_path, sizeof(char) * (strlen(game_level_deref->level_path) + 1), MEMORY_ALLOCATION_CATEGORY_STRING);

    LOG_INFO("\t - Freeing game level structure...");

    FREE(game_level, sizeof(GameLevel), MEMORY_ALLOCATION_CATEGORY_GAME_LEVEL);

    LOG_SUCCESS("\t - Game level structure freed successfully.");
}
