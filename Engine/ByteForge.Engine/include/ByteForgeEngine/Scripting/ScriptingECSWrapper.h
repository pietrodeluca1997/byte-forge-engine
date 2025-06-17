#pragma once

#include "ByteForgeEngine/Application/EngineApplication.h"

/**
 * @brief Registers the ECS (Entity-Component-System) system with the scripting subsystem.
 *
 * This function registers the ECS system, which may include setting up scripting bindings,
 * exposing ECS-related functionality to the scripting subsystem, and initializing necessary
 * components for interacting with the ECS from scripts.
 *
 * @param engine_application A pointer to the `EngineApplication` structure, which contains information
 *                           about the engine's state, scripting subsystem, and ECS registry.
 */
void ScriptingECSWrapper_Register(const EngineApplication* const engine_application);