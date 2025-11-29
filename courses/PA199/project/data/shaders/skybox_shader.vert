#version 430 core


// Box Data //
const vec3 positions[36] = vec3[36]
(
	vec3( -1.0f,  1.0f,  1.0f ),
	vec3( -1.0f, -1.0f,  1.0f ),
	vec3(  1.0f, -1.0f,  1.0f ),
	vec3( -1.0f,  1.0f,  1.0f ),
	vec3(  1.0f, -1.0f,  1.0f ),
	vec3(  1.0f,  1.0f,  1.0f ),
			
	vec3(  1.0f,  1.0f,  1.0f ),
	vec3(  1.0f, -1.0f,  1.0f ),
	vec3(  1.0f, -1.0f, -1.0f ),
	vec3(  1.0f,  1.0f,  1.0f ),
	vec3(  1.0f, -1.0f, -1.0f ),
	vec3(  1.0f,  1.0f, -1.0f ),

	vec3(  1.0f,  1.0f, -1.0f ),
	vec3(  1.0f, -1.0f, -1.0f ),
	vec3( -1.0f, -1.0f, -1.0f ),
	vec3(  1.0f,  1.0f, -1.0f ),
	vec3( -1.0f, -1.0f, -1.0f ),
	vec3( -1.0f,  1.0f, -1.0f ),
	
	vec3( -1.0f,  1.0f, -1.0f ),
	vec3( -1.0f, -1.0f, -1.0f ),
	vec3( -1.0f, -1.0f,  1.0f ),
	vec3( -1.0f,  1.0f, -1.0f ),
	vec3( -1.0f, -1.0f,  1.0f ),
	vec3( -1.0f,  1.0f,  1.0f ),
	
	vec3( -1.0f,  1.0f, -1.0f ),
	vec3( -1.0f,  1.0f,  1.0f ),
	vec3(  1.0f,  1.0f,  1.0f ),
	vec3( -1.0f,  1.0f, -1.0f ),
	vec3(  1.0f,  1.0f,  1.0f ),
	vec3(  1.0f,  1.0f, -1.0f ),
			
	vec3( -1.0f, -1.0f,  1.0f ),
	vec3( -1.0f, -1.0f, -1.0f ),
	vec3(  1.0f, -1.0f, -1.0f ),
	vec3( -1.0f, -1.0f,  1.0f ),
	vec3(  1.0f, -1.0f, -1.0f ),
	vec3(  1.0f, -1.0f,  1.0f )
);

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


// The Data about the Vertex (in World Space) //
out vec3 tex_coord;


void main()
{
	tex_coord = positions[gl_VertexID];
    gl_Position = projection * view * vec4(positions[gl_VertexID] * 100.0f, 1.0);
}