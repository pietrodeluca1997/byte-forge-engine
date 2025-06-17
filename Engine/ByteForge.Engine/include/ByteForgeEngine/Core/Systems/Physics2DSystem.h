#pragma once

#define PHYSICS_2D_SYSTEM_NAME "Physics2DSystem"

#include "ECS/ECS_Registry.h"
#include "ECS/ECS_System.h"
#include "ECS/ECS_ComponentType.h"

typedef struct Physics2DSystem
{    
    ECS_ComponentType* transform_2d_component;
    ECS_ComponentType* physics_2d_component;
} Physics2DSystem;

Physics2DSystem* Physics2DSystem_New(ECS_ComponentType* transform_2d_component, ECS_ComponentType* physics_2d_component);

void Physics2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time);

void Physics2DSystem_Free(Physics2DSystem** physics_2d_system);