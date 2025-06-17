#pragma once

#define OPENGL_RENDER_2D_SYSTEM_NAME "OpenGLRender2DSystem"

#include "ECS/ECS_Registry.h"
#include "ECS/ECS_System.h"
#include "ECS/ECS_ComponentType.h"

#include <OpenGL/OpenGLRenderer.h>

typedef struct OpenGLRender2DSystem
{
    ECS_ComponentType* transform_2d_component;
    ECS_ComponentType* sprite_2d_component;
    ECS_ComponentType* animated_sprite_2d_component;
    ECS_ComponentType* parallax_sprite_2d_component;
    OpenGLVertexArray opengl_vertex_array;
} OpenGLRender2DSystem;

OpenGLRender2DSystem* OpenGLRender2DSystem_New(ECS_ComponentType* transform_2d_component, ECS_ComponentType* sprite_2d_component, ECS_ComponentType* animated_sprite_2d_component, ECS_ComponentType* parallax_sprite_2d_component);

void OpenGLRender2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time);

void OpenGLRender2DSystem_Free(OpenGLRender2DSystem** opengl_render_2d_system);