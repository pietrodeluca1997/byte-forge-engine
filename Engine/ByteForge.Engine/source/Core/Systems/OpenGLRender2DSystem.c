#include "ByteForgeEngine/Core/Systems/OpenGLRender2DSystem.h"
#include "ByteForgeEngine/Core/Components/Transform2DComponent.h"
#include "ByteForgeEngine/Core/Components/Sprite2DComponent.h"
#include "ByteForgeEngine/Core/Components/AnimatedSprite2DComponent.h"
#include "ByteForgeEngine/Core/Components/ParallaxSprite2DComponent.h"

#include "OpenGL/OpenGLRenderer.h"

#include <Math/Matrix4.h>
#include <Memory/Helpers/MemoryStructureHelper.h>

#include <glad/glad.h>

OpenGLRender2DSystem* OpenGLRender2DSystem_New(ECS_ComponentType* transform_2d_component, ECS_ComponentType* sprite_2d_component, ECS_ComponentType* animated_sprite_2d_component, ECS_ComponentType* parallax_sprite_2d_component)
{
    OpenGLRender2DSystem* system = ALLOC(OpenGLRender2DSystem, MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);

    if (!system) return NULL;

    system->opengl_vertex_array = OpenGLRenderer_CreateQuadShader();
    system->transform_2d_component = transform_2d_component;
    system->sprite_2d_component = sprite_2d_component;
    system->animated_sprite_2d_component = animated_sprite_2d_component;
    system->parallax_sprite_2d_component = parallax_sprite_2d_component;

    return system;
}

void OpenGLRender2DSystem_Update(ECS_Registry* registry, ECS_System* self, const double delta_time)
{
    OpenGLRender2DSystem* opengl_render_system = self->data;

    glUseProgram(opengl_render_system->opengl_vertex_array.opengl_shader_program);
    
    Matrix4 projection = Matrix4_Orthographic(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
    int projection_matrix = glGetUniformLocation(opengl_render_system->opengl_vertex_array.opengl_shader_program, "projection_matrix");
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &projection.matrix_data[0]);

    for (uint64_t i = 0; i < self->entities->count; i++)
    {
        ECS_Entity* entity = DynamicArray_Get(self->entities, i);

        Transform2DComponent* entity_transform = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(opengl_render_system->transform_2d_component->entity_id_to_array_index_map, opengl_render_system->transform_2d_component->data_array, entity->id);
        Sprite2DComponent* entity_sprite = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(opengl_render_system->sprite_2d_component->entity_id_to_array_index_map, opengl_render_system->sprite_2d_component->data_array, entity->id);
        AnimatedSprite2DComponent* entity_animated_sprite = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(opengl_render_system->animated_sprite_2d_component->entity_id_to_array_index_map, opengl_render_system->animated_sprite_2d_component->data_array, entity->id);
        ParallaxSprite2DComponent* entity_parallax_sprite = MemoryStructureHelper_GetValueFromArrayUsingDictIndex(opengl_render_system->parallax_sprite_2d_component->entity_id_to_array_index_map, opengl_render_system->parallax_sprite_2d_component->data_array, entity->id);
        
        int model_matrix = glGetUniformLocation(opengl_render_system->opengl_vertex_array.opengl_shader_program, "model_matrix");
               
        if (entity_sprite)
        {
            Matrix4 model = Matrix4_Identity();
            model = Matrix4_Scale(model, entity_transform->size.x, entity_transform->size.y, 1.0f);
            model = Matrix4_Translate(model, entity_transform->position.x, entity_transform->position.y, 0.0f);

            glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model.matrix_data[0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, entity_sprite->texture_id);
            int texture_location = glGetUniformLocation(opengl_render_system->opengl_vertex_array.opengl_shader_program, "in_texture");
            glUniform1i(texture_location, 0);
        }
        else if (entity_animated_sprite)
        {
            entity_animated_sprite->current_frame += entity_animated_sprite->desired_frame_rate * delta_time;

            if (entity_animated_sprite->current_frame >= entity_animated_sprite->animation_textures->count)
            {
                entity_animated_sprite->current_frame = fmod(entity_animated_sprite->current_frame, entity_animated_sprite->animation_textures->count);
            }

            Matrix4 model = Matrix4_Identity();
            model = Matrix4_Scale(model, entity_transform->size.x, entity_transform->size.y, 1.0f);
            model = Matrix4_Translate(model, entity_transform->position.x, entity_transform->position.y, 0.0f);

            glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model.matrix_data[0]);

            uint32_t* texture_id = DynamicArray_Get(entity_animated_sprite->animation_textures, entity_animated_sprite->current_frame);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, *texture_id);
            int texture_location = glGetUniformLocation(opengl_render_system->opengl_vertex_array.opengl_shader_program, "in_texture");
            glUniform1i(texture_location, 0);
        }
        else if (entity_parallax_sprite)
        {
           for (uint64_t j = 0; j < entity_parallax_sprite->animation_textures->count; j++)
           {
                ParallaxTexture* parallax_texture = DynamicArray_Get(entity_parallax_sprite->animation_textures, j);

                parallax_texture->offset.x -= entity_parallax_sprite->scroll_speed;

                if (parallax_texture->offset.x < -entity_transform->size.x)
                {
                    parallax_texture->offset.x = (entity_parallax_sprite->animation_textures->count - 1) * entity_transform->size.x;
                }
                
                Matrix4 model = Matrix4_Identity();
                model = Matrix4_Scale(model, entity_transform->size.x, entity_transform->size.y, 1.0f);
                model = Matrix4_Translate(model, entity_transform->position.x + parallax_texture->offset.x, entity_transform->position.y + parallax_texture->offset.y, 0.0f);

                glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model.matrix_data[0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, parallax_texture->texture_id);
                int texture_location = glGetUniformLocation(opengl_render_system->opengl_vertex_array.opengl_shader_program, "in_texture");
                glUniform1i(texture_location, 0);

                glBindVertexArray(opengl_render_system->opengl_vertex_array.vertex_array_opengl_id);
                glDrawElements(GL_TRIANGLES, opengl_render_system->opengl_vertex_array.index_number, GL_UNSIGNED_INT, NULL);

           }
        }
        else
        {
            continue;
        }

        glBindVertexArray(opengl_render_system->opengl_vertex_array.vertex_array_opengl_id);

        glDrawElements(GL_TRIANGLES, opengl_render_system->opengl_vertex_array.index_number, GL_UNSIGNED_INT, NULL);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

void OpenGLRender2DSystem_Free(OpenGLRender2DSystem** opengl_render_2d_system)
{
    if (!opengl_render_2d_system || !*opengl_render_2d_system)
    {
        return;
    }

    FREE(opengl_render_2d_system, sizeof(OpenGLRender2DSystem), MEMORY_ALLOCATION_CATEGORY_ECS_SYSTEM);
}
