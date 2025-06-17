#include "OpenGL/OpenGLRenderer.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <Math/Matrix4.h>

char* ReadFile(const char* file_path) {
	FILE* file = fopen(file_path, "rb");

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc((fileSize + 1) * sizeof(char));

	fread(buffer, sizeof(char), fileSize, file);
	buffer[fileSize] = '\0';

	fclose(file);
	return buffer;
}

static OpenGLVertexArray VertexArray_Create(const float* vertex, uint32_t vertex_number, const uint32_t* index, uint16_t index_number)
{
	OpenGLVertexArray vertex_array = { 0 };

	glGenVertexArrays(1, &vertex_array.vertex_array_opengl_id);
    glGenBuffers(1, &vertex_array.vertex_buffer_opengl_id);
    glGenBuffers(1, &vertex_array.index_buffer_opengl_id);

	glBindVertexArray(vertex_array.vertex_array_opengl_id);
    	
	glBindBuffer(GL_ARRAY_BUFFER, vertex_array.vertex_buffer_opengl_id);
	glBufferData(GL_ARRAY_BUFFER, vertex_number * 5 * sizeof(float), vertex, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_array.index_buffer_opengl_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_number * sizeof(uint32_t), index, GL_STATIC_DRAW);
    	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 3 * sizeof(float));
    glEnableVertexAttribArray(1);

    vertex_array.vertex_number = vertex_number;
    vertex_array.index_number = index_number;

	return vertex_array;
}

int Shader_Create(const char* vertex_shader_path, const char* fragment_shader_path)
{
    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char* fragment_shader_code = ReadFile(fragment_shader_path);

    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);

    GLint success;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("Erro no Fragment Shader: %s\n", infoLog);
    }

    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    char* vertex_shader_code = ReadFile(vertex_shader_path);
    if (!vertex_shader_code) {
        free(fragment_shader_code);
        return 0;
    }

    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("Erro no Vertex Shader: %s\n", infoLog);
    }

    int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("Erro no Shader Program: %s\n", infoLog);
    }

    // Cleanup
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(fragment_shader_code);
    free(vertex_shader_code);

    return shader_program;
}


OpenGLVertexArray OpenGLRenderer_CreateQuadShader()
{
	float vertex_buffer[] =
	{
        // Position          // Texture coordinates
		-0.5f, 0.5f, 0.0f,	 0.0f, 0.0f, // Top left vertex
		0.5f, 0.5f, 0.0f,    1.0f, 0.0f, // Top right vertex
		0.5f, -0.5f, 0.0f,   1.0f, 1.0f, // Bottom right vertex
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f// Bottom left vertex
	};

	unsigned int index_buffer[] =
	{
		0, 1, 2, // First triangle
		2, 3, 0  // Second triangle
	};
    int shader_program = Shader_Create("./Shaders/Quad.vert", "./Shaders/Quad.frag");

	OpenGLVertexArray vertex_array = VertexArray_Create(&vertex_buffer, 4, &index_buffer, 6);

    vertex_array.opengl_shader_program = shader_program;

	return vertex_array;
}