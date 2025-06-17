#pragma once

#include <stdbool.h>

/**
 * @brief Holds platform-specific settings for the window, such as title, width, and height.
 */
typedef struct PlatformWindowData
{
    char* window_title;
    int window_width;
    int window_height;
} PlatformWindowData;

/**
 * @brief Creates a PlatformWindowData instance with the specified parameters.
 *
 * @param window_title:                The title of the window. Must not be NULL.
 * @param window_width:                The desired width of the window in pixels. Must be greater than zero.
 * @param window_height:               The desired height of the window in pixels. Must be greater than zero.
 * @param out_platform_window_data:    Pointer to the output PlatformWindowData instance. Must not be NULL.
 *
 * @return True if the structure was successfully created; false otherwise.
 */
bool PlatformWindowData_Create(const char* window_title, const int window_width, const int window_height, PlatformWindowData** out_platform_window_data);

/**
 * @brief Frees the memory associated with a PlatformWindowData instance.
 *
 * @param platform_window_data: Pointer to the PlatformWindowData instance to be freed. Must not be NULL.
 */
void PlatformWindowData_Free(PlatformWindowData** platform_window_data);
