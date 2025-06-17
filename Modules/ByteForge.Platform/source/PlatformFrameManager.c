#include "Platform/PlatformFrameManager.h"

#include <SDL3/SDL.h>

static void PlatformFrameManager_CalculateDeltaTime(PlatformFrameManager* platform_frame_manager)
{
	platform_frame_manager->delta_time = (platform_frame_manager->current_frame_end_tick_count - platform_frame_manager->last_frame_tick_count) / 1000.0f;
	platform_frame_manager->last_frame_tick_count = platform_frame_manager->current_frame_end_tick_count;
}

static void PlatformFrameManager_HandleFrameTiming(PlatformFrameManager* platform_frame_manager)
{
	const uint32_t frame_duration = (uint32_t)(platform_frame_manager->current_frame_end_tick_count - platform_frame_manager->current_frame_start_tick_count);
		
	if (frame_duration < platform_frame_manager->target_frame_time_in_ms)
	{
		SDL_Delay((uint32_t)platform_frame_manager->target_frame_time_in_ms - frame_duration);
	}
}

PlatformFrameManager PlatformFrameManager_Create(const double target_frame_time_in_ms)
{
	PlatformFrameManager frame_manager =
	{
		.delta_time = 0.0f,
		.last_frame_tick_count = SDL_GetTicks(),
		.target_frame_time_in_ms = target_frame_time_in_ms,
	};

	return frame_manager;
}

void PlatformFrameManager_StartFrame(PlatformFrameManager* platform_frame_manager)
{
	platform_frame_manager->current_frame_start_tick_count = SDL_GetTicks();
}

void PlatformFrameManager_EndFrame(PlatformFrameManager* platform_frame_manager)
{
	platform_frame_manager->current_frame_end_tick_count = SDL_GetTicks();

	PlatformFrameManager_CalculateDeltaTime(platform_frame_manager);
	PlatformFrameManager_HandleFrameTiming(platform_frame_manager);	
}