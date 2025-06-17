#pragma once

#include "PlatformData.h"

#include <stdbool.h>

/**
 * @brief Initializes the platform context, setting up the necessary resources with OpenGL.
 *
 * @param platform_data: Pointer to the platform data required to initialize. Must not be NULL.
 * @return true if initialization succeeds, false otherwise.
 */
bool PlatformOpenGLContext_Initialize(PlatformData* platform_data);


/**
 * @brief Swaps the rendering buffers for the current platform context with OpenGL.
 *
 * @param platform_data: Pointer to the PlatformData instance containing the rendering context. Must not be NULL.
 */
void PlatformOpenGLContext_SwapBuffers(const PlatformData* const platform_data);


/**
 * @brief Sets the background color for the rendering context with OpenGL.
 *
 * @param platform_data: Pointer to the PlatformData instance containing the rendering context. Must not be NULL.
 * @param r: Red component of the color (0-255).
 * @param g: Green component of the color (0-255).
 * @param b: Blue component of the color (0-255).
 * @param a: Alpha component of the color (0-255).
 */
void PlatformOpenGLContext_SetBackgroundColor(const PlatformData* const platform_data, const int r, const int g, const int b, const int a);
