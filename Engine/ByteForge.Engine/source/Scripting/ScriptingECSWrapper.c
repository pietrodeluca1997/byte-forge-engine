#include "ByteForgeEngine/Scripting/ScriptingECSWrapper.h"
#include "ByteForgeEngine/Core/Components/Transform2DComponent.h"
#include "ByteForgeEngine/Core/Components/Sprite2DComponent.h"
#include "ByteForgeEngine/Core/Components/AnimatedSprite2DComponent.h"
#include "ByteForgeEngine/Core/Components/ParallaxSprite2DComponent.h"
#include "ByteForgeEngine/Core/Systems/Render2DSystem.h"
#include "ByteForgeEngine/Core/Systems/OpenGLRender2DSystem.h"

#include "ByteForgeEngine/Core/Components/Physics2DComponent.h"
#include "ByteForgeEngine/Core/Systems/Physics2DSystem.h"
#include "ByteForgeEngine/Core/Components/BoxCollider2DComponent.h"
#include "ByteForgeEngine/Core/Systems/Collision2DSystem.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <SDL3_image/SDL_image.h>

#include <ByteForgeLogging.h>
#include <ByteForgeECS.h>
#include <Memory/Helpers/MemoryStructureHelper.h>

static const char* const SCRIPTING_TABLE_ECS = "ECS";
static const char* const EMBEDDED_APPLICATION_DATA = "Engine_Application";

static const char* const SCRIPTING_FUNCTION_PRINT_INFO = "PrintInfo";
static const char* const SCRIPTING_FUNCTION_CREATE_ENTITY = "CreateEntity";
static const char* const SCRIPTING_FUNCTION_KILL_ENTITY = "KillEntity";
static const char* const SCRIPTING_FUNCTION_ADD_TRANSFORM2D_COMPONENT = "AddTransform2DComponent";
static const char* const SCRIPTING_FUNCTION_ADD_SPRITE2D_COMPONENT = "AddSprite2DComponent";
static const char* const SCRIPTING_FUNCTION_ADD_PHYSICS2D_COMPONENT = "AddPhysics2DComponent";
static const char* const SCRIPTING_FUNCTION_ADD_ANIMATED_SPRITE2D_COMPONENT = "AddAnimatedSprite2DComponent";
static const char* const SCRIPTING_FUNCTION_ADD_PARALLAX_SPRITE2D_COMPONENT = "AddParallaxSprite2DComponent";
static const char* const SCRIPTING_FUNCTION_ADD_BOX_COLLIDER2D_COMPONENT = "AddBoxCollider2DComponent";
static const char* const SCRIPTING_FUNCTION_REGISTER_TRANSFORM2D_COMPONENT = "RegisterTransform2DComponent";
static const char* const SCRIPTING_FUNCTION_REGISTER_SPRITE2D_COMPONENT = "RegisterSprite2DComponent";
static const char* const SCRIPTING_FUNCTION_REGISTER_ANIMATED_SPRITE2D_COMPONENT = "RegisterAnimatedSprite2DComponent";
static const char* const SCRIPTING_FUNCTION_REGISTER_PARALLAX_SPRITE2D_COMPONENT = "RegisterParallaxSprite2DComponent";
static const char* const SCRIPTING_FUNCTION_REGISTER_PHYSICS2D_COMPONENT = "RegisterPhysics2DComponent";
static const char* const SCRIPTING_FUNCTION_REGISTER_BOX_COLLIDER2D_COMPONENT = "RegisterBoxCollider2DComponent";
static const char* const SCRIPTING_FUNCTION_ADD_RENDER2D_SYSTEM = "AddRender2DSystem";
static const char* const SCRIPTING_FUNCTION_ADD_OPENGL_RENDER2D_SYSTEM = "AddOpenGLRender2DSystem";
static const char* const SCRIPTING_FUNCTION_ADD_PHYSICS2D_SYSTEM = "AddPhysics2DSystem";
static const char* const SCRIPTING_FUNCTION_ADD_COLLISION2D_SYSTEM = "AddCollision2DSystem";
static const char* const SCRIPTING_FUNCTION_PUBLISH_ENTITY = "PublishEntity";
static const char* const SCRIPTING_FUNCTION_GET_TRANSFORM2D_COMPONENT = "GetTransform2DComponent";
static const char* const SCRIPTING_FUNCTION_UPDATE_TRANSFORM2D_COMPONENT = "UpdateTransform2DComponent";
static const char* const SCRIPTING_FUNCTION_UPDATE_PHYSICS2D_COMPONENT = "UpdatePhysics2DComponent";

