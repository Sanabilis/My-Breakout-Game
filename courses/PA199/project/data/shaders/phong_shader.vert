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


// The Data about the Vertex (in world space) //
out Vertex
{
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	vec2 tex_coord;
} out_vertex;


void main()
{
	out_vertex.position = vec3(model * vec4(position, 1.0));
	out_vertex.normal = vec3(model_it * vec4(normal, 0.0));
	out_vertex.tex_coord = tex_coord;

	if (length(normalize(out_vertex.normal) - vec3(0.0f, 1.0f, 0.0f)) < 10e-05 || length(normalize(out_vertex.normal) + vec3(0.0f, 1.0f, 0.0f)) < 10e-05)
	{
		out_vertex.tangent = vec3(1.0f, 0.0f, 0.0f);
		out_vertex.bitangent = vec3(0.0f, 0.0f, 1.0f);
	}
	else
	{
		out_vertex.tangent = cross(vec3(0.0f, 1.0f, 0.0f), out_vertex.normal);
		out_vertex.bitangent = cross(out_vertex.normal, out_vertex.tangent);
	}

    gl_Position = projection * view * model * vec4(position, 1.0f);
}