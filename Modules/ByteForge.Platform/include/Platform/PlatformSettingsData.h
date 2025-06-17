#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Structure that holds platform-specific settings such as target FPS and frame time.
 */
typedef struct PlatformSettingsData
{
    uint8_t target_fps;
    double target_frame_time_in_ms;
} PlatformSettingsData;

/**
 * @brief Creates a PlatformSettingsData instance with the specified target FPS.
 *
 * @param target_fps:                  The desired target frames per second. Must be greater than zero.
 * @param out_platform_settings_data:  Pointer to the output PlatformSettingsData instance. Must not be NULL.
 *
 * @return True if the instance was created successfully, false otherwise.
 */
bool PlatformSettingsData_Create(const uint8_t target_fps, PlatformSettingsData** out_platform_settings_data);

/**
 * @brief Frees the memory associated with a PlatformSettingsData instance.
 *
 * @param platform_settings_data: Pointer to the PlatformSettingsData instance to be freed. Must not be NULL.
 */
void PlatformSettingsData_Free(PlatformSettingsData** platform_settings_data);
