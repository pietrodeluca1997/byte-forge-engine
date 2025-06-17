#include "ByteForgeEngine/Configuration/GameStartupConfiguration.h"

#include <ByteForgeLogging.h>
#include <ByteForgeMemory.h>

static const char* const GAME_STARTUP_CONFIGURATION_FILE_PATH = "./Configuration/GameStartupConfiguration.lua";
static const char* const STARTUP_LEVEL_TABLE_NAME = "StartupLevel";
static const char* const LEVEL_NAME_FIELD_NAME = "level_name";
static const char* const LEVEL_PATH_FIELD_NAME = "level_path";

bool GameStartupConfiguration_LoadStartupLevel(const ScriptingSubsystem* const scripting_subsystem, GameLevel** out_game_level)
{
    if (!ScriptingSubsystem_LoadFile(scripting_subsystem, GAME_STARTUP_CONFIGURATION_FILE_PATH))
    {
        return false;
    }

    if (!ScriptingSubsystem_PushTable(scripting_subsystem, STARTUP_LEVEL_TABLE_NAME))
    {
        return false;
    }
        
    GameLevel* startup_game_level = ALLOC(GameLevel, MEMORY_ALLOCATION_CATEGORY_GAME_LEVEL);

    if (!startup_game_level)
    {
        LOG_FATAL("Error when trying to initialize GameLevel memory location");
        return false;
    }

    if (!ScriptingSubsystem_GetGlobalString(scripting_subsystem, LEVEL_NAME_FIELD_NAME, &startup_game_level->level_name)) return false;
    if (!ScriptingSubsystem_GetGlobalString(scripting_subsystem, LEVEL_PATH_FIELD_NAME, &startup_game_level->level_path)) return false;
    
    if (!ScriptingSubsystem_PopTable(scripting_subsystem)) return false;

    *out_game_level = startup_game_level;

    return true;
}