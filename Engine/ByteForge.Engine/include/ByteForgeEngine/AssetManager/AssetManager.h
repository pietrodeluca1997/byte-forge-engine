#pragma once

#include <Memory/Structures/Dictionary.h>
#include <Memory/Allocation/MemoryAllocationMacros.h>

#include <stdbool.h>

#include <SDL3/SDL_render.h>

typedef struct AssetManager
{
	Dictionary* textures_map;
} AssetManager;

bool AssetManager_Create(AssetManager** out_asset_manager);
uint32_t AssetManager_LoadTexture(AssetManager* manager, SDL_Renderer* renderer, const char* const texture_path);
void AssetManager_Free(AssetManager** asset_manager);