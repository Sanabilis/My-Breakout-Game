#version 430 core

// The Data about the Vertex (in World Space) //
in Vertex
{
	vec3 position;
	vec2 tex_coord;
} in_vertex;

// Texture //
layout(location = 1) uniform bool has_diffuse_texture;
uniform sampler2D sample_texture;

// The Final Color of the Fragment //
layout(location = 0) out vec4 final_color;

void main()
{
	if (has_diffuse_texture)
	{
		vec4 color = texture(sample_texture, in_vertex.tex_coord);
		final_color = vec4(vec3(1.0f), color.a);
	}
}