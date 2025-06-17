#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"
#include "ByteForgeEngine/Levels/GameLevel.h"

#include <ByteForgeMemory.h>
#include <ByteForgeLogging.h>

#include <Platform/PlatformData.h>

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

bool ScriptingSubsystem_Create(ScriptingSubsystem** scripting_subsystem)
{
    ScriptingSubsystem* new_scripting_subsystem = ALLOC(ScriptingSubsystem, MEMORY_ALLOCATION_CATEGORY_SCRIPTING_SUBSYSTEM);

    if (!new_scripting_subsystem)
    {
        LOG_FATAL("Error when trying to allocate memory for scripting subsystem.");
        return false;
    }

    new_scripting_subsystem->lua_state = luaL_newstate();

    if (!new_scripting_subsystem->lua_state)
    {
        LOG_FATAL("Unable to initialize a new Lua state for the scripting subsystem.");

        ScriptingSubsystem_Free(&new_scripting_subsystem);

        return false;
    }

    luaL_openlibs(new_scripting_subsystem->lua_state);

    *scripting_subsystem = new_scripting_subsystem;

    return true;
}

bool ScriptingSubsystem_LoadFile(const ScriptingSubsystem* const scripting_subsystem, const char* const file_path)
{
    if (luaL_dofile(scripting_subsystem->lua_state, file_path) != LUA_OK)
    {
        const char* error_message = lua_tostring(scripting_subsystem->lua_state, -1);
        LOG_ERROR("Error when trying to read file %s: %s", file_path, error_message ? error_message : "Unknown error");
        lua_pop(scripting_subsystem->lua_state, 1);

        return false;
    }

    return true;
}

bool ScriptingSubsystem_PushTable(const ScriptingSubsystem* const scripting_subsystem, const char* const table)
{
    lua_getglobal(scripting_subsystem->lua_state, table);

    return lua_istable(scripting_subsystem->lua_state, -1);
}

bool ScriptingSubsystem_PopTable(const ScriptingSubsystem* const scripting_subsystem)
{
    if (lua_istable(scripting_subsystem->lua_state, -1))
    {
        lua_pop(scripting_subsystem->lua_state, 1);
        return true;
    }

    return false;
}

bool ScriptingSubsystem_GetGlobalInteger(const ScriptingSubsystem* const scripting_subsystem, const char* const field, int* out_integer)
{
    lua_getfield(scripting_subsystem->lua_state, -1, field);

    if (lua_isinteger(scripting_subsystem->lua_state, -1))
    {
        *out_integer = (int) lua_tointeger(scripting_subsystem->lua_state, -1);

        lua_pop(scripting_subsystem->lua_state, 1);

        return true;
    }

    return false;
}

void* ScriptingSubsystem_GetUserdataByGlobalName(lua_State* lua_state, const char* global_name)
{
    lua_getglobal(lua_state, global_name);

    if (lua_isuserdata(lua_state, -1))
    {
        void* userdata = lua_touserdata(lua_state, -1);

        lua_pop(lua_state, 1);

        return userdata;
    }
    else
    {
        lua_pop(lua_state, 1);

        return NULL;
    }
}

void ScriptingSubsystem_PushInteger(lua_State* lua_state, int value)
{
    lua_pushinteger(lua_state, value);
}

bool ScriptingSubsystem_GetGlobalString(const ScriptingSubsystem* const scripting_subsystem, const char* const field, char** out_string)
{
    lua_getfield(scripting_subsystem->lua_state, -1, field);

    if (lua_isstring(scripting_subsystem->lua_state, -1))
    {
        const char* string = lua_tostring(scripting_subsystem->lua_state, -1);

        if (string)
        {
            *out_string = ALLOCN(char, strlen(string) + 1, MEMORY_ALLOCATION_CATEGORY_STRING);

            memcpy(*out_string, string, strlen(string) + 1);

            lua_pop(scripting_subsystem->lua_state, 1);

            return true;
        }        
    }

    return false;
}

bool ScriptingSubsystem_Call(const ScriptingSubsystem* const scripting_subsystem, const char* const function_name, const uint8_t arguments_count, ...)
{
    lua_getglobal(scripting_subsystem->lua_state, function_name);

    if (!lua_isfunction(scripting_subsystem->lua_state, -1)) return false;

    va_list args;
    va_start(args, arguments_count);

    for (int i = 0; i < arguments_count; ++i) 
    {
        const char* type = va_arg(args, const char*);

        if (strcmp(type, SCRIPTING_NUMBER_TYPE) == 0)
        {
            double num = va_arg(args, double);
            lua_pushnumber(scripting_subsystem->lua_state, num);
        }
        else if (strcmp(type, SCRIPTING_STRING_TYPE) == 0) 
        {
            const char* str = va_arg(args, const char*);
            lua_pushstring(scripting_subsystem->lua_state, str);
        }
        else if (strcmp(type, SCRIPTING_BOOLEAN_TYPE) == 0)
        {
            int boolean = va_arg(args, int);
            lua_pushboolean(scripting_subsystem->lua_state, boolean);
        }
    }

    va_end(args);
    
    return lua_pcall(scripting_subsystem->lua_state, arguments_count, 0, 0) == LUA_OK;
}

void ScriptingSubsystem_Free(ScriptingSubsystem** scripting_system)
{
    if (!scripting_system || !*scripting_system) return;

    if ((*scripting_system)->lua_state)
    {
        lua_close((*scripting_system)->lua_state);
    }   

    FREE(scripting_system, sizeof(ScriptingSubsystem), MEMORY_ALLOCATION_CATEGORY_SCRIPTING_SUBSYSTEM);
}
