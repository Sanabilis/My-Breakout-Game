#version 430 core


// Color of the Line //
uniform vec3 color;


// 3D texture coordinates //
in vec3 tex_coord;

// Skybox //
uniform samplerCube skybox;


// The Final Color of the Fragment //
layout(location = 0) out vec4 final_color;


void main()
{
    final_color = vec4(texture(skybox, vec3(-tex_coord.x, tex_coord.y, -tex_coord.z)).rgb, 1.0);
}