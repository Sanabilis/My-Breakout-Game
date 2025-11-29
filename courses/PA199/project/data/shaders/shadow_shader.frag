#version 430 core

// The Data about the Vertex (in World Space) //
in Vertex
{
	vec3 position;
	vec3 normal;
	vec2 tex_coord;
} in_vertex;

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
layout(location = 1) uniform bool has_diffuse_texture;
layout (binding = 0) uniform sampler2D diffuse_texture;

// Texture //
layout(location = 2) uniform bool has_normal_texture;
layout (binding = 1) uniform sampler2D normal_texture;


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

layout(location = 3) uniform uint lights_count;
layout(location = 4) uniform vec3 global_ambient;

layout(location = 5) uniform bool use_alpha;
layout(location = 6) uniform vec3 ball_position;

layout (binding = 2) uniform sampler2D shadow_texture;
layout(location = 7) uniform mat4 shadow_matrix;


// The Final Color of the Fragment //
layout(location = 0) out vec4 final_color;


void main()
{
	//vec4 position_cs = projection * view * vec4(in_vertex.position, 1.0f);
	//float depth = position_cs.z / position_cs.w;
	final_color = vec4(1.0f);
}