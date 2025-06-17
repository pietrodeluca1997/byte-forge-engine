#pragma once

#include "ByteForgeEngine/Application/EngineApplicationArguments.h"
#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"
#include "ByteForgeEngine/Levels/GameLevel.h"
#include "ByteForgeEngine/AssetManager/AssetManager.h"

#include <ByteForgeECS.h>
#include <ByteForgePlatform.h>


/**
 * @brief Represents the main application structure of the ByteForge engine.
 *
 * This structure holds all necessary components and subsystems for the engine
 * application to run, such as arguments, scripting, platform data, game level,
 * and ECS registry.
 */
typedef struct EngineApplication
{
	EngineApplicationArguments* arguments;
	ScriptingSubsystem* scripting_subsystem;
	ECS_Registry* ecs_registry;
	PlatformData* platform_data;
	GameLevel* default_level;
	AssetManager* asset_manager;
} EngineApplication;

/**
 * @brief Creates an EngineApplication with the provided application arguments.
 *
 * Initializes the EngineApplication structure.
 *
 * @param argc: Number of command-line arguments.
 * @param argv: Array of command-line argument strings.
 * @param out_engine_application: Pointer to address to be filled with the EngineApplication structure
 * 
 * @returns True if the EngineApplication structure is created, false otherside.
 */
bool EngineApplication_Create(const int argc, const char** argv, EngineApplication** out_engine_application);

bool EngineApplication_Initialize(EngineApplication* engine_application);

void EngineApplication_Run(const EngineApplication* application);

/**
 * @brief Frees the resources allocated for the EngineApplication structure.
 *
 * This function deallocates memory and cleans up all resources used by the EngineApplication structure.
 *
 * @param application: Pointer to the EngineApplication instance to be freed.
 */
void EngineApplication_Free(EngineApplication** application);