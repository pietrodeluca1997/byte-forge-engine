#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define SCRIPTING_LANGUAGE_FILE_EXTENSION ".lua"
#define SCRIPTING_STRING_TYPE "string"
#define SCRIPTING_NUMBER_TYPE "number"
#define SCRIPTING_BOOLEAN_TYPE "boolean"

/**
 * @brief A subsystem that interfaces with Lua scripting.
 *
 * The `ScriptingSubsystem` is responsible for managing the Lua state and providing functionality
 * for executing Lua scripts, manipulating Lua tables, and calling Lua functions within the engine.
 */
typedef struct ScriptingSubsystem
{
    struct lua_State* lua_state; ///< The Lua state that is used for script execution.
} ScriptingSubsystem;

/**
 * @brief Creates and initializes a new `ScriptingSubsystem`.
 *
 * This function allocates and sets up the necessary resources for Lua scripting in the engine.
 *
 * @param scripting_subsystem: A pointer to a pointer to an `ScriptingSubsystem`, which will be
 *                             initialized by this function.
 *
 * @returns `true` if the subsystem was created successfully, `false` otherwise.
 */
bool ScriptingSubsystem_Create(ScriptingSubsystem** scripting_subsystem);

/**
 * @brief Loads a Lua script from a file.
 *
 * This function loads and executes a Lua script from the specified file path, and the Lua state
 * is updated with any global variables and functions defined in the script.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` instance.
 * @param file_path: The path to the Lua script to load and execute.
 *
 * @returns `true` if the file was loaded and executed successfully, `false` otherwise.
 */
bool ScriptingSubsystem_LoadFile(const ScriptingSubsystem* const scripting_subsystem, const char* const file_path);

/**
 * @brief Pushes a Lua table onto the Lua stack.
 *
 * This function allows interaction with a Lua table by pushing it onto the Lua stack so that
 * its fields can be accessed or modified.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` instance.
 * @param table: The name of the Lua table to push onto the stack.
 *
 * @returns `true` if the table was pushed successfully, `false` otherwise.
 */
bool ScriptingSubsystem_PushTable(const ScriptingSubsystem* const scripting_subsystem, const char* const table);

/**
 * @brief Pops a Lua table from the Lua stack.
 *
 * This function removes the top table from the Lua stack, allowing further stack manipulation.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` instance.
 *
 * @returns `true` if the table was popped successfully, `false` otherwise.
 */
bool ScriptingSubsystem_PopTable(const ScriptingSubsystem* const scripting_subsystem);

/**
 * @brief Gets a global integer value from the Lua state.
 *
 * This function retrieves a global variable from the Lua state and stores it as an integer.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` instance.
 * @param field: The name of the global variable to retrieve.
 * @param out_integer: A pointer to the integer where the value will be stored.
 *
 * @returns `true` if the integer was successfully retrieved, `false` otherwise.
 */
bool ScriptingSubsystem_GetGlobalInteger(const ScriptingSubsystem* const scripting_subsystem, const char* const field, int* out_integer);

void* ScriptingSubsystem_GetUserdataByGlobalName(lua_State* lua_state, const char* global_name);

void ScriptingSubsystem_PushInteger(lua_State* lua_state, int value);

/**
 * @brief Gets a global string value from the Lua state.
 *
 * This function retrieves a global variable from the Lua state and stores it as a string.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` instance.
 * @param field: The name of the global variable to retrieve.
 * @param out_string: A pointer to the string where the value will be stored.
 *
 * @returns `true` if the string was successfully retrieved, `false` otherwise.
 */
bool ScriptingSubsystem_GetGlobalString(const ScriptingSubsystem* const scripting_subsystem, const char* const field, char** out_string);

/**
 * @brief Calls a Lua function with the given arguments.
 *
 * This function pushes arguments onto the Lua stack and then calls the specified Lua function.
 *
 * @param scripting_subsystem: A pointer to the `ScriptingSubsystem` instance.
 * @param function_name: The name of the Lua function to call.
 * @param arguments_count: The number of arguments to pass to the function.
 * @param ... The arguments to pass to the Lua function.
 *
 * @returns `true` if the function was called successfully, `false` otherwise.
 */
bool ScriptingSubsystem_Call(const ScriptingSubsystem* const scripting_subsystem, const char* const function_name, const uint8_t arguments_count, ...);

/**
 * @brief Frees the resources associated with a `ScriptingSubsystem`.
 *
 * This function releases any allocated memory or resources tied to the scripting subsystem,
 * including the Lua state.
 *
 * @param scripting_subsystem: A pointer to a pointer to the `ScriptingSubsystem` instance to free.
 */
void ScriptingSubsystem_Free(ScriptingSubsystem** scripting_system);
