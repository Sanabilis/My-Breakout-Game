#version 430 core


// Vertex Data //
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;


// The Data about the Camera //	
layout (std140, binding = 0) uniform CameraData
{
	mat4 projection;	 // The Projection Matrix.
	mat4 projection_inv;
	mat4 view;			 // The View Matrix
	mat4 view_inv;
	mat4 view_it;
};

layout(location = 0) uniform vec3 eye_position;


// The Data about the Model //	
layout (std140, binding = 1) uniform ModelData
{
	mat4 model;		// The Model Matrix.
	mat4 model_inv;
	mat4 model_it;
};

layout (std140, binding = 2) uniform MaterialData
{
	vec4 ambient;	 // Material Color
	vec4 diffuse;
	vec4 specular;
	float shininess; // Material Surface Properties
	float roughness;
	float alpha;
};

// Texture //
layout(location = 1) uniform bool has_texture;
uniform sampler2D sample_texture;


// The Data about the Lights //	
struct LightData
{
	vec4 position;	  // The Position of the Light (+ w, which decided between directional and point light)
	vec4 attenuation; // The Light Attenuation + Radius
	vec4 ambient;	  // The Light Color
	vec4 diffuse;
	vec4 specular;
};

layout(std430, binding = 3) buffer LightBuffer
{
    LightData lights[];
};

layout(location = 2) uniform uint lights_count;
layout(location = 3) uniform vec3 global_ambient;


// The Data about the Vertex (in World Space) //
out Vertex
{
	vec3 position;
	vec3 normal;
	vec2 tex_coord;
} out_vertex;


void main()
{
    gl_Position = projection * view * vec4(position * 10000.f, 1.0);
}