#pragma once

#include "PlatformInputCallbackFunctionSignature.h"
#include "PlatformData.h"

#include <stdbool.h>

/**
 * @brief Initializes the platform context, setting up the necessary resources.
 *
 * @param platform_data: Pointer to the platform data required to initialize. Must not be NULL.
 * @return true if initialization succeeds, false otherwise.
 */
bool PlatformContext_Initialize(PlatformData* platform_data);

/**
 * @brief Polls for platform events in the current thread and processes input.
 *
 * @param handle_input_callback: Optional callback function to handle keyboard input events. Can be NULL.
 * @param application_data: Custom application data to send to the input callback.
 * @return true if polling succeeds, false if an error occurs or the application should exit.
 */
bool PlatformContext_PollThreadEvents(const PlatformInputCallbackFunctionSignature handle_input_callback, const void* application_data);

/**
 * @brief Swaps the rendering buffers for the current platform context.
 *
 * @param platform_data: Pointer to the PlatformData instance containing the rendering context. Must not be NULL.
 */
void PlatformContext_SwapBuffers(const PlatformData* const platform_data);

/**
 * @brief Sets the background color for the rendering context.
 *
 * @param platform_data: Pointer to the PlatformData instance containing the rendering context. Must not be NULL.
 * @param r: Red component of the color (0-255).
 * @param g: Green component of the color (0-255).
 * @param b: Blue component of the color (0-255).
 * @param a: Alpha component of the color (0-255).
 */
void PlatformContext_SetBackgroundColor(const PlatformData* const platform_data, const int r, const int g, const int b, const int a);

/**
 * @brief Frees the resources associated with the platform context.
 *
 * @param platform_data: Pointer to the PlatformData instance to be freed. Can be NULL.
 */
void PlatformContext_Free(PlatformData* platform_data);
