#pragma once

#include "PlatformSettingsData.h"
#include "PlatformWindowData.h"

#include <SDL3/SDL.h>

/**
 * @brief Holds platform-specific data including SDL objects, settings, and window configuration.
 */
typedef struct PlatformData
{
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    SDL_GLContext opengl_context;
    PlatformSettingsData* settings_data;
    PlatformWindowData* window_data;
} PlatformData;

/**
 * @brief Creates a PlatformData instance empty.
 *
 * @param out_platform_data: Pointer to the output PlatformData instance.
 *
 * @return True if the instance was created successfully, false otherwise.
 */
bool PlatformData_Create(PlatformData** out_platform_data);

/**
 * @brief Frees the memory associated with a PlatformData instance, including its settings and window data.
 *
 * @param platform_data: Pointer to the PlatformData instance to be freed. Must not be NULL.
 */
void PlatformData_Free(PlatformData** platform_data);
