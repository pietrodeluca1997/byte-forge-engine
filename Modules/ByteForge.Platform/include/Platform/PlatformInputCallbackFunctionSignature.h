#pragma once

#include <SDL3/SDL.h>

/**
 * @brief Callback function signature for handling input events.
 *
 * @param keyboard_state: Pointer to the platform event data
 */
typedef void (*PlatformInputCallbackFunctionSignature)(const SDL_Event* event, const void* application_data);