static EngineApplication* ScriptingECSWrapper_GetEngineApplicationByContext(lua_State* lua_state)
{
    return ScriptingSubsystem_GetUserdataByGlobalName(lua_state, EMBEDDED_APPLICATION_DATA);
}

static int ScriptingECSWrapper_CreateEntity(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Entity new_entity = { 0 };
	ECS_Registry_CreateEntity(application->ecs_registry, &new_entity);

    ScriptingSubsystem_PushInteger(lua_state, new_entity.id);

	return 1;
}

static int ScriptingECSWrapper_KillEntity(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Entity entity = { luaL_checkinteger(lua_state, 1) };

    ECS_Registry_AddEntityToKillQueue(application->ecs_registry, entity);

    return 0;
}


static int ScriptingECSWrapper_PrintInfo(lua_State* lua_state)
{   
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_PrintInfo(application->ecs_registry);

    return 0;
}

static bool ScriptingECSWrapper_GetVector2D(lua_State* lua_state, const int table_index, const char* field_name, Vector2* out_vector)
{
    lua_getfield(lua_state, table_index, field_name);

    if (lua_istable(lua_state, -1)) 
    {
        lua_getfield(lua_state, -1, "x");
        out_vector->x = (float)luaL_optnumber(lua_state, -1, 0.0f);
        lua_pop(lua_state, 1);

        lua_getfield(lua_state, -1, "y");
        out_vector->y = (float)luaL_optnumber(lua_state, -1, 0.0f);
        lua_pop(lua_state, 1);
    }

    lua_pop(lua_state, 1);
    return true;
}

static int ScriptingECSWrapper_AddTransform2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);

    Transform2DComponent component_data = { 0 };
        
    ScriptingECSWrapper_GetVector2D(lua_state, 2, "position", &component_data.position);
    ScriptingECSWrapper_GetVector2D(lua_state, 2, "size", &component_data.size);

    ECS_Registry_AddComponentToEntity(application->ecs_registry, component_type, &component_data, entity);

    return 0;
}

static int ScriptingECSWrapper_AddPhysics2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PHYSICS_2D_COMPONENT_NAME);

    Physics2DComponent component_data = { 0 };

    ScriptingECSWrapper_GetVector2D(lua_state, 2, "velocity", &component_data.velocity);

    ECS_Registry_AddComponentToEntity(application->ecs_registry, component_type, &component_data, entity);

    return 0;
}

static int ScriptingECSWrapper_AddAnimatedSprite2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, ANIMATED_SPRITE_2D_COMPONENT_NAME);

    AnimatedSprite2DComponent component_data = { 0 };
    
    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);

    luaL_checktype(lua_state, 2, LUA_TTABLE);

    component_data.current_frame = 0;
    component_data.desired_frame_rate = (float)luaL_checknumber(lua_state, 3);

    DynamicArray_Initialize(&component_data.animation_textures, sizeof(uint32_t), 5, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

    lua_pushnil(lua_state);
    while (lua_next(lua_state, 2) != 0)
    {
        const char* texture_path = luaL_checkstring(lua_state, -1);

        uint32_t texture_id = AssetManager_LoadTexture(application->asset_manager, application->platform_data->sdl_renderer, texture_path);

        DynamicArray_Add(component_data.animation_textures, &texture_id, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

        lua_pop(lua_state, 1);
    }

    ECS_Registry_AddComponentToEntity(application->ecs_registry, component_type, &component_data, entity);
}

static int ScriptingECSWrapper_AddBoxCollider2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, BOX_COLLIDER_2D_COMPONENT_NAME);

    BoxCollider2DComponent component_data = { 0 };

    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);

    luaL_checktype(lua_state, 2, LUA_TTABLE);
    int texture_table_index = 2;

    ScriptingECSWrapper_GetVector2D(lua_state, 2, "size", &component_data.collision_box);

    lua_getfield(lua_state, 2, "on_collision");
    if (lua_isfunction(lua_state, -1))
    {
        component_data.on_collision_script_function = luaL_ref(lua_state, LUA_REGISTRYINDEX);
    }
    else
    {
        component_data.on_collision_script_function = LUA_NOREF;
    }
    lua_pop(lua_state, 1);

    ECS_Registry_AddComponentToEntity(application->ecs_registry, component_type, &component_data, entity);
}

