#pragma once

#include <stdint.h>

typedef struct OpenGLVertexArray
{
	// How many vertices in the vertex buffer?
	uint32_t vertex_number;
	// How many indices in the index buffer?
	uint32_t index_number;
	// OpenGL ID of the vertex buffer
	uint32_t vertex_buffer_opengl_id;
	// OpenGL ID of the index buffer
	uint32_t index_buffer_opengl_id;
	// OpenGL ID of the vertex array object
	uint32_t vertex_array_opengl_id;
	int opengl_shader_program;
} OpenGLVertexArray;

OpenGLVertexArray OpenGLRenderer_CreateQuadShader();