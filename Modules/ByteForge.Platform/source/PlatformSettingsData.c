#include "Platform/PlatformSettingsData.h"

#include <ByteForgeLogging.h>
#include <ByteForgeMemory.h>

#define MINIMUM_TARGET_FPS_REQUIRED 30

bool PlatformSettingsData_Create(const uint8_t target_fps, PlatformSettingsData** out_platform_settings_data)
{
	LOG_INFO("Creating platform settings data:");

	if (target_fps < MINIMUM_TARGET_FPS_REQUIRED)
	{
		LOG_FATAL("\t - Target fps must be greater or equal to %d.", MINIMUM_TARGET_FPS_REQUIRED);
		return false;
	}
	
	PlatformSettingsData* platform_settings = ALLOC(PlatformSettingsData, MEMORY_ALLOCATION_CATEGORY_PLATFORM);

	if (!platform_settings)
	{
		LOG_FATAL("\t - Error when trying to allocate memory for platform settings data structure.");
		return false;
	}

	platform_settings->target_fps = target_fps;
	platform_settings->target_frame_time_in_ms = 1000.f / target_fps;

	*out_platform_settings_data = platform_settings;

	LOG_SUCCESS("\t - Platform settings data created successfully with target FPS: %d.", target_fps);
	LOG_NEW_LINE();

	return true;
}

void PlatformSettingsData_Free(PlatformSettingsData** platform_settings_data)
{
	LOG_INFO("Freeing platform settings data structure...");

	if (!platform_settings_data || !*platform_settings_data)
	{
		LOG_WARNING("\t - Warning: Attempted to free a NULL platform settings data structure.");
		return;
	}

	FREE(platform_settings_data, sizeof(PlatformSettingsData), MEMORY_ALLOCATION_CATEGORY_PLATFORM);

	LOG_SUCCESS("\t - Platform settings data structure freed successfully.");
	LOG_NEW_LINE();
}
