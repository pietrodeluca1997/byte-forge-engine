#pragma once

#include <stdint.h>

/**
 * @brief Manages frame timing and performance for the platform.
 */
typedef struct PlatformFrameManager
{
	uint64_t last_frame_tick_count;
	uint64_t current_frame_start_tick_count;
	uint64_t current_frame_end_tick_count;
	double delta_time;
	double target_frame_time_in_ms;
} PlatformFrameManager;

/**
 * @brief Creates a PlatformFrameManager instance with the specified target frame time.
 *
 * @param target_frame_time_in_ms: Target frame duration in milliseconds. Must be greater than zero.
 *
 * @return Initialized PlatformFrameManager struct.
 */
PlatformFrameManager PlatformFrameManager_Create(const double target_frame_time_in_ms);

/**
 * @brief Marks the start of a new frame, recording the starting tick count.
 *
 * @param platform_frame_manager: Pointer to the PlatformFrameManager instance. Must not be NULL.
 */
void PlatformFrameManager_StartFrame(PlatformFrameManager* platform_frame_manager);

/**
 * @brief Marks the end of the current frame, recording the ending tick count and updating delta time.
 *
 * @param platform_frame_manager: Pointer to the PlatformFrameManager instance. Must not be NULL.
 */
void PlatformFrameManager_EndFrame(PlatformFrameManager* platform_frame_manager);
