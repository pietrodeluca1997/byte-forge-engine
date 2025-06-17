#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texture_coordinates;

out vec2 texture_coordinates;

uniform mat4 projection_matrix;
uniform mat4 model_matrix;

void main()
{
	texture_coordinates = in_texture_coordinates;
	gl_Position = projection_matrix * model_matrix * vec4(position, 1.0);
}