static int ScriptingECSWrapper_AddParallaxSprite2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PARALLAX_SPRITE_2D_COMPONENT_NAME);

    ParallaxSprite2DComponent component_data = { 0 };

    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);
        
    DynamicArray_Initialize(&component_data.animation_textures, sizeof(ParallaxTexture), 5, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

    component_data.scroll_speed = luaL_checknumber(lua_state, 2);

    lua_pushnil(lua_state);
    while (lua_next(lua_state, 3) != 0)
    {
        luaL_checktype(lua_state, -1, LUA_TTABLE);

        ParallaxTexture parallax_texture = { 0 };

        lua_getfield(lua_state, -1, "path");
        const char* texture_path = luaL_checkstring(lua_state, -1);
        lua_pop(lua_state, 1);

        ScriptingECSWrapper_GetVector2D(lua_state, -1, "offset", &parallax_texture.offset);
                       
        parallax_texture.texture_id = AssetManager_LoadTexture(application->asset_manager, application->platform_data->sdl_renderer, texture_path);

        DynamicArray_Add(component_data.animation_textures, &parallax_texture, MEMORY_ALLOCATION_CATEGORY_ECS_COMPONENT_TYPE);

        lua_pop(lua_state, 1);
    }

    ECS_Registry_AddComponentToEntity(application->ecs_registry, component_type, &component_data, entity);

    return 0;
}

static int ScriptingECSWrapper_AddSprite2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, SPRITE_2D_COMPONENT_NAME);

    Sprite2DComponent component_data = { 0 };

    lua_getfield(lua_state, 2, "texture");
    if (lua_istable(lua_state, -1)) 
    {
        lua_getfield(lua_state, -1, "image_path");

        if (lua_isstring(lua_state, -1))
        {
            component_data.texture_id = AssetManager_LoadTexture(application->asset_manager, application->platform_data->sdl_renderer, luaL_checkstring(lua_state, -1));
        }
        lua_pop(lua_state, 1);

        ScriptingECSWrapper_GetVector2D(lua_state, -1, "size", &component_data.texture_size);
    }
    lua_pop(lua_state, 1);

    ECS_Registry_AddComponentToEntity(application->ecs_registry, component_type, &component_data, entity);

    return 0;
}

static int ScriptingECSWrapper_RegisterTransform2DComponent(lua_State* lua_state)
{       
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);
    
    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(Transform2DComponent), TRANSFORM_2D_COMPONENT_NAME, NULL);

    return 0;
}

static int ScriptingECSWrapper_RegisterCollision2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(BoxCollider2DComponent), BOX_COLLIDER_2D_COMPONENT_NAME, NULL);

    return 0;
}

static int ScriptingECSWrapper_RegisterSprite2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(Sprite2DComponent), SPRITE_2D_COMPONENT_NAME, NULL);

    return 0;
}

static int ScriptingECSWrapper_RegisterPhysics2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(Physics2DComponent), PHYSICS_2D_COMPONENT_NAME, NULL);

    return 0;
}

static int ScriptingECSWrapper_RegisterAnimatedSprite2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(AnimatedSprite2DComponent), ANIMATED_SPRITE_2D_COMPONENT_NAME, AnimatedSprite2DComponent_Free);

    return 0;
}

static int ScriptingECSWrapper_RegisterParallaxSprite2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(ParallaxSprite2DComponent), PARALLAX_SPRITE_2D_COMPONENT_NAME, ParallaxSprite2DComponent_Free);

    return 0;
}

static int ScriptingECSWrapper_RegisterBoxCollider2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Registry_RegisterComponentType(application->ecs_registry, sizeof(BoxCollider2DComponent), BOX_COLLIDER_2D_COMPONENT_NAME, NULL);

    return 0;
}


