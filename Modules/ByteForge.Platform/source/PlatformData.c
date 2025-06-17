#include "Platform/PlatformData.h"

#include <ByteForgeLogging.h>
#include <ByteForgeMemory.h>

bool PlatformData_Create(PlatformData** out_platform_data)
{
    LOG_INFO("Creating platform data:");

	PlatformData* platform_data = ALLOC(PlatformData, MEMORY_ALLOCATION_CATEGORY_PLATFORM);

	if (!platform_data)
	{
		LOG_FATAL("Error when trying to allocate memory for platform data structure.");
		return false;
	}

	*out_platform_data = platform_data;

	LOG_SUCCESS("\t - Platform data structure created successfully.");
    LOG_NEW_LINE();

	return true;
}

void PlatformData_Free(PlatformData** platform_data)
{
    LOG_INFO("Freeing platform data structure...");

	if (!platform_data || !*platform_data) 
	{
		LOG_WARNING("\t - Warning: Attempted to free a NULL platform data structure.");
		return;
	}

    PlatformData* platform_data_deref = *platform_data;

    if (platform_data_deref->settings_data) 
    {
        LOG_INFO("\t - Freeing settings data...");
        PlatformSettingsData_Free(&platform_data_deref->settings_data);
    }

    if (platform_data_deref->window_data) 
    {
        LOG_INFO("\t - Freeing window data...");
        PlatformWindowData_Free(&platform_data_deref->window_data);
    }

    LOG_INFO("\t - Freeing platform data structure...");

    FREE(platform_data, sizeof(PlatformData), MEMORY_ALLOCATION_CATEGORY_PLATFORM);

    LOG_SUCCESS("\t - Platform data structure freed successfully.");
    LOG_NEW_LINE();
}
