#pragma once

#define COLLISION_2D_SYSTEM_NAME "Collision2DSystem"

#include "ECS/ECS_Registry.h"
#include "ECS/ECS_System.h"
#include "ECS/ECS_ComponentType.h"

#include "ByteForgeEngine/Scripting/ScriptingSubsystem.h"

typedef struct Collision2DSystem
{
    ECS_ComponentType* transform_2d_component;
    ECS_ComponentType* box_collider_2d_component;
    ECS_ComponentType* physics_2d_component;
    ScriptingSubsystem* scripting_subsystem;
} Collision2DSystem;

Collision2DSystem* Collision2DSystem_New(ECS_ComponentType* transform_2d_component, ECS_ComponentType* box_collider_2d_component, ECS_ComponentType* physics_2d_component, ScriptingSubsystem* scripting_subsystem);

void Collision2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time);

void Collision2DSystem_Free(Collision2DSystem** collision_2d_system);