static int ScriptingECSWrapper_AddRender2DSystem(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);
    ECS_ComponentType* transform_2D_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);
    ECS_ComponentType* sprite_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, SPRITE_2D_COMPONENT_NAME);
    ECS_ComponentType* animated_sprite_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, ANIMATED_SPRITE_2D_COMPONENT_NAME);
    ECS_ComponentType* parallax_sprite_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PARALLAX_SPRITE_2D_COMPONENT_NAME);
    ECS_ComponentType* box_collider_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, BOX_COLLIDER_2D_COMPONENT_NAME);

    Render2DSystem* render2d_system_data = Render2DSystem_New(application->platform_data->sdl_renderer, transform_2D_component, sprite_2d_component, animated_sprite_2d_component, parallax_sprite_2d_component, box_collider_2d_component);

    if (!render2d_system_data) return false;

    if (!ECS_Registry_CreateSystem(application->ecs_registry, (1ULL << transform_2D_component->id), RENDER_2D_SYSTEM_NAME, Render2DSystem_Update, Render2DSystem_Free, render2d_system_data)) return false;

    return 0;
}

static int ScriptingECSWrapper_AddOpenGLRender2DSystem(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);
    ECS_ComponentType* transform_2D_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);
    ECS_ComponentType* sprite_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, SPRITE_2D_COMPONENT_NAME);
    ECS_ComponentType* animated_sprite_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, ANIMATED_SPRITE_2D_COMPONENT_NAME);
    ECS_ComponentType* parallax_sprite_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PARALLAX_SPRITE_2D_COMPONENT_NAME);

    OpenGLRender2DSystem* opengl_render2d_system_data = OpenGLRender2DSystem_New(transform_2D_component, sprite_2d_component, animated_sprite_2d_component, parallax_sprite_2d_component);

    if (!opengl_render2d_system_data) return false;

    if (!ECS_Registry_CreateSystem(application->ecs_registry, (1ULL << transform_2D_component->id), OPENGL_RENDER_2D_SYSTEM_NAME, OpenGLRender2DSystem_Update, OpenGLRender2DSystem_Free, opengl_render2d_system_data)) return false;

    return 0;
}

static int ScriptingECSWrapper_AddCollision2DSystem(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);
    ECS_ComponentType* transform_2D_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);
    ECS_ComponentType* box_collider_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, BOX_COLLIDER_2D_COMPONENT_NAME);       
    ECS_ComponentType* physics_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PHYSICS_2D_COMPONENT_NAME);       

    Collision2DSystem* collision2d_system_data = Collision2DSystem_New(transform_2D_component, box_collider_2d_component, physics_2d_component, application->scripting_subsystem);

    if (!collision2d_system_data) return false;

    if (!ECS_Registry_CreateSystem(application->ecs_registry, (1ULL << transform_2D_component->id) | (1ULL << box_collider_2d_component->id), COLLISION_2D_SYSTEM_NAME, Collision2DSystem_Update, Collision2DSystem_Free, collision2d_system_data)) return false;

    return 0;
}

static int ScriptingECSWrapper_AddPhysics2DSystem(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);
    ECS_ComponentType* transform_2D_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);
    ECS_ComponentType* physics_2d_component = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PHYSICS_2D_COMPONENT_NAME);

    Physics2DSystem* physics_2d_system_data = Physics2DSystem_New(transform_2D_component, physics_2d_component);

    if (!physics_2d_system_data) return false;

    if (!ECS_Registry_CreateSystem(application->ecs_registry, (1ULL << transform_2D_component->id) | (1ULL << physics_2d_component->id), PHYSICS_2D_SYSTEM_NAME, Physics2DSystem_Update, Physics2DSystem_Free, physics_2d_system_data)) return false;

    return 0;
}

static int ScriptingECSWrapper_PublishEntity(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    ECS_Entity entity = { 0 };
    entity.id = luaL_checkinteger(lua_state, 1);

    ECS_Registry_PublishEntity(application->ecs_registry, entity);

    return 0;
}

static int ScriptingECSWrapper_UpdateTransform2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);
    
    uint64_t entity_id = (uint64_t)luaL_checkinteger(lua_state, 1);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);

    Transform2DComponent* component_data = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(component_type->entity_id_to_array_index_map, component_type->data_array, entity_id);    
    
    ScriptingECSWrapper_GetVector2D(lua_state, 2, "position", &component_data->position);    

    return 1;
}

static int ScriptingECSWrapper_UpdatePhysics2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    uint64_t entity_id = (uint64_t)luaL_checkinteger(lua_state, 1);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, PHYSICS_2D_COMPONENT_NAME);

    Physics2DComponent* component_data = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(component_type->entity_id_to_array_index_map, component_type->data_array, entity_id);

    ScriptingECSWrapper_GetVector2D(lua_state, 2, "velocity", &component_data->velocity);

    return 1;
}

