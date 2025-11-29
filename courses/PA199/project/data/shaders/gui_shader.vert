#version 430 core


// Vertex Data //
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 anchor;
layout(location = 2) in vec2 tex_coord;

layout(location = 0) uniform vec2 size;

// Texture //
layout(location = 1) uniform bool has_diffuse_texture;
uniform sampler2D sample_texture;

// The Data about the Vertex (in World Space) //
out Vertex
{
	vec3 position;
	vec2 tex_coord;
} out_vertex;


void main()
{
	float width = size.x;
	float height = size.y;
	float aspect = width / height;

	out_vertex.position = vec3(anchor.x + min(height, width) * position.x / (aspect * height), anchor.y + min(height, width) * position.y / height, 0.0f);
	out_vertex.tex_coord = tex_coord;

    gl_Position = vec4(out_vertex.position, 1.0f);
}