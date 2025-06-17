#version 460 core

in vec2 texture_coordinates;
out vec4 out_color;

uniform sampler2D in_texture;

void main()
{
	out_color = texture(in_texture, texture_coordinates);
}