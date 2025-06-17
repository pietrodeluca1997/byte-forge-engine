#include "Platform/PlatformOpenGLContext.h"
#include <glad/glad.h>

#include <ByteForgeLogging.h>

bool PlatformOpenGLContext_Initialize(PlatformData* platform_data)
{
    LOG_INFO("Initializing platform context with OpenGL:");

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
        SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY
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

    LOG_INFO("\t - Creating platform OpenGL context...");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_SetWindowSurfaceVSync(window, 0);

    SDL_GLContext opengl_context = SDL_GL_CreateContext(window);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    platform_data->opengl_context = opengl_context;
    platform_data->sdl_window = window;
    platform_data->sdl_renderer = renderer;

    LOG_SUCCESS("\t - Platform context with OpenGL initialized successfully.");
    LOG_NEW_LINE();

    return true;
}

void PlatformOpenGLContext_SwapBuffers(const PlatformData* const platform_data)
{
    SDL_GL_SwapWindow(platform_data->sdl_window);
}

void PlatformOpenGLContext_SetBackgroundColor(const PlatformData* const platform_data, const int r, const int g, const int b, const int a)
{
    if (!platform_data || !platform_data->sdl_renderer)
    {
        LOG_ERROR("Error: Invalid platform_data or renderer pointer.");
        return;
    }

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}