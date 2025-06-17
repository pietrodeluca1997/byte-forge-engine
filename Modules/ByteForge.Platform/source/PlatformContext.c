#include "Platform/PlatformContext.h"

#include <stdlib.h>

#include <ByteForgeLogging.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>

bool PlatformContext_Initialize(PlatformData* platform_data)
{
    LOG_INFO("Initializing platform context:");

    if (!platform_data)
    {
        LOG_FATAL("Error: Invalid platform_data pointer (NULL).");
        return false;
    }

    if (!platform_data->window_data)
    {
        LOG_FATAL("Error: Invalid platform_data->window_data pointer (NULL).");
        return false;
    }

    LOG_INFO("\t - Initializing video subsystem...");

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        LOG_FATAL("Error: Video subsystem failed to initialized. SDL message: %s.", SDL_GetError());
        return false;
    }

    LOG_INFO("\t - Initializing events subsystem...");

    if (!SDL_InitSubSystem(SDL_INIT_EVENTS))
    {
        LOG_FATAL("Error: Events subsystem failed to initialized. SDL message: %s.", SDL_GetError());
        return false;
    }

    LOG_INFO("\t - Creating platform window...");
    SDL_Window* window = SDL_CreateWindow(
        platform_data->window_data->window_title,
        platform_data->window_data->window_width,
        platform_data->window_data->window_height,
        SDL_WINDOW_HIGH_PIXEL_DENSITY
    );

    if (!window)
    {
        LOG_FATAL("Error: Unable to create platform window. SDL message: %s.", SDL_GetError());
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return false;
    }

    LOG_INFO("\t - Creating platform renderer...");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        LOG_FATAL("Error: Unable to create platform renderer. SDL message: %s.", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return false;
    }
    
    platform_data->sdl_window = window;
    platform_data->sdl_renderer = renderer;

    LOG_SUCCESS("\t - Platform context initialized successfully.");
    LOG_NEW_LINE();

    return true;
}



bool PlatformContext_PollThreadEvents(const PlatformInputCallbackFunctionSignature handle_input_callback, void* application_data)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (handle_input_callback)
        {
            handle_input_callback(&event, application_data);
        }

        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                LOG_WARNING("Application shutdown requested through platform...");
                LOG_NEW_LINE();
                return false;
            }
        }
    }

    const uint8_t* keyboard_state = (const uint8_t*) SDL_GetKeyboardState(NULL);

    if (!keyboard_state) 
    {
        LOG_ERROR("Error: Unable to retrieve keyboard state.");
        return true;
    }

    if (keyboard_state[SDL_SCANCODE_ESCAPE])
    {
        LOG_WARNING("Application shutdown requested through \"ESC\" command key...");
        LOG_NEW_LINE();
        return false;
    }


    return true;
}

void PlatformContext_SwapBuffers(const PlatformData* const platform_data)
{
    if (!platform_data) 
    {
        LOG_ERROR("Error: Invalid platform_data pointer.");
        return;
    }

    if (!platform_data->sdl_renderer)
    {
        LOG_ERROR("Error: Invalid renderer pointer.");
        return;
    }

    SDL_RenderPresent(platform_data->sdl_renderer);
}

void PlatformContext_SetBackgroundColor(const PlatformData* const platform_data, const int r, const int g, const int b, const int a)
{
    if (!platform_data || !platform_data->sdl_renderer)
    {
        LOG_ERROR("Error: Invalid platform_data or renderer pointer.");
        return;
    }

    SDL_SetRenderDrawColor(platform_data->sdl_renderer, r, g, b, a);
    SDL_RenderClear(platform_data->sdl_renderer);
}

void PlatformContext_SetOpenGLBackgroundColor(const PlatformData* const platform_data, const int r, const int g, const int b, const int a)
{
    if (!platform_data || !platform_data->sdl_renderer)
    {
        LOG_ERROR("Error: Invalid platform_data or renderer pointer.");
        return;
    }
       
    glViewport(0, 0, platform_data->window_data->window_width, platform_data->window_data->window_height);
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PlatformContext_Free(PlatformData* platform_data)
{
    LOG_WARNING("Cleaning platform context resources...");

    if (!platform_data)
    {
        LOG_WARNING("Warning: Attempted to free a NULL platform data structure.");
        return;
    }

    if (platform_data->opengl_context)
    {
        LOG_WARNING("\t - Disposing platform OpenGL context...");
        SDL_GL_DestroyContext(platform_data->opengl_context);
    }

    if (platform_data->sdl_renderer)
    {
        LOG_WARNING("\t - Disposing platform renderer...");
        SDL_DestroyRenderer(platform_data->sdl_renderer);
        platform_data->sdl_renderer = NULL;
    }

    if (platform_data->sdl_window)
    {
        LOG_WARNING("\t - Disposing platform window...");
        SDL_DestroyWindow(platform_data->sdl_window);
        platform_data->sdl_window = NULL;
    }

    LOG_WARNING("\t - Shutting down video subsytem...");
	SDL_QuitSubSystem(SDL_INIT_VIDEO);

    LOG_WARNING("\t - Shutting down events subsytem...");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    LOG_WARNING("\t - Shutting down platform...");
	SDL_Quit();

    LOG_SUCCESS("Platform context freed successfully.");
}