static int ScriptingECSWrapper_GetTransform2DComponent(lua_State* lua_state)
{
    EngineApplication* application = ScriptingECSWrapper_GetEngineApplicationByContext(lua_state);

    uint64_t entity_id = (uint64_t)luaL_checkinteger(lua_state, 1);

    ECS_ComponentType* component_type = ECS_Registry_GetComponentTypeReferenceByName(application->ecs_registry, TRANSFORM_2D_COMPONENT_NAME);

    Transform2DComponent* component_data = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(component_type->entity_id_to_array_index_map, component_type->data_array , entity_id);
    
    lua_newtable(lua_state);

    lua_pushnumber(lua_state, component_data->position.x);
    lua_setfield(lua_state, -2, "x");

    lua_pushnumber(lua_state, component_data->position.y);
    lua_setfield(lua_state, -2, "y");

    return 1;
}

static void ScriptingECSWrapper_RegisterLuaFunction(lua_State* L, lua_CFunction function, const char* name)
{
    lua_pushcfunction(L, function);
    lua_setfield(L, -2, name);
}

void ScriptingECSWrapper_Register(const EngineApplication* const engine_application)
{
    lua_State* L = engine_application->scripting_subsystem->lua_state;

    lua_pushlightuserdata(L, (void*) engine_application);
    lua_setglobal(L, EMBEDDED_APPLICATION_DATA);

    lua_newtable(L);

    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_PrintInfo, SCRIPTING_FUNCTION_PRINT_INFO);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_CreateEntity, SCRIPTING_FUNCTION_CREATE_ENTITY);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_KillEntity, SCRIPTING_FUNCTION_KILL_ENTITY);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddTransform2DComponent, SCRIPTING_FUNCTION_ADD_TRANSFORM2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddSprite2DComponent, SCRIPTING_FUNCTION_ADD_SPRITE2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddPhysics2DComponent, SCRIPTING_FUNCTION_ADD_PHYSICS2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddAnimatedSprite2DComponent, SCRIPTING_FUNCTION_ADD_ANIMATED_SPRITE2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddParallaxSprite2DComponent, SCRIPTING_FUNCTION_ADD_PARALLAX_SPRITE2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddBoxCollider2DComponent, SCRIPTING_FUNCTION_ADD_BOX_COLLIDER2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_RegisterTransform2DComponent, SCRIPTING_FUNCTION_REGISTER_TRANSFORM2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_RegisterSprite2DComponent, SCRIPTING_FUNCTION_REGISTER_SPRITE2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_RegisterAnimatedSprite2DComponent, SCRIPTING_FUNCTION_REGISTER_ANIMATED_SPRITE2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_RegisterParallaxSprite2DComponent, SCRIPTING_FUNCTION_REGISTER_PARALLAX_SPRITE2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_RegisterPhysics2DComponent, SCRIPTING_FUNCTION_REGISTER_PHYSICS2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_RegisterBoxCollider2DComponent, SCRIPTING_FUNCTION_REGISTER_BOX_COLLIDER2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddRender2DSystem, SCRIPTING_FUNCTION_ADD_RENDER2D_SYSTEM);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddOpenGLRender2DSystem, SCRIPTING_FUNCTION_ADD_OPENGL_RENDER2D_SYSTEM);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddPhysics2DSystem, SCRIPTING_FUNCTION_ADD_PHYSICS2D_SYSTEM);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_AddCollision2DSystem, SCRIPTING_FUNCTION_ADD_COLLISION2D_SYSTEM);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_PublishEntity, SCRIPTING_FUNCTION_PUBLISH_ENTITY);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_GetTransform2DComponent, SCRIPTING_FUNCTION_GET_TRANSFORM2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_UpdateTransform2DComponent, SCRIPTING_FUNCTION_UPDATE_TRANSFORM2D_COMPONENT);
    ScriptingECSWrapper_RegisterLuaFunction(L, ScriptingECSWrapper_UpdatePhysics2DComponent, SCRIPTING_FUNCTION_UPDATE_PHYSICS2D_COMPONENT);

    lua_setglobal(L, SCRIPTING_TABLE_ECS);
}