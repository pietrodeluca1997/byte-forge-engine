#include "ByteForgeEngine/Configuration/EnginePlatformConfiguration.h"

#include <ByteForgeMemory.h>

static const char* const PLATFORM_CONFIGURATION_FILE_PATH = "./Configuration/PlatformConfiguration.lua";
static const char* const PLATFORM_SETTINGS_TABLE_NAME = "PlatformSettings";
static const char* const PLATFORM_WINDOW_TABLE_NAME = "PlatformWindow";
static const char* const TARGET_FPS_FIELD_NAME = "target_fps";
static const char* const WINDOW_TITLE_FIELD_NAME = "window_title";
static const char* const WINDOW_WIDTH_FIELD_NAME = "window_width";
static const char* const WINDOW_HEIGHT_FIELD_NAME = "window_height";

bool EnginePlatformConfiguration_LoadFromConfigurationFile(const ScriptingSubsystem* const scripting_subsystem, PlatformData** out_platform_data)
{
    if (!ScriptingSubsystem_LoadFile(scripting_subsystem, PLATFORM_CONFIGURATION_FILE_PATH)) return false;
    if (!ScriptingSubsystem_PushTable(scripting_subsystem, PLATFORM_SETTINGS_TABLE_NAME)) return false;

    int target_fps;

    if (!ScriptingSubsystem_GetGlobalInteger(scripting_subsystem, TARGET_FPS_FIELD_NAME, &target_fps)) return false;

    if (!ScriptingSubsystem_PopTable(scripting_subsystem)) return false;

    PlatformSettingsData* platform_settings = NULL;

    if (!PlatformSettingsData_Create((uint8_t)target_fps, &platform_settings)) return false;

    if (!ScriptingSubsystem_PushTable(scripting_subsystem, PLATFORM_WINDOW_TABLE_NAME)) return false;

    char* window_title = NULL;
    uint8_t* window_width = NULL;
    uint8_t* window_height = NULL;

    if (!ScriptingSubsystem_GetGlobalString(scripting_subsystem, WINDOW_TITLE_FIELD_NAME, &window_title)) return false;
    if (!ScriptingSubsystem_GetGlobalInteger(scripting_subsystem, WINDOW_WIDTH_FIELD_NAME, &window_width)) return false;
    if (!ScriptingSubsystem_GetGlobalInteger(scripting_subsystem, WINDOW_HEIGHT_FIELD_NAME, &window_height)) return false;

    if (!ScriptingSubsystem_PopTable(scripting_subsystem)) return false;

    PlatformWindowData* platform_window = NULL;

    if (!PlatformWindowData_Create(window_title, window_width, window_height, &platform_window)) return false;

    FREE(&window_title, sizeof(char) * (strlen(window_title) + 1), MEMORY_ALLOCATION_CATEGORY_STRING);

    PlatformData* platform_data = NULL;

    if (!PlatformData_Create(&platform_data))
    {
        return false;
    }

    platform_data->settings_data = platform_settings;
    platform_data->window_data = platform_window;

    *out_platform_data = platform_data;

    return true;
}
