#include "ByteForgeEngine/AssetManager/AssetManager.h"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <glad/glad.h>

#include <string.h>

static bool AssetManager_IsTextureEqual(const char* first_texture_path, const char* second_texture_path)
{
    const char* first_texture_path_value = *(const char**)first_texture_path;
    const char* second_texture_path_value = *(const char**)second_texture_path;
    return strcmp(first_texture_path_value, second_texture_path_value) == 0;
}

bool AssetManager_Create(AssetManager** out_asset_manager)
{
	AssetManager* asset_manager = ALLOC(AssetManager, MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER);

	if (!asset_manager) return false;

	if (!Dictionary_Initialize(&asset_manager->textures_map, sizeof(const char*), sizeof(uint32_t), 10, AssetManager_IsTextureEqual, MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER)) return false;
	
    *out_asset_manager = asset_manager;

	return true;
}

uint32_t AssetManager_LoadTexture(AssetManager* manager, SDL_Renderer* renderer, const char* const texture_path)
{
    uint32_t* existing_texture_id = Dictionary_Get(manager->textures_map, &texture_path);

    if (existing_texture_id != NULL)
    {
        return *existing_texture_id;
    }

    SDL_Surface* surface = IMG_Load(texture_path);

    if (surface == NULL) 
    {
        return NULL;
    }


    uint32_t texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    SDL_DestroySurface(surface);

    Dictionary_AddOrUpdate(manager->textures_map, &texture_path, &texture_id, MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER);

    return texture_id;
}

void AssetManager_Free(AssetManager** asset_manager)
{
    glDeleteTextures((*asset_manager)->textures_map->value_size * (*asset_manager)->textures_map->count, (*asset_manager)->textures_map->values);
    Dictionary_Free(&(*asset_manager)->textures_map, MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER);
    FREE(asset_manager, sizeof(AssetManager), MEMORY_ALLOCATION_CATEGORY_ASSET_MANAGER);
}
