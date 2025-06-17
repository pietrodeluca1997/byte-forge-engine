#include "ByteForgeEngine/Application/EngineApplication.h"
#include "ByteForgeEngine/Application/EngineApplicationPresenter.h"
#include "ByteForgeEngine/Configuration/EnginePlatformConfiguration.h"
#include "ByteForgeEngine/Configuration/GameStartupConfiguration.h"
#include "ByteForgeEngine/Levels/GameLevelManager.h"
#include "ByteForgeEngine/Scripting/ScriptingECSWrapper.h"

#include <OpenGL/OpenGLRenderer.h>

#include <ByteForgeLogging.h>
#include <ByteForgeMemory.h>
#include <ByteForgePlatform.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <SDL3/SDL_events.h>

static void EngineApplication_HandleInput(const SDL_Event* event, const EngineApplication* application)
{
	lua_State* L = application->scripting_subsystem->lua_state;

	switch (event->type)
	{
		case SDL_EVENT_KEY_DOWN:
		{
			ScriptingSubsystem_Call(application->scripting_subsystem, "OnKey", 2, SCRIPTING_STRING_TYPE, SDL_GetKeyName(event->key.key), SCRIPTING_BOOLEAN_TYPE, true);
			break;
		}
		case SDL_EVENT_KEY_UP:
		{
			ScriptingSubsystem_Call(application->scripting_subsystem, "OnKey", 2, SCRIPTING_STRING_TYPE, SDL_GetKeyName(event->key.key), SCRIPTING_BOOLEAN_TYPE, false);
			break;
		}
		case SDL_EVENT_MOUSE_MOTION:
		{
			ScriptingSubsystem_Call(application->scripting_subsystem, "OnMouseMotion", 2, SCRIPTING_NUMBER_TYPE, event->motion.x, SCRIPTING_NUMBER_TYPE, event->motion.y);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			const char* button = (event->button.button == SDL_BUTTON_LEFT) ? "Left" : (event->button.button == SDL_BUTTON_RIGHT) ? "Right" : "Middle";
			ScriptingSubsystem_Call(application->scripting_subsystem, "OnMouseButton", 2, SCRIPTING_STRING_TYPE, button, SCRIPTING_BOOLEAN_TYPE, true);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			const char* button = (event->button.button == SDL_BUTTON_LEFT) ? "Left" : (event->button.button == SDL_BUTTON_RIGHT) ? "Right" : "Middle";
			ScriptingSubsystem_Call(application->scripting_subsystem, "OnMouseButton", 2, SCRIPTING_STRING_TYPE, button, SCRIPTING_BOOLEAN_TYPE, false);
			break;
		}
		default:
		{
			break;
		}
	}
}

bool EngineApplication_Create(const int argc, const char** argv, EngineApplication** out_engine_application)
{
	EngineApplication* engine_application = ALLOC(EngineApplication, MEMORY_ALLOCATION_CATEGORY_ENGINE_APPLICATION);

	if (!engine_application)
	{
		LOG_FATAL("Error when trying to allocate memory for engine application.");
		return false;
	}

	EngineApplication* arguments = NULL;
	
	if (!EngineApplicationArguments_Create(argc, argv, &arguments))
	{
		LOG_FATAL("Error when trying to create EngineApplicationArguments instance.");
		return false;
	}

	AssetManager* asset_manager = NULL;
	if (!AssetManager_Create(&asset_manager))
	{
		LOG_FATAL("Error when trying to create asset manager instance.");
		return false;
	}

	engine_application->arguments = arguments;
	engine_application->asset_manager = asset_manager;

	*out_engine_application = engine_application;

	return true;
}

bool EngineApplication_Initialize(EngineApplication* engine_application)
{
	if (!ScriptingSubsystem_Create(&engine_application->scripting_subsystem)) return false;

	if (!ECS_Registry_Create(&engine_application->ecs_registry)) return false;
	
	if (!EnginePlatformConfiguration_LoadFromConfigurationFile(engine_application->scripting_subsystem, &engine_application->platform_data)) return false;
		
	if (!GameStartupConfiguration_LoadStartupLevel(engine_application->scripting_subsystem, &engine_application->default_level)) return false;

	if (!PlatformOpenGLContext_Initialize(engine_application->platform_data)) return false;

	if (!GameLevelManager_LoadLevel(engine_application->scripting_subsystem, engine_application->default_level)) return false;

	ScriptingECSWrapper_Register(engine_application);

	if (!GameLevelManager_SetupLevel(engine_application->scripting_subsystem, engine_application->default_level)) return false;

	return true;
}

void EngineApplication_Run(const EngineApplication* application)
{
	GameLevelManager_StartLevel(application->scripting_subsystem, &application->default_level);

	PlatformFrameManager frame_manager = PlatformFrameManager_Create(application->platform_data->settings_data->target_frame_time_in_ms);

	while (PlatformContext_PollThreadEvents(EngineApplication_HandleInput, application))
	{
		PlatformFrameManager_StartFrame(&frame_manager);

		PlatformOpenGLContext_SetBackgroundColor(application->platform_data, 21, 21, 21, 255);

		GameLevelManager_UpdateLevel(application->scripting_subsystem, &application->default_level, frame_manager.delta_time);

		ECS_Registry_Update(application->ecs_registry, frame_manager.delta_time);

		ECS_Registry_SpawnEntities(application->ecs_registry);
		
		PlatformOpenGLContext_SwapBuffers(application->platform_data);

		ECS_Registry_KillEntities(application->ecs_registry);

		PlatformFrameManager_EndFrame(&frame_manager);
	}

	GameLevelManager_QuitLevel(application->scripting_subsystem, &application->default_level);
}

void EngineApplication_Free(EngineApplication** application)
{
	GameLevelManager_UnloadLevel(&(*application)->default_level);

	ScriptingSubsystem_Free(&(*application)->scripting_subsystem);

	AssetManager_Free(&(*application)->asset_manager);

	PlatformContext_Free((*application)->platform_data);
	PlatformData_Free(&(*application)->platform_data);

	ECS_Registry_Free(&(*application)->ecs_registry);
	
	EngineApplicationArguments_Free(&(*application)->arguments);
	FREE(application, sizeof(EngineApplication), MEMORY_ALLOCATION_CATEGORY_ENGINE_APPLICATION);

	MemoryUsageReport_PrintInfo();

	MemoryUsageReport_Exit